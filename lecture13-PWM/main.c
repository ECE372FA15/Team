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

#define switchVal   PORTEbits.RE1
#define ADCDone     AD1CON1bits.SSRC
#define ADCFlag     IFS0bits.AD1IF
#define timerFlag   IFS0bits.T1IF
#define timerOn     T1CONbits.TON
#define fwd         0
#define bck         1

typedef enum stateTypeEnum{
    forward, backward, debouncePress, debounceRelease
} stateType;

    volatile  stateType state = forward;
    volatile int direction = 0;


int main(void){
    
    SYSTEMConfigPerformance(40000000);
  //  int latch = 0; 
    int direction = 0; // 0 = forward 1 =backwards 
    initTimer3();
    initTimer1();
    initSwitch1();
    initLCD();
    clearLCD();
    writeLCD(0b00001111, 0, 50);
    initPWM();
    initADC();
  //  enableInterrupts();
    disableInterrupts();
   // TRISBbits.TRISB13 = 0;
    
    
    // initialize robot 
    direction = 0;
    ADCFlag = 0;            // reset adc thing 
    while(ADCDone == 0 );
    setMotorsSweepForward(ADC1BUF0);
    
    while(1){   
  
         switch(state){
             
             case forward:
                 
                 direction = fwd;
              //   printCharLCD(PORTDbits.RD1 + '0');
                 while(switchVal == 1){
                     ADCFlag = 0;            // reset adc thing 
                     while(ADCDone == 0 );
                     setMotorsSweepForward(ADC1BUF0);
                 } // wait for press
                 state = debouncePress;
                 TMR1 = 0;
                 timerFlag = 0;
                 timerOn = 1;
                 break;
             
             case backward:
                 
                 direction = bck;
                 while(switchVal == 1){
                     ADCFlag = 0;            // reset adc thing 
                     while(ADCDone == 0 );
                     setMotorsSweepBackward(ADC1BUF0);
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
                 //delayUs(100);
                 if(direction == fwd){
                     state = backward;
                 }
                 else{
                     state = forward;
                 }
                 
             
             
         }

    }
    return 0;
}

/*void __ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt(void){
    IFS0bits.AD1IF = 0;
    OC2RS = ADC1BUF0;
}*/