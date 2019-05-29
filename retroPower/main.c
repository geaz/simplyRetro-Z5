#include <time.h>
#include <wiringPi.h>
#include <iostream>
#include <stdlib.h>
#include <mcp3008.h>

#define BASE 100
#define SPI_CHAN 0

time_t shutdownPressedOn;

int main() 
{
    wiringPiSetup();
    mcp3008Setup (BASE, SPI_CHAN);
    pinMode(24, INPUT);

    while(1) 
    {
        if(digitalRead(1) == 1) 
        {
            for (chan = 0 ; chan < 8 ; ++chan) {
                x = analogRead (BASE + chan) ;
                printf("%d\n", x);
            }

            if(shutdownPressedOn == 0) 
            {
                shutdownPressedOn = time(0);
            }
            else if(time(0) >= shutdownPressedOn + 3) 
            {
                system("shutdown -P now");
            }            
        }
        else if(shutdownPressedOn != 0) {
            shutdownPressedOn = 0;
        }
    }
}