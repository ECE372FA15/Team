// ******************************************************************************************* //
//
// File:         lab1p1.c
// Date:         
// Authors:      
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
    runOn, stopOn, dbPress, dbRelease
} stateType;

//TODO: Use volatile variables that change within interrupts
volatile stateType state = runOn; 

int main(void)
{
   // intitsw(); 
    
    
    while(1)
    {
        //TODO: Using a finite-state machine, define the behavior of the LEDs
        //Debounce the switch
    }
    
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL3SRS) _CNInterrupt(void){
    //TODO: Implement the interrupt to capture the press of the button

}