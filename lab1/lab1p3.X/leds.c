
// File:         leds.c
// Date:         9/24/2015
// Authors:      Brandon Lipjanic
//               Jonathan Hawkins
//               Abigail Francis
//               Pierce Simpson

#include <xc.h>
#include "leds.h"
#define OUTPUT 0
#define OFF 1
#define ON 0

//Changed LED1 to reflect assignment to TRD1 on reg G pin 12
//Changed LED2 to reflect assignment to TRD2 on reg G pin 14

void initLED(int i)
{
    if(i == 0)
        TRISGbits.TRISG12 = 0;
    else if ( i == 1)      
        TRISAbits.TRISA7 = 0;    
}

void turnOnLED(int i)
{
    if(i == 0)
        LATGbits.LATG12 = 0;
    else if (i == 1)
        LATAbits.LATA7 = 0;
}

void turnOffLED(int i)
{
    if(i == RUN_LED)
        LATGbits.LATG12 = 1;
    else if (i == STOP_LED)
        LATAbits.LATA7 = 1;
}

void toggleAllLEDs()
{    
        LATGbits.LATG12 = !LATGbits.LATG12;
        LATAbits.LATA7 = !LATAbits.LATA7;
}