/*
 * File:   timer.c
 * Authors: Brandon Lipjanic, Jonny Hawkins, Abigail Francis, Pierce Simpson
 * Team 203
 */

#include <xc.h>
#include "timer.h"
#include "interrupt.h"

void initTimer1(){
    TMR1 = 0;
    PR1 = 0;
    T1CONbits.TCKPS = 0;
    T1CONbits.TCS = 0;
    T1CONbits.ON = 1;
}

void initTimer3(){
    TMR3 = 0;
    PR3 = 1023;
    T3CONbits.TCKPS = 0;
    T3CONbits.TCS = 0;
    T3CONbits.ON = 1;    
}

//Uses timer 2
/*void delayUs(unsigned int delay){
    TMR1 = 0;
    PR1 = 5*delay;
    IFS0bits.T2IF = 0;
    T1CONbits.TCKPS = 1;
    disableInterrupts();
    T1CONbits.TON = 1;
    while(IFS0bits.T1IF == 0);
    T1CONbits.TON = 0;
    enableInterrupts();
}*/

void delayUs(long int delay){
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