#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#define BATADC 0
#define USBADC 1

#define DIVIDER_R1 6800.0
#define DIVIDER_R2 10000.0

#define BAT_MIN 3.4
#define BAT_MAX 4.05
#define GPIO_MAX 3.3

time_t shutdownPressedOn = 0;
time_t lastBatCheck = 0;

int checkIntervalInSec = 3;
int checkBatIntervalInSec = 10;

char lastShownImage[50];
bool debug = false;

char iconName[] = "battery";
char filePath[] = "/root/.retropower/";
char extension[] = ".png";
char iconFilePath[50];

void checkDebug(int argc, char *argv[]);
void checkPowerOff();
void checkBat();
float voltageDivider(float r1, float r2, float vin);
int analogPowerRead(int adcnum);

int main(int argc, char *argv[]) 
{
    checkDebug(argc, argv);    
    wiringPiSetup();
    wiringPiSPISetup(0, 4*1000*1000);
    pinMode(24, INPUT); // WiringPi24 = GPIO 19 - The PowerOff Pin

    while(1) 
    {
        checkPowerOff();
        checkBat();
        sleep(checkIntervalInSec);
    }
}

void checkDebug(int argc, char *argv[])
{
    if(argc > 1 && strcmp(argv[1], "debug") == 0)
    {
        debug = true;
    }
}

void checkPowerOff()
{
    if(shutdownPressedOn == 0 && digitalRead(24) == 1)
    {
        shutdownPressedOn = time(0);
    }
    else if(shutdownPressedOn != 0 && digitalRead(24) == 1)
    {
        system("poweroff");
    }
    else
    {
        shutdownPressedOn = 0;
    }
}

void checkBat()
{
    if(analogPowerRead(1) > 0)
    {
        sprintf(iconFilePath, "%s%s-%s%s", filePath, iconName, "charging", extension);
    }
    else if(lastBatCheck == 0 || time(0) >= lastBatCheck + checkBatIntervalInSec)
    {
        lastBatCheck = time(0);

        // The Max Voltage we get from the BAT Pin
        float maxVoltageBat = voltageDivider(DIVIDER_R1, DIVIDER_R2, BAT_MAX);
        // The Min Voltage we get from the BAT Pin
        float minVoltageBat = voltageDivider(DIVIDER_R1, DIVIDER_R2, BAT_MIN);
        // Because our VREF is 3.3v coming from PI and this will be not equal to 
        // our max voltage coming from the BAT Pin
        // we have to calculate a conversion factor
        float correctionFactor = 1 / (maxVoltageBat / GPIO_MAX);

        float batRelativeRead = analogPowerRead(0);
        float batCorrectedRead = batRelativeRead * correctionFactor; 
        
        float effectiveRangeStart = (1024 / maxVoltageBat) * minVoltageBat;
        float effectiveRange = 1024 - effectiveRangeStart;

        float batLevelEffective = batCorrectedRead - effectiveRangeStart;
        float batPercentage = batLevelEffective / effectiveRange;
         
        int roundedBatPercentage = round(batPercentage*100);

        if(batPercentage < 3)
        {
            system("poweroff");
        }
        else if(batPercentage < 10)
        {
            sprintf(iconFilePath, "%s%s-%s%s", filePath, iconName, "alert", extension);
        }
        else if(roundedBatPercentage < 95) 
        {
            int tenthRoundedBatPercentage = roundedBatPercentage - (roundedBatPercentage%10);
            sprintf(iconFilePath, "%s%s-%d%s", filePath, iconName, tenthRoundedBatPercentage, extension);
        }
        else 
        {
            sprintf(iconFilePath, "%s%s%s", filePath, iconName, extension);
        }

        if(debug)
        {
            printf("Max Voltage Bat: %.6f\n", maxVoltageBat);
            printf("Min Voltage Bat: %.6f\n", minVoltageBat);
            printf("Correction Factor: %.6f\n", correctionFactor);
            printf("Bat Relative Read: %.6f\n", batRelativeRead);
            printf("Bat Corrected Read: %.6f\n", batCorrectedRead);
            printf("Effective Range Start: %.6f\n", effectiveRangeStart);
            printf("Effective Range: %.6f\n", effectiveRange);
            printf("Bat Level Effective: %.6f\n", batLevelEffective);
            printf("Bat Percentage: %.6f\n", batPercentage);
        }
    }
        
    if(strcmp(lastShownImage, iconFilePath) != 0)
    {
        if(debug)
        {            
            printf("%s\n", iconFilePath);
        }
        
        strcpy(lastShownImage, iconFilePath);
        system("killall -9 pngview");

        char buf[100];
        sprintf(buf, "%s %s &", "pngview -b 0x0000 -d 0 -l 15000 -y 5 -x 775", iconFilePath);
        system(buf);     
    }   
}

/* 
Calculate the output of a voltage divider
voltage_divider layout is:
Vin ---[ R1 ]---[ R2 ]---GND
              |
            Vout

Vout = R2 / (R1 + R2) * Vin
 e.g. if R1 = 6800 and R2 = 10000 and Vin is 5.2V then Vout is 3.095 
 */
float voltageDivider(float r1, float r2, float vin) 
{
    return vin * (r2 / (r1 + r2));
}

int analogPowerRead(int adcnum)
{ 
    unsigned int commandout = 0;
    unsigned int adcout = 0;

    commandout = adcnum & 0x3;  // only 0-7
    commandout |= 0x18;     // start bit + single-ended bit

    uint8_t spibuf[3];

    spibuf[0] = commandout;
    spibuf[1] = 0;
    spibuf[2] = 0;

    wiringPiSPIDataRW(0, spibuf, 3);    

    adcout = ((spibuf[1] << 8) | (spibuf[2])) >> 4;

    return adcout;
} 