/* 
* File:   leds.h
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#ifndef LEDS_H
#define	LEDS_H

#define RUN_LED 1
#define STOP_LED 2

// initialize the led 
void initLED(int i);

// turn on the specified led 
void turnOnLED(int i);

// turn off the specified led 
void turnOffLED(int i);

#endif	/* LEDS_H */

