
#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "interrupt.h"
#include "timer.h"
#include "pwm.h"
#include "adc.h"
#include "lcd.h"

int main(void){
    SYSTEMConfigPerformance(40000000);
    ANSELE = 0;
    initTimer1();
    initPWM();
    initADC();
    initLCD();
    enableInterrupts();
    
    while(1){
        printCharLCD('a');
    }
    
    
    long int ADCValue = 0;
    TRISBbits.TRISB5 = 1;
 
   
         ANSELB = 0x0020;
         AD1CON1 = 0x0004; // ASAM bit = 1 implies acquisition ..
                             // starts immediately after last
                             // conversion is done
         AD1CHS = 0x00050000; // Connect RB50/AN5 as CH0 input ..
                                 // in this example RB7/AN7 is the input
         AD1CSSL = 0;
         AD1CON3 = 0x0002;          // Sample time manual, Tad = internal 6 TPB
         AD1CON2 = 0;
         AD1CON1SET = 0x8000;        // turn ADC ON
         while (1)              // repeat continuously
         {
         delayUs(65000);           // sample for 100 mS
         AD1CON1SET = 0x0002;           // start Converting
         while (!(AD1CON1 & 0x0001));           // conversion done?
         ADCValue = ADC1BUF0;           // yes then get ADC value
         printVoltage(ADCValue);
         }
    
    return 0;
}

void __ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt(void){
    IFS0bits.AD1IF = 0;
    OC2RS = ADC1BUF0;
}