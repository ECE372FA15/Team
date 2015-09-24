
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



//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    runOn, stopOn, dbPress, dbRelease, waitForPress
} stateType;

//TODO: Use volatile variables that change within interrupts
volatile stateType state = runOn; 
unsigned int dummyVariable = 0;

int main(void)
{
    //Initialize new interrupt fix
    SYSTEMConfigPerformance(40000000);
    
   initSW(); 
   initLED(RUN_LED);
   initLED(STOP_LED);
   initTimer2();
   enableInterrupts();

    
    while(1){
        
        switch(state){
            case runOn:
                turnOnLED(RUN_LED); //Turn on the RunLED
       
                
                state = waitForPress; //Go to debounce press state
                break;
                
            case stopOn:
                turnOnLED(STOP_LED); //Turn on the StopLED
             
                
                state = waitForPress; //Go to debounce press state
                break;
                
            case waitForPress:
                while(IFS1bits.CNDIF == FLAG_DOWN); //Wait for button press to enable CN flag
                IFS1bits.CNDIF == FLAG_DOWN; //Put the CN flag down
                
                break;
                
            case dbPress:
                delayUs(5000); // Delay for 5ms
                while(IFS1bits.CNDIF == FLAG_DOWN); //Wait for button to be released
                IFS1bits.CNDIF == FLAG_DOWN; //Put the CN flag down
                TMR2 = 0;   //Reset Timer2
                break;
                
            case dbRelease:
                delayUs(5000); //Delay for 5ms
                
                if(state == runOn){ //Previous State was runOn
                    state = stopOn;
                }
                
                else{                // Previous State was stopOn
                    state = runOn;
                }
                TMR2 = 0;   //Reset Timer2
                break;
        } 
    }
    
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL3SRS) _CNInterrupt(void){
    //TODO: Implement the interrupt to capture the press of the button
    dummyVariable = PORTDbits.RD6; //Read a value from PORTDbits because Vanhoy said so
    IFS1bits.CNDIF = FLAG_DOWN; //Put the CN flag down
    if((state == runOn) || (state == stopOn)){
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