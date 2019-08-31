#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>

#include "powerConfig.h"
#include "powerOff.h"
#include "debugLogger.h"

time_t shutdownPressedOn = 0;
int shutdownPressDurationInSec = 3;

void checkPowerOff(const powerConfig config)
{
    if(shutdownPressedOn == 0 && digitalRead(config.shutdownPin) == 1)
    {
        shutdownPressedOn = time(0);
    }
    else if(shutdownPressedOn != 0 && time(0) >= shutdownPressedOn + shutdownPressDurationInSec && digitalRead(config.shutdownPin) == 1)
    {
        writeDebug(config, "Power Off initiated (Button pressed)");
        system("halt");
    }
    else if(shutdownPressedOn != 0 && digitalRead(config.shutdownPin) == 0)
    {
        shutdownPressedOn = 0;
    }
}