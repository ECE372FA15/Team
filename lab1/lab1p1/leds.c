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

#include <xc.h>
#include "leds.h"
#define OUTPUT 0
#define OFF 0
#define ON 1

void initLED(int i)
{
    if(i == 1)
        TRISDbits.TRISD1 = OUTPUT;
    else if ( i == 2)      
        TRISDbits.TRISD2 = OUTPUT;    
}

void turnOnLED(int i)
{
    if(i == 1)
        LATDbits.LATD1 = ON;
    else if (i == 2)
        LATDbits.LATD2 = ON;
}

void turnOffLED(int i)
{
    if(i == 1)
        LATDbits.LATD1 = OFF;
    else if (i == 2)
        LATDbits.LATD2 = OFF;
}

