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

int main(void){
    SYSTEMConfigPerformance(40000000);
    
    initTimer3();
    initTimer1();
    initLCD();
    clearLCD();
    writeLCD(0b00001111, 0, 50);
    initPWM();
    initADC();
  //  enableInterrupts();
    disableInterrupts();
   // TRISBbits.TRISB13 = 0;
    while(1){   
  
       
         IFS0bits.AD1IF = 0;            // reset adc thing 
         while(AD1CON1bits.SSRC == 0 );
       
         if(ADC1BUF0 < 256){            //Backwards
            OC2RS = 0; // left forward
            OC4RS = ADC1BUF0*4; // left backwards

            OC1RS = 0; //Right Forwards
            OC3RS = ADC1BUF0*4; // Right Backwards
         }
         else if (ADC1BUF0 < 512){      //CounterClockwise
            OC2RS = 0; // left forward
            OC4RS = ADC1BUF0*2; // left backwards

            OC1RS = ADC1BUF0*2; //Right Forwards
            OC3RS = 0; // Right Backwards
         }
         else if (ADC1BUF0 >= 768 && ADC1BUF0 < 1024){      //Right
            OC2RS = (ADC1BUF0*3)/2; // left forward
            OC4RS = 0; // left backwards

            OC1RS = 0; //Right Forwards
            OC3RS = (ADC1BUF0*3)/2; // Right Backwards    
         }
         else {                  //Forwards
            OC2RS = ADC1BUF0; // left forward
            OC4RS = 0; // left backwards

            OC1RS = ADC1BUF0; //Right Forwards
            OC3RS = 0; // Right Backwards 
         }
         printVoltage(ADC1BUF0);
         
 
    }
    
    return 0;
}

/*void __ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt(void){
    IFS0bits.AD1IF = 0;
    OC2RS = ADC1BUF0;
}*/