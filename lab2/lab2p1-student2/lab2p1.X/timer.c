/*
 * File:   timer.c
 * Author: gvanhoy
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"

void initTimer1(){
    TMR1 = 0;                  //t1 reg reset
    PR1 = 1;                   //set Period value
    T1CONbits.TCKPS = 0b00;    //prescaler value1:8
    T1CONbits.TCS = 0;         //internal peripheral clock
    IFS0bits.T1IF = 0;         //flag down
    T1CONbits.ON = 0;          //t1 on 
}
//Uses timer 2
void delayUs(int delay){
    int stop = delay - 1;
    int i = 0;
     PR1 = 21; 
    T1CONbits.ON = 1;           //start timer
    for ( i = 0; i < stop; i++){
    while (IFS0bits.T1IF == 0); //wait for timer to terminate
    IFS0bits.T1IF = 0;          //put flag down
    TMR1 = 0;
    }
    T1CONbits.ON = 0;           //turn off timer    
    IFS0bits.T1IF = 0;          //
    TMR1 = 0;
    
}

void delay1pt5Us(){
    PR1 = 1; 
    T1CONbits.ON = 1;           //start timer
    while (IFS0bits.T1IF == 0); //wait for timer to terminate
    T1CONbits.ON = 0;           //turn off timer    
    IFS0bits.T1IF = 0;          //
    TMR1 = 0;
}