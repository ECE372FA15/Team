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
#include "test.h"

#define switchVal   PORTEbits.RE1
#define ADCDone     AD1CON1bits.SSRC
#define ADCFlag     IFS0bits.AD1IF
#define timerFlag   IFS0bits.T1IF
#define timerOn     T1CONbits.TON
#define fwd         0
#define bck         1
#define IDLEBACK    2
#define IDLEFWD     3
#define TEST
//#define RUN

typedef enum stateTypeEnum{
    forward, backward, debouncePress, debounceRelease, idleFwd, idleBack
} stateType;

    volatile  stateType state = idleBack;       // State the state machine in idleBack so that when the switch is pressed it goes into Forward
    volatile int direction = 0;         //Used to determine which state to go to next inside the debounce release state


int main(void){
    
    SYSTEMConfigPerformance(40000000);
  
    int direction = 0; // 0 = forward 1 =backwards 
    initTimer3();
    initTimer1();
    initSwitch1();
    initLCD();
    clearLCD();
    writeLCD(0b00001111, 0, 50);
    initPWM();
    initADC();

    disableInterrupts();
   
    
    
    
    direction = 0;
    ADCFlag = 0;            // reset adc thing 
    while(ADCDone == 0 ); //Wait for ADC Value 
    setMotorsSweepForward(ADC1BUF0);
    
#ifdef TEST
    test();
#endif    
    
#ifdef RUN    
    while(1){   
  
         switch(state){
             
             case forward:
                 
                 direction = fwd;
              
                 while(switchVal == 1){ //Wait for Press
                     ADCFlag = 0;            // reset adc thing 
                     while(ADCDone == 0 );
                     setMotorsSweepForward(ADC1BUF0);
                 } 
                 state = debouncePress;
                 TMR1 = 0;
                 timerFlag = 0;
                 timerOn = 1;
                 break;
             
             case backward:
                 
                 direction = bck;
                 while(switchVal == 1){ //Wait for Press
                     ADCFlag = 0;            // reset adc thing 
                     while(ADCDone == 0 );
                     setMotorsSweepBackward(ADC1BUF0);
                 } 
                 state = debouncePress;
                 TMR1 = 0;
                 timerFlag = 0;
                 timerOn = 1;
                 break;
             case idleBack:
                 
                 direction = IDLEBACK;
                 while(switchVal == 1){ //Wait for Press
                     ADCFlag = 0;            // reset adc thing 
                     while(ADCDone == 0 );
                     setMotorsIdle();
                 } //wait for press
                 state = debouncePress;
                 TMR1 = 0;
                 timerFlag = 0;
                 timerOn = 1;
                 break;
                 
            case idleFwd:
                 
                 direction = IDLEFWD;
                 while(switchVal == 1){ //Wait for Press
                     ADCFlag = 0;            // reset adc thing 
                     while(ADCDone == 0 );
                     setMotorsIdle();
                 } //wait for press
                 state = debouncePress;
                 TMR1 = 0;
                 timerFlag = 0;
                 timerOn = 1;
                 break;
                 
               
             case debouncePress:
                 
                 delayUs(100);
                 while(switchVal == 0); //wait for release
                 state = debounceRelease;
                 break;
                 
             case debounceRelease:
                 delayUs(100);
                 
                 // Determine the next state based on the value of direction.
                 if(direction == fwd){          
                     state = idleFwd;
                 }
                 else if(direction == bck){
                     state = idleBack;
                 }
                 else if(direction == IDLEBACK){
                     state = forward;
                 }
                 else{
                     state = backward;
                 }
                 
             
             
         }

    }
#endif
    return 0;
}

