 /* 
 * File: main.c
 * Authors: Brandon Lipjanic, Jonny Hawkins, Abigail Francis, Pierce Simpson
 * Team 203
 */
#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "interrupt.h"
#include "timer.h"
#include "pwm.h"
#include "adc.h"

#ifndef STATETYPE_
#define STATETYPE_
typedef enum stateTypeEnum{
    runToggle, dbPress, dbRelease, waitForPress
} stateType;
#endif // STATETYPE_

int main(void){
    
    SYSTEMConfigPerformance(40000000);
    // initialize 
    initTimer3();
    initTimer1();
    initLCD();
    clearLCD();
    writeLCD(0b00001111, 0, 50);
    initPWM();
    initADC();
    disableInterrupts();
    
    while(1){   
        
        
        
    }
    
    return 0;
}

/*void __ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt(void){
    IFS0bits.AD1IF = 0;
    OC2RS = ADC1BUF0;
}*/