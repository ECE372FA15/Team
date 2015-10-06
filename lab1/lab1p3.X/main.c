
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
#include <stdint.h>
#include "leds.h"
#include "interrupt.h"
#include "switch.h"
#include "timer.h"
#include "config.h"

#define DBdelayTime 500
#define runLED 0
#define stopLED 1
#define PRESSED 0
#define RELEASED 1

#define test
// state machine definitions 
typedef enum stateTypeEnum{
    dBPress, waitRelease, dBRelease, stoppedWaitForPress, runningWaitForPress
} stateType;

//global varables declared to work in ISRs 
volatile stateType state = runningWaitForPress; 
volatile uint64_t timeCountInHundredthsOfASecond = 0; 
unsigned int dummyVariable = 0;

#ifdef mainFunction
int main(void)
{
    //Initialize new interrupt fix
    SYSTEMConfigPerformance(40000000);

   // initialize the project components 
   initSW(); 
   initLED(runLED);
   initLED(stopLED);
   initTimer2();
   enableInterrupts();
   turnOffLED(stopLED);
   turnOnLED(runLED);
   
   
   // infinite loop 
    while(1){
        
        switch(state){
            // the state that toggles the LEDs 
            case stoppedWaitForPress:
                turnOnLED(runLED);
                turnOffLED(stopLED);
                while(state == stoppedWaitForPress){
                    if(PORTDbits.RD6 == PRESSED){     //CN Flag is high should be the condition?
                        timeCountInHundredthsOfASecond = 0; //should this be done in the ISR?
                    }
                }
                break;
                
            // wait for user input i.e. button press
            case runningWaitForPress:
                turnOnLED(stopLED);
                turnOffLED(runLED);
                break;
                
            // once the button has been pressed 
            case dBPress:
                
                delayUs(DBdelayTime); // Delay for 5ms
              
                while(state == dBPress );
               
                break;
            
            // once the button has been released 
            case dBRelease:
                 
                delayUs(DBdelayTime); //Delay for 5ms

                while(state == dBRelease);
                 
                break;
        } 
    }

    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL6SRS) _CNInterrupt(void){

    dummyVariable = PORTAbits.RA7 = 1;//Put the CN flag down
    IFS1bits.CNAIF = 0;

   if(state == dBRelease){
        // if the run led is on 
        if(TRISGbits.TRISG12 == 1){
            state = stoppedWaitForPress; // goto stopped 
        }
        else{
            state = runningWaitForPress; // advance to go 
        }
    }
    else if(state == dBPress){               
        //Going from dbPress to dbRelease
        state = dBRelease; 
    }
    else {
        state = dBPress;
    }
}
//time timer that should go off every 1/100 th of a second 
void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt(void){
    
    // set the flag down 
    IFS0bits.T1IF = 0;
   // dummyVariable = PORTAbits.RA7 = 1;//Put the CN flag down
    
      // if the run led is on 
       if(state == runningWaitForPress){
            // increment the timer 
            timeCountInHundredthsOfASecond ++ ;
            // display running message and time 
           writeRunning(timeCountInHundredthsOfASecond); 
       }
       else{
           // display stopped message and time 
           writeStopped(timeCountInHundredthsOfASecond);
       }
}

#endif

#ifdef test

int main(void){

    //Initialize new interrupt fix
    SYSTEMConfigPerformance(40000000);
    
   // initialize the project components 
   initSW(); 
   
   initLCD();
   clearLCD();
   
   initLED(runLED);
   initLED(stopLED);
   initTimer2();
   enableInterrupts();
   turnOffLED(stopLED);
   turnOnLED(runLED);
   while (1)
   {
      testPrintTimeLCD();
   }
   
}

#endif