// ******************************************************************************************* //
// File:         main.c
// Date:         
// Authors:      
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include <string.h>
#include "lcd.h"
#include "timer.h"
#include "keypad.h"
#include "config.h"
#include "interrupt.h"
#include "variableDefs.h"
#define run

#define nump = 10;
#define lenp = 4; 

//#define TEST

typedef enum stateTypeEnum{
   scanKey, printKey, dbPress, dbRelease, waitForPress, waitForRelease, firstStar,
           dispGood, dispBad, dispEnter, dispValid, dispInvalid, dispMode
} stateType;

volatile stateType modeState = dispEnter; 
volatile stateType state = waitForPress;
volatile int dummyVariable = 0;
volatile int keyScanned = -1;

int main(void)
{
    char passWord[10][5] ; //[nump][lenp]; 
    char temp[6];
    int pwItt = 0; 
    int pwStoreIndex = 0; 
    int numCharsPrinted = 0; 
    int newKeyPressed = 1;
    ANSELE = 0;
    SYSTEMConfigPerformance(40000000);
    initLCD();
    clearLCD();
    writeLCD(0b00001111, 0, 50);
    initTimer1();
    initKeypad();
    //enableInterrupts();
    
    strcmp(passWord[1], temp);
    
#ifdef run  
    while(1){
        
   //<><><><>  button de bounce stuff  <><><><><><><><><><><><><><><><><><><><><><>        
        switch(state){

            
           case dispGood:
               printOutput("Good    ");
                break;
           case dispBad:
               printOutput("Bad     ");
                break;
           case dispEnter:
               clearLCD();
               printStringLCD("Enter   ");
               state = waitForPress;
                break;
           case dispValid://-
               printOutput("Valid   "); 
                break;
           case dispInvalid://-
               printOutput("Invalid "); 
                break;
           case dispMode://-
               printOutput("Set Mode"); 
               clearLCD();
               state = dispValid; 
               break;
            case printKey:
                newKeyPressed = 1; 
                temp[pwItt] = (char)keyScanned; 
                pwItt++;
                state = waitForRelease; 
            break;
            case scanKey:
                keyScanned  = scanKeypad(); 
                state = printKey;
            break;
            
            case dbPress:   
                delayUs(DBDelayTime);
                state = scanKey;
            break;
            
            case dbRelease:
                delayUs(DBDelayTime);
                state = waitForPress;
            break;
            
            case waitForPress:
               // while(state = waitForPress);        //This state will change in the ISR when the keypad is pressed.
               // while(state == waitForPress);        //This state will change in the ISR when the keypad is pressed.
            break;
            
            case waitForRelease:
                enableInterrupts(); 
                //while(state = waitForRelease);      //This state will change in the ISR when the keypad is released.
                //while(state == waitForRelease);      //This state will change in the ISR when the keypad is released.
            break;    
        }
//<><><><> END button de bounce stuff  <><><><><><><><><><><><><><><><><><><><><><>  
        
        
//<><><><>  Mode setting state machine <><><><><><><><><><><><><><><><><><><><><><>       
    if(newKeyPressed == 1){
            newKeyPressed = 0; 
        // the newKeyPressed variable gets changed to 1 everytime a key press is detected    
        switch(modeState){
           case firstStar:
               
               
                break; 
           case dispGood:
               printOutput("Good");
                break;
           case dispBad:
               printOutput("Bad");
                break;
           case dispEnter:
               clearLCD();
               printStringLCD("Enter");
               
               modeState = 1;
                break;
           case dispValid://-
               printOutput("Valid   "); 
                break;
           case dispInvalid://-
               printOutput("Invalid "); 
                break;
           case dispMode://-
               clearLCD()
               printStringLCD("Set Mode"); 
               
               
               
               modeState = dispValid; 
               modeState = dispInvalid; 
                break;   
        }   
        }
//<><><><> END Mode setting state machine <><><><><><><><><><><><><><><><><><><><><><>   
        
    }
    
    return 0;
}
#endif

#ifdef TEST

while(1) jTestKeypad();
return 0;
}
#endif

#ifdef run
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
    
    disableInterrupts(); 
    
    dummyVariable = PORTEbits.RE3 = 1;
    dummyVariable = PORTEbits.RE7 = 1;
    dummyVariable = PORTDbits.RD5 = 1;
    
    IFS1bits.CNEIF = 0; //Put the CN flag down
    IFS1bits.CNDIF = 0;
    
    if(state == waitForPress){
        disableInterrupts();
        state = dbPress;
        return; 
    }
    
    if(state == waitForRelease){
        state = dbRelease; 
        enableInterrupts(); 
        return; 
    }
    
    enableInterrupts(); 
}
#endif

