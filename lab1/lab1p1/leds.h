
// File:         leds.h
// Date:         9/24/2015
// Authors:      Brandon Lipjanic
//               Jonathan Hawkins
//               Abigail Francis
//               Pierce Simpson

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

void toggleAllLEDs();

#endif	/* LEDS_H */

