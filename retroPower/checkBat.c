#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "checkBat.h"
#include "debugLogger.h"
#include "powerConfig.h"

char iconName[] = "battery";
char filePath[] = "/root/.retropower/";
char extension[] = ".png";
char iconFilePath[50];
char lastShownImage[50];

int checkBatIntervalInSec = 10;
time_t lastBatCheck = 0;

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

void checkBat(const powerConfig config)
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

        if(batPercentage < 0.03 && !config.onlyReadAdc)
        {
            writeDebug(config, "Power Off initiated (Bat Low)");
            system("halt");
        }
        if(batPercentage < 0.03)
        {
            writeDebug(config, "Only Read ADC Mode! Battery Low!");
        }
        else if(batPercentage < 0.1)
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

        writeDebug(config, "Max Voltage Bat (After Divider): %.6f", maxVoltageBat);
        writeDebug(config, "Min Voltage Bat (After Divider): %.6f", minVoltageBat);
        writeDebug(config, "Correction Factor (Caused By Divider): %.6f", correctionFactor);
        writeDebug(config, "Bat Relative Read: %.6f", batRelativeRead);
        writeDebug(config, "Bat Corrected Read: %.6f", batCorrectedRead);
        writeDebug(config, "Effective Range Start: %.6f", effectiveRangeStart);
        writeDebug(config, "Effective Range: %.6f", effectiveRange);
        writeDebug(config, "Bat Level Effective: %.6f", batLevelEffective);
        writeDebug(config, "Bat Percentage: %.6f", batPercentage);
    }
        
    if(strcmp(lastShownImage, iconFilePath) != 0)
    {
        if(config.debugActive)
        {            
            writeDebug(config, "%s\n", iconFilePath);
        }
        
        strcpy(lastShownImage, iconFilePath);
        system("killall -9 pngview");

        char buf[100];
        sprintf(buf, "%s %s &", "pngview -b 0x0000 -d 0 -l 15000 -y 5 -x 775", iconFilePath);
        system(buf);     
    }   
}