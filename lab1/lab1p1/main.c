
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
#define part1
#define DBdelayTime 500


typedef enum stateTypeEnum{
    runToggle, dbPress, dbRelease, waitForPress
} stateType;

volatile stateType state = runToggle; 
volatile stateType prevState = runToggle;
unsigned int dummyVariable = 0;

int main(void)
{
    //Initialize new interrupt fix
    SYSTEMConfigPerformance(40000000);
    
   
#ifdef part1
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
            // the state that toggles the LEDs 
            case runToggle:
                // switch the led's
                toggleAllLEDs();
                prevState = runToggle;
                
                state = waitForPress; //Go to debounce press state
                break;
                
            // wait for user input i.e. button press
            case waitForPress:
                
                while (state == waitForPress);
                
                break;
                
            // once the button has been pressed 
            case dbPress:
                
                delayUs(DBdelayTime); // Delay for 5ms
              
                while(state == dbPress );
               
                break;
            
            // once the button has been released 
            case dbRelease:
                
                delayUs(DBdelayTime); //Delay for 5ms

                 state = runToggle;
                 
                break;
        } 
    }
#endif
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL6SRS) _CNInterrupt(void){

    dummyVariable = PORTAbits.RA7 = 1;//Put the CN flag down
    IFS1bits.CNAIF = 0;
    
    if((state == runToggle)){
        //runOn OR stopOn into waitForPress
        state = waitForPress; 
    }
    else if(state == waitForPress){
        //Going from waitForPress to dbPress
        state = dbPress; 
    }
    else{               
        //Going from dbPress to dbRelease
        state = dbRelease; 
    }
}