/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"

#define FCY 625000

//Uses timer 2

void initTimer2(){

    TMR2 = 0; //reset timer register
    T2CONbits.TCS = 0; // Enable Internal peripheral clock
    T2CONbits.TCKPS = 0b111; //Prescalar of 256
    IFS0bits.T2IF = FLAG_DOWN;  //Interrupt Flag Down



    return;
}

void delayUs(float delay){
    //TODO: Create a delay using timer 2 for "delay" microseconds.

    unsigned int prVal = ((FCY*delay*0.000001)/256.0 -1.0); //Calculate the PR value using delay as the time, converted to ms.
    PR2 = prVal;
    TMR2 = 0;   //reset timer 2 register
    T2CONbits.TON = 1; //Timer on
    IFS0bits.T2IF = FLAG_DOWN; // Flag Down
    while(IFS0bits.T2IF == FLAG_DOWN){} // While the flag is down, once flag is raised exit loop
    // Flag would be raised in hardware here.
    IFS0bits.T2IF = FLAG_DOWN; //Flag Down
    T2CONbits.TON = 0; // Timer off


    //TODO: Using timer 2, create a delay
    // that is delay amount of us.
    return;
}