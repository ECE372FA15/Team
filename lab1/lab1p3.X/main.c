
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

#define DBdelayTime 1000
#define runLED 0
#define stopLED 1
#define PRESSED 0
#define RELEASED 1

#define mainFunction
// state machine definitions 
#ifdef mainFunction
typedef enum stateTypeEnum{
    dBPress, waitRelease, dBRelease, stoppedWaitForPress, runningWaitForPress
} stateType;

//global varables declared to work in ISRs 
volatile stateType state = runningWaitForPress; 
volatile int t = 0; 
volatile uint64_t timeCountInHundredthsOfASecond = 0; 
unsigned int dummyVariable = 0;


int main(void)
{
    ANSELE = 0;
    //Initialize new interrupt fix
    SYSTEMConfigPerformance(80000000);

   // initialize the project components 
   //initSW(); 
   initT1();       
   initTimer2();
   initLCD();
   clearLCD();
   writeLCD(0b00001111, 0, 50);
   initLED(1);
   initLED(0);
   enableInterrupts();
   TRISGbits.TRISG12 = 1;     
   TRISGbits.TRISG14 = 0;  
   TRISDbits.TRISD5 = 0;
   // infinite loop 
    while(1){
        
        
        switch(state){
            // the state that toggles the LEDs 
            case stoppedWaitForPress:
                LATGbits.LATG12 = 1;
                LATGbits.LATG14 = 0;
                t = 1;
                while(state == stoppedWaitForPress){
                    if(PORTDbits.RD6 == 0){     //CN Flag is high should be the condition?
                        timeCountInHundredthsOfASecond = 0; //should this be done in the ISR?
                    }
                    if (IFS1bits.CNAIF == 1){
                        int a = 0;
                    }
                }
                break;
                
            // wait for user input i.e. button press
            case runningWaitForPress:
                LATGbits.LATG12 = 0;
                LATGbits.LATG14 = 1;
                t = 0; 
                while (state == runningWaitForPress);
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

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){

    dummyVariable = PORTAbits.RA7 = 1;//Put the CN flag down
    IFS1bits.CNAIF = 0;
    
   if(state == dBRelease){
        // if the run led is on 
        if(t == 0){//LATGbits.LATG12 == 0){
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
    LATDbits.LATD5 = !LATDbits.LATD5;
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
    TMR1 = 0;
    //T1CONbits.ON = 1;
    
}

#endif

#ifdef test

int main(void){
ANSELE = 0;
    //Initialize new interrupt fix
    SYSTEMConfigPerformance(40000000);
    
   // initialize the project components 
   initSW(); 
   
   initLCD();
   clearLCD();
   writeLCD(0b00001111, 0, 50);
   //initLED(runLED);
   //initLED(stopLED);
   initTimer2();
   enableInterrupts();
   //turnOffLED(stopLED);
   //turnOnLED(runLED);
   testPrintTimeLCD();
   
}

#endif