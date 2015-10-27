
#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "interrupt.h"
#include "timer.h"
#include "pwm.h"
#include "adc.h"
#include "lcd.h"
volatile int ADCBufferValue;
int main(void){
    SYSTEMConfigPerformance(40000000);

   
    initTimer1();
    initPWM();
    initADC();
    initLCD();
    clearLCD();
    writeLCD(0b00001111, 0, 50);
    enableInterrupts();

    while(1){
        enableInterrupts();
         if(IFS0bits.AD1IF == 1){  // Poll for a change in the ADC value
             
             IFS0bits.AD1IF = 0;
            
            printVoltage(ADCBufferValue);
            printCharLCD('_');
            delayUs(65000);
            delayUs(65000);
            delayUs(65000);
            delayUs(65000);
            delayUs(65000);
            delayUs(65000);
    }
    }
    
    return 0;
}

void __ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt(void){
    disableInterrupts();
    IFS0bits.AD1IF = 0;
    ADCBufferValue = ADC1BUF0;
}