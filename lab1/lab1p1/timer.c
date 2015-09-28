
// File:         timer.c
// Date:         9/24/2015
// Authors:      Brandon Lipjanic
//               Jonathan Hawkins
//               Abigail Francis
//               Pierce Simpson


#include <xc.h>
#include <proc/p32mx470f512l.h>
#include "timer.h"
#include "vardefs.h"

#define FCY 625000

//Uses timer 2

void initTimer2(){

    TMR2 = 0; //reset timer register
    T2CONbits.TCS = DISABLE; // Enable Internal peripheral clock
    T2CONbits.TCKPS = 0b111; //Prescalar of 256
    //Enable interrupt
   // IEC0bits.T2IE = ENABLE;
    //Set interrupt priority
    IPC2bits.T2IP = 3;
    IFS0bits.T2IF = FLAG_DOWN;  //Interrupt Flag Down


    return;
}

void delayUs(float delay){
    //TODO: Create a delay using timer 2 for "delay" microseconds.

    unsigned int prVal = (unsigned int)((FCY*delay*0.00001)/256.0 - 1.0); //Calculate the PR value using delay as the time, converted to ms.
    PR2 = prVal/2;
    TMR2 = 0;   //reset timer 2 register
    IFS0bits.T2IF = FLAG_DOWN; // Flag Down
    T2CONbits.TON = 1; //Timer on
    while(IFS0bits.T2IF == FLAG_DOWN){} // While the flag is down, once flag is raised exit loop
    // Flag would be raised in hardware here.
    IFS0bits.T2IF = FLAG_DOWN; //Flag Down
    T2CONbits.TON = 0; // Timer off


    //TODO: Using timer 2, create a delay
    // that is delay amount of us.
    return;
}