
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
#define FCY 96000000
#define SCALAR .000001
#define PRE_SCALAR 1

//Uses timer 2

void initTimer2(){

    TMR2 = 0; //reset timer register
    T2CONbits.TCS = DISABLE; // Enable Internal peripheral clock
    T2CONbits.TCKPS = 0b000; //Prescalar of 8
    IFS0bits.T2IF = FLAG_DOWN;  //Interrupt Flag Down
    long int prVal = (((FCY*SCALAR)/PRE_SCALAR) - 1.0); //Calculate the PR value using delay as the time, converted to ms.
   
    PR2 = 1;

    return;
}
void delay50Us(){
    int i = 0;
    for(i = 0; i < 5; i++){
        delay9Us(); 
    }
}
void delay9Us(){
    
    PR2 = 18;
        
    TMR2 = 0;   //reset timer 2 register
    IFS0bits.T2IF = FLAG_DOWN; // Flag Down
    T2CONbits.TON = 1; //Timer on
    
    while(IFS0bits.T2IF == FLAG_DOWN){} // While the flag is down, once flag is raised exit loop
    // Flag would be raised in hardware here.
    T2CONbits.TON = 0; // Timer off
    IFS0bits.T2IF = FLAG_DOWN; //Flag Down
}

void delayUs(int delay){
    int i = 0;
    i+=1;i-=1;i+=1;i-=1;i+=1;i-=1;i+=1;i-=1;
    i+=1;i-=1;i+=1;i-=1;i+=1;
    
    int stop = delay/9 -1 ;
    for (i = 0; i < stop; i++){
        delay9Us();
    }

}

void delayMs(float delay){
    int i = 0;
    int stop = delay * 20 - 1;
    for( i = 0; i < stop; i++){
        delay50Us();
    }
}