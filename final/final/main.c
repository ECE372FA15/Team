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

#include "ir.h"

#ifndef STATETYPE_
#define STATETYPE_

typedef enum stateTypeEnum{
    trackLines, attackBot, snooze
} stateType;
#endif // STATETYPE_

volatile stateType mainState; 

int main(void){
    
    int i = 0;
    SYSTEMConfigPerformance(40000000);
    // initialize 
    mainState = trackLines;
    initTimer3();
    initTimer1();
    initLCD();
    clearLCD();
    writeLCD(0b00001111, 0, 50);
    initPWM();
    //initADC();
    initIR(); 
    disableInterrupts();
    while(1){   
        
////    testIR(); 
//      testMotorAndIR();
      
        switch(mainState){
            case trackLines: 
                    trackLine(); 
                break;
            case attackBot:
                break;
            case snooze:
                break;
        }
        
        
    }
    
    return 0;
}

/*void __ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt(void){
    IFS0bits.AD1IF = 0;
    OC2RS = ADC1BUF0;
}*/