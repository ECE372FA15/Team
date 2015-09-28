
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
    if(i == RUN_LED)
        TRISGbits.TRISG12 = OUTPUT;
    else if ( i == STOP_LED)      
        TRISGbits.TRISG14 = OUTPUT;    
}

void turnOnLED(int i)
{
    if(i == RUN_LED)
        LATGbits.LATG12 = ON;
    else if (i == STOP_LED)
        LATGbits.LATG14 = ON;
}

void turnOffLED(int i)
{
    if(i == RUN_LED)
        LATGbits.LATG12 = OFF;
    else if (i == STOP_LED)
        LATGbits.LATG14 = OFF;
}

