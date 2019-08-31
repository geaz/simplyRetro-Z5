#ifndef CHECKBAT_H
#define CHECKBAT_H

#define BATADC 0
#define USBADC 1

#define DIVIDER_R1 6800.0
#define DIVIDER_R2 10000.0

#define BAT_MIN 3.4
#define BAT_MAX 4.05
#define GPIO_MAX 3.3

void checkBat();

#endif /* CHECKBAT_H */