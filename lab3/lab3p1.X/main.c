
#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "interrupt.h"
#include "timer.h"
#include "pwm.h"
#include "adc.h"
#include "lcd.h"
#include "motor.h"

volatile int ADCBufferValue;


int main(void){
    SYSTEMConfigPerformance(40000000);

    initTimer1();
    initTimer3();
    initPWM();
    initADC();
    initLCD();
    clearLCD();
    writeLCD(0b00001111, 0, 50);
  //  enableInterrupts();
    disableInterrupts(); 
    
    while(1){
        clearLCD(); 
        
        IFS0bits.AD1IF = 0;            // reset adc thing 
         while(AD1CON1bits.SSRC == 0 );
       
         ADCBufferValue = ADC1BUF0;      // get buffer value 
         printVoltage(ADCBufferValue);
         delayUs(100000);               // wait one second 
         leftMotorForward(50);
         delayUs(100000);               // wait one second 
         delayUs(100000);               // wait one second 
         rightMotorForward(50);
         delayUs(100000);               // wait one second 
         
         
        
    }
    
    return 0;
}

//void __ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt(void){
//    disableInterrupts();
//    IFS0bits.AD1IF = 0;
//    ADCBufferValue = ADC1BUF0;
//}

