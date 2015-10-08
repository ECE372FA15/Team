
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


// state machine definitions 

typedef enum stateTypeEnum{
    dBPress, waitRelease, dBRelease, stoppedWaitForPress, runningWaitForPress
} stateType;

//global varables declared to work in ISRs 
volatile stateType state = runningWaitForPress; //stoppedWaitForPress; 
volatile int latch = 1; 
volatile uint64_t timeCountInHundredthsOfASecond = 0; 
unsigned int dummyVariable = 0;


int main(void)
{
    ANSELE = 0;
    //Initialize new interrupt fix
    SYSTEMConfigPerformance(80000000);

   // initialize the project components 
   initSW(); 
   initT1();       
   initTimer2();
   initLCD();
   clearLCD();
   writeLCD(0b00001111, 0, 50);
   initLED(1);
   initLED(0);
   latch = 1; 
   enableInterrupts(); 

   //TRISDbits.TRISD5 = 1;
   
   // infinite loop 
    while(1){
        
        
        switch(state){/*
            // the state that toggles the LEDs 
            case stoppedWaitForPress:
            //    LATGbits.LATG12 = 1;
            //    LATGbits.LATG14 = 0;
                latch = 1;
                while(state == stoppedWaitForPress){
                    // if button pressed
                    if(PORTAbits.RA6 == 0){ state = dBPress; }
                    
                    if(PORTDbits.RD6 == 0){     //if clear time button pressed
                        timeCountInHundredthsOfASecond = 0; //should this be done in the ISR?
                    }
                }
                break;
                
            // wait for user input i.e. button press
            case runningWaitForPress:
             //   LATGbits.LATG12 = 0;
             //   LATGbits.LATG14 = 1;
                
                latch = 1; 
                // if the switch is pressed 
                while (state == runningWaitForPress){
                    if(PORTAbits.RA6 == 0){ state = dBPress; }
                };
                break;
                
            // once the button has been pressed 
            case dBPress:
                
                delayUs(DBdelayTime); // Delay for 5ms
              
                latch = 1;
                while(state == dBPress );
                break;
            
            // once the button has been released 
            case dBRelease:
                 
                delayUs(DBdelayTime); //Delay for 5ms
                latch = 1; 
                while(state == dBRelease);
                 
                break;
 */
        } 
                       
            
    }
   
    return 0;

}


//void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
//
//    dummyVariable = PORTAbits.RA7 = 1;//Put the CN flag down
//    IFS1bits.CNAIF = 0;
//    
//   if(state == dBRelease){
//        // if the run led is on 
//        if(t == 0){//LATGbits.LATG12 == 0){
//            state = stoppedWaitForPress; // goto stopped 
//        }
//        else{
//            state = runningWaitForPress; // advance to go 
//        }
//    }
//    else if(state == dBPress){               
//        //Going from dbPress to dbRelease
//        state = dBRelease; 
//    }
//    else {
//        state = dBPress;
//    }
//}

//time timer that should go off every 1/100 th of a second 
void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt(void){
    
    latch = PORTAbits.RA6; 
    // set the flag down 
    IFS0bits.T1IF = 0;
   // dummyVariable = PORTAbits.RA7 = 1;//Put the CN flag down
   // LATDbits.LATD5 = !LATDbits.LATD5;
      // if the run led is on 
    
    //<><><><><><><><><><><><><> DISP MESSAGE LOGIC <><><><><><><><><><><><><
//       if(state == runningWaitForPress){
//                LATGbits.LATG12 = 0;
//                LATAbits.LATA7 = 1;
//            // increment the timer 
//            timeCountInHundredthsOfASecond ++ ;
//            // display running message and time 
//           writeRunning(timeCountInHundredthsOfASecond); 
//       }
//       else{
//                LATGbits.LATG12 = 1;
//                LATAbits.LATA7 = 0;
//           // display stopped message and time 
//           writeStopped(timeCountInHundredthsOfASecond);
//       }
    //<><><><><><><><><><><><><> END DISP MESSAGE LOGIC <><><><><><><><><><><><><
    
    //<><><><><><><><><><><><><> CHANGE STATE MACHINE LOGIC <><><><><><><><><><><><><
     //   if(latch == 1){// only allow state changes if prev state has finished task
    //        latch = 0; // reset latch 
             if(state == runningWaitForPress){
                    
                    if(PORTAbits.RA6 == 0){ state = dBPress; }  
                    
                // increment the timer 
                timeCountInHundredthsOfASecond ++ ;
                // display running message and time 
                writeRunning(timeCountInHundredthsOfASecond);                  
            }else if(state == dBRelease){
                // determine the next state based on the led state
                if(LATGbits.LATG12 == 0){
                    state = stoppedWaitForPress; // goto stopped 
                    LATGbits.LATG12 = 1;
                    LATAbits.LATA7 = 0;
                    // display stopped message and time 
                    writeStopped(timeCountInHundredthsOfASecond);
                }
                else{
                    LATGbits.LATG12 = 0;
                    LATAbits.LATA7 = 1;
                    state = runningWaitForPress; // advance to go 
                }
            
            }
            else if(state == dBPress){               
                //Going from dbPress to dbRelease
                // if the button has been released 
                if(PORTAbits.RA6 == 1){//PORTAbits.RA6 == 1){
                    clearLCD(); 
                    state = dBRelease; 
                }
                
            }else if(state == stoppedWaitForPress ){
                    // if the button is pressed                     
                    if(PORTAbits.RA6 == 0){ state = dBPress; } 
                    if(PORTDbits.RD6 == 0){ 
                        timeCountInHundredthsOfASecond = 0;
                        writeStopped(timeCountInHundredthsOfASecond);
                    }
                    
            }
     //            
            
 //           else {
 //               state = dBPress;
 //               latch = 1;
 //           }
 //       }
    //<><><><><><><><><><><><><> END CHANGE STATE MACHINE LOGIC <><><><><><><><><><><><><
    
    // reset the timer 
    TMR1 = 50;
    //T1CONbits.ON = 1;
    
}
