
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
    ANSELA = 0;
    ANSELC = 0;
    ANSELD = 0;
    ANSELE = 0;
    ANSELF = 0;
    ANSELG = 0;
   
    initTimer1();
    initPWM();
    initADC();
    initLCD();
    clearLCD();
    writeLCD(0b00001111, 0, 50);
    enableInterrupts();
    printCharLCD('a');
    
  // while(1){
    //    printCharLCD('a');
    //}
    
    
    long int ADCValue = 0;
    TRISBbits.TRISB5 = 1;
 
 
         ANSELB = 0x0020;
         AD1CON1 = 0x0000; // ASAM bit = 1 implies acquisition ..
                             // starts immediately after last
                             // conversion is done
         AD1CHS = 0x00050000; // Connect RB50/AN5 as CH0 input ..
         printCharLCD('b');                        // in this example RB7/AN7 is the input
         AD1CSSL = 0;
         AD1CON3 = 0x0002;          // Sample time manual, Tad = internal 6 TPB
         AD1CON2 = 0;
         printCharLCD('c');
         AD1CON1SET = 0x8000;        // turn ADC ON
         printCharLCD('d');
         while (1)              // repeat continuously
         {
             AD1CON1SET = 0x0002;
             printCharLCD('m');
             delayUs(65000);
             delayUs(35000);        // start Converting
             printCharLCD('x');
             AD1CON1CLR = 0x0002;
             printCharLCD('o');
         while (!(AD1CON1 & 0x0001));   
         printCharLCD('p');             // conversion done?
         ADCValue = ADC1BUF0;           // yes then get ADC value
         printVoltage(ADCValue);
         printCharLCD('g');
         }
    
    return 0;
}

void __ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt(void){
    IFS0bits.AD1IF = 0;
 
}