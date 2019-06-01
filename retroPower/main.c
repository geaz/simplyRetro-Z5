#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <signal.h>
#include <string.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#define BATADC 0
#define USBADC 1

#define DIVIDER_R1 6800.0
#define DIVIDER_R2 10000.0

#define BAT_MIN 3.65
#define BAT_MAX 4.05
#define GPIO_MAX 3.3

time_t shutdownPressedOn = 0;
time_t lastUsbCheck = 0;
time_t lastBatCheck = 0;

int checkUsbIntervalInSec = 1;
int checkBatIntervalInSec = 10;

char lastShownImage[50];

void checkPowerOff();
void checkBat();
float voltageDivider(float r1, float r2, float vin);
int analogPowerRead(int adcnum);

int main() 
{
    wiringPiSetup();
    wiringPiSPISetup(0, 4*1000*1000);
    pinMode(24, INPUT); // WiringPi24 = GPIO 19 - The PowerOff Pin

    while(1) 
    {
        checkPowerOff();
        checkBat();
    }
}

void checkPowerOff()
{
    if(digitalRead(24) == 1) 
    {
        if(shutdownPressedOn == 0) 
        {
            shutdownPressedOn = time(0);
        }
        else if(time(0) >= shutdownPressedOn + 3) 
        {
            system("poweroff");
        }            
    }
    else if(shutdownPressedOn != 0) 
    {
        shutdownPressedOn = 0;
    }
}

void checkBat()
{
    if(lastUsbCheck == 0 || time(0) >= lastUsbCheck + checkUsbIntervalInSec)
    {
        lastUsbCheck = time(0);

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

        char iconName[] = "battery";
        char filePath[] = "/root/.retropower/";
        char extension[] = ".png";
        char iconFilePath[50];

        if(analogPowerRead(1) > 0) 
        {
            sprintf(iconFilePath, "%s%s-%s%s", filePath, iconName, "charging", extension);
        }
        else if(lastBatCheck == 0 || time(0) >= lastBatCheck + checkBatIntervalInSec)
        {
            lastBatCheck = time(0);
            if(roundedBatPercentage < 2)
            {
                system("poweroff");
            }
            else if(roundedBatPercentage < 5)
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
        }
        else
        {
            strcpy(iconFilePath, lastShownImage);
        }

        printf("%s\n", iconFilePath);
        if(strcmp(lastShownImage, iconFilePath) != 0)
        {
            strcpy(lastShownImage, iconFilePath);
            system("killall -9 pngview");

            char buf[100];
            sprintf(buf, "%s %s &", "pngview -b 0x0000 -d 0 -l 15000 -y 5 -x 775", iconFilePath);
            system(buf);     
        }
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