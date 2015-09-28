
// File:         main.c
// Date:         9/24/2015
// Authors:      Brandon Lipjanic
//               Jonathan Hawkins
//               Abigail Francis
//               Pierce Simpson
//
// Description: Part 1 for lab 1
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "leds.h"
#include "interrupt.h"
#include "switch.h"
#include "timer.h"
#include "config.h"
#define run
#define DBdelayTime 500

//#define test 

//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    runToggle, dbPress, dbRelease, waitForPress
} stateType;

//TODO: Use volatile variables that change within interrupts
volatile stateType state = runToggle; 
volatile stateType prevState = runToggle;
unsigned int dummyVariable = 0;

int main(void)
{
    //Initialize new interrupt fix
    SYSTEMConfigPerformance(40000000);
    
#ifdef test
   initSW(); 
   initLED(RUN_LED);
   initLED(STOP_LED);
   initTimer2();
   enableInterrupts();
   
   turnOnLED(1); //Turn on the RunLED
   turnOffLED(2);

   // continusuly toggle LED's 
    while (1){
       delayUs(10000000);  toggleAllLEDs();
    }
#endif
   
#ifdef run
   initSW(); 
   initLED(RUN_LED);
   initLED(STOP_LED);
   initTimer2();
   enableInterrupts();
   
   // initialize the lights         
   state = runToggle; 
   turnOffLED(STOP_LED);
   turnOnLED(RUN_LED);
   
    while(1){
        
        switch(state){
            case runToggle:
                
                toggleAllLEDs();
                prevState = runToggle;
                
                state = waitForPress; //Go to debounce press state
                break;
                
            case waitForPress:
                
                while (state == waitForPress);
                
                break;
                
            case dbPress:
                
                delayUs(DBdelayTime); // Delay for 5ms
              
                while(state == dbPress );
               
                break;
                
            case dbRelease:
                
                delayUs(DBdelayTime); //Delay for 5ms

                 state = runToggle;
                 
                break;
        } 
    }
#endif
    return 0;
}

//void __ISR(_CHANGE_NOTICE_VECTOR, IPL3SRS) _CNInterrupt(void){
void __ISR(_CHANGE_NOTICE_VECTOR, IPL6SRS) _CNInterrupt(void){

    dummyVariable = PORTAbits.RA7 = 1;//Put the CN flag down
  //  dummyVariable = PORTDbits.RD6 = 1;//Put the CN flag down
    IFS1bits.CNAIF = 0;
    
    if((state == runToggle)){
        state = waitForPress; //runOn OR stopOn into waitForPress
    }
    else if(state == waitForPress){
        
        state = dbPress; //Going from waitForPress to dbPress
    }
    else{               
        state = dbRelease; //Going from dbPress to dbRelease
    }
    //Change state from dbRelease into runOn or stopOn in the switch statement.

}