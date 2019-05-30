#include <time.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

time_t shutdownPressedOn;

int main() 
{
    wiringPiSetup();
    pinMode(24, INPUT); // WiringPi24 = GPIO 19
    while(1) 
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
        else if(shutdownPressedOn != 0) {
            shutdownPressedOn = 0;
        }
    }
}