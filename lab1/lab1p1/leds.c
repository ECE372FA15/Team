/*
 *	Jonathan    Hawkins
 *  Abigail     Francis
 *  Brandon     Lipjanic
 *  Pierce      Simpson
 * 
 *	University of Arizona
 *	ece 372 lab 1
 * 
 * File: leds.c 
*/

#include "leds.h"
#include <xc.h>
#define OUTPUT 0
#define OFF 0
#define ON 1

void initLEDs()
{
    TRISDbits.TRISD1 = OUTPUT;
    TRISDbits.TRISD2 = OUTPUT;    
}

void turnOnLED(int i)
{
    if(i == 1)
        LATDbits.LATD1 = ON;
    else
        LATDbits.LATD2 = ON;
}

void turnOffLED(int i)
{
    if(i == 1)
        LATDbits.LATD1 = OFF;
    else
        LATDbits.LATD2 = OFF;
}

