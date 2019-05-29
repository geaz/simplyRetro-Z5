#include <time.h>
#include <wiringPi.h>
#include <stdlib.h>

time_t shutdownPressedOn;

int main() 
{
    wiringPiSetup();
    pinMode(19, INPUT);

    while(1) 
    {
        if(digitalRead(1) == 1) 
        {
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