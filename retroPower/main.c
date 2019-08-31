#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "debugLogger.h"
#include "powerConfig.h"
#include "checkBat.h"
#include "powerOff.h"

powerConfig config;
char configFile[] = "/boot/retropower.cfg";
int checkIntervalInSec = 1;

int main(int argc, char *argv[]) 
{    
    if(access(configFile, F_OK) != -1)
    {
        config = readPowerConfig(configFile);
        writeDebug(config, "Shutdown Pin: %d", config.shutdownPin);
        writeDebug(config, "Shutdown Active: %s", config.shutdownActive ? "true" : "false");
        writeDebug(config, "Check Bat Active: %s", config.checkActive ? "true" : "false");
        writeDebug(config, "Only Read ADC: %s", config.onlyReadAdc ? "true" : "false");

        wiringPiSetup();
        wiringPiSPISetup(0, 4*1000*1000);
        if(config.shutdownPin != -1 && config.shutdownActive) 
        {           
            pinMode(config.shutdownPin, INPUT);
        }          

        if(config.shutdownActive || config.checkActive)
        {
            while(1) 
            {
                if(config.shutdownActive) checkPowerOff(config);
                if(config.checkActive) checkBat(config);
                sleep(checkIntervalInSec);
            }
        }
    } 
}

