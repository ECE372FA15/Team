// ******************************************************************************************* //
// File:         main.c
// Date:         
// Authors:      
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "keypad.h"
#include "config.h"
#include "interrupt.h"

#define run
//#define TEST

typedef enum stateTypeEnum{
   scanKey, printKey, dbPress, dbRelease, waitForPress, waitForRelease
} stateType;

volatile stateType state = waitForPress;
volatile int dummyVariable = 0;

int main(void)
{
    int keyScanned = -1;
    
    ANSELE = 0;
    SYSTEMConfigPerformance(40000000);
    enableInterrupts();
    initLCD();
    clearLCD();
    initTimer1();
    writeLCD(0b00001111, 0, 50);

#ifdef run  
    while(1){
        switch(state){
            case printKey:
                
                if((keyScanned > -1) && (keyScanned < 10)){
                    printCharLCD(keyScanned + '0'); 
                }
                else if (keyScanned == 42){
                    printCharLCD('*');
                }
                else if (keyScanned == 35){
                    printCharLCD('#');
                }
                else{
                    //Do not print to LCD, potentially clear LCD.
                }
                
                
                // Still need to set up moving the cursor after each print, I want 
                // to test if it will print in the first spot on the LCD before
                // trying to implement this however
            break;
            
            case scanKey:
                //Disable CN interrupts
                keyScanned = scanKeypad();
                //Enable CN interrupts
            break;
            
            case dbPress:   
                delayUs(DBDelayTime);
                state = waitForRelease;
            break;
            
            case dbRelease:
                delayUs(DBDelayTime);
                state = printKey;
            break;
            
            case waitForPress:
                while(state = waitForPress);        //This state will change in the ISR when the keypad is pressed.
            break;
            
            case waitForRelease:
                while(state = waitForRelease);      //This state will change in the ISR when the keypad is released.
            break;
            
        }
    }
    
    return 0;
}
#endif

#ifdef TEST

while(1) testKeypad();

#endif

void __ISR(_CHANGE_NOTICE_VECTOR, IPL6SRS) _CNInterrupt(void){
    dummyVariable = PORTAbits.RA7 = 1;
    IFS1bits.CNAIF = 0; //Put the CN flag down
    
    if(state == waitForPress){
        state = dbPress;
    }
    else{
        state = dbRelease;
    }
}