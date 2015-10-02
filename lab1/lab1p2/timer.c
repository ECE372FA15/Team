
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

#define FCY 80000000
#define SCALAR 0.000001
#define PRE_SCALAR 1

//Uses timer 2

void initTimer2(){

    TMR2 = 0; //reset timer register
    T2CONbits.TCS = DISABLE; // Enable Internal peripheral clock
    T2CONbits.TCKPS = 0b000; //Prescalar of 8
//    IPC2bits.T2IP = 3;
    IFS0bits.T2IF = FLAG_DOWN;  //Interrupt Flag Down


    return;
}

void delayUs(float delay){
    //TODO: Create a delay using timer 2 for "delay" microseconds.

    long int prVal = ((FCY*delay*SCALAR)/PRE_SCALAR - 1.0); //Calculate the PR value using delay as the time, converted to ms.
   
    // if the delay value is less than about 200 (or something) PR2 would be 
    //     assigned to 0 and thats not good 
    if (prVal <= 0)
        { PR2 = 1; }
    else if (prVal >= 0xFFFF){
        PR2 = 0xFFFF;}
    else {
        PR2 = prVal;}
    
    TMR2 = 0;   //reset timer 2 register
    IFS0bits.T2IF = FLAG_DOWN; // Flag Down
    T2CONbits.TON = 1; //Timer on
    
    while(IFS0bits.T2IF == FLAG_DOWN){} // While the flag is down, once flag is raised exit loop
    // Flag would be raised in hardware here.
    T2CONbits.TON = 0; // Timer off
    IFS0bits.T2IF = FLAG_DOWN; //Flag Down


    //TODO: Using timer 2, create a delay
    // that is delay amount of us.
    return;
}