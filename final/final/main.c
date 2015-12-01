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
#include "HC_SR04.h"

#include "ir.h"

#define TEST_SENSOR

#ifndef STATETYPE_
#define STATETYPE_

typedef enum stateTypeEnum{
    trackLines, attackBot, snooze
} stateType;
#endif // STATETYPE_

volatile stateType mainState; 
#ifdef RUN

int main(void){

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
    int *count = 0;
    while(1){   
//        
//    testIR(); 
////     testMotorAndIR();
      
        switch(mainState){
            case trackLines: 
               // analogPrintIR(); 
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
#endif
/*void __ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt(void){
    IFS0bits.AD1IF = 0;
    OC2RS = ADC1BUF0;
}*/


#ifdef TEST_SENSOR
int main (void){
     SYSTEMConfigPerformance(40000000);
     int Distance = 0;
     char Dist [3];
     
     int i = 0;
    initTimer3();
    initTimer1();
    initLCD();
    clearLCD();
    writeLCD(0b00001111, 0, 50);
    disableInterrupts();
    printStringLCD("Test");
    
    while(1){
    
    Distance = FindDistance();
    sprintf(Dist, "%d", Distance);
    printStringLCD(Dist);
    printStringLCD("in");
    for(i=0; i < 1000 ; i++){
        
    
    delayUs(1000);
    }
    
    clearLCD();
   
    }
     return 0;
}
#endif