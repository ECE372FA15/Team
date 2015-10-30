/* 
 * File:   pwm.h
 * Authors: Brandon Lipjanic, Jonny Hawkins, Abigail Francis, Pierce Simpson
 * Team 203
 */

#include <xc.h>

#define OCPin0 RPD0Rbits.RPD0R
#define OCPin1 RPD1Rbits.RPD1R
#define OCPin2 RPD2Rbits.RPD2R
#define OCPin3 RPD3Rbits.RPD3R

#define OCTriPin0 TRISDbits.TRISD0
#define OCTriPin1 TRISDbits.TRISD1
#define OCTriPin2 TRISDbits.TRISD2
#define OCTriPin3 TRISDbits.TRISD3

#define OCLatPin0 LATDbits.LATD0
#define OCLatPin1 LATDbits.LATD1
#define OCLatPin2 LATDbits.LATD2
#define OCLatPin3 LATDbits.LATD3

void initPWM(){
    
    OCTriPin0 = 0;
    OCTriPin1 = 0;
    OCTriPin2 = 0;
    OCTriPin3 = 0;
    
    OCPin1 = 0b1011; // map OC2 to RD1
    OC2CON = 0x0000; // Turn off OC1 while doing setup.
    OC2R = 0; // Initialize primary Compare Register
    OC2RS = 0; // Initialize secondary Compare Register
    OC2CON = 0x0006; // Configure for PWM mode
    OC2CONbits.OCTSEL = 1;
    OC2CONSET = 0x8000; // Enable OC1
    
    OCPin2= 0b1011; // map OC3 to RD2
    OC3CON = 0x0000; // Turn off OC1 while doing setup.
    OC3R = 0x0000; // Initialize primary Compare Register
    OC3RS = 0; // Initialize secondary Compare Register
    OC3CON = 0x0006; // Configure for PWM mode
    OC3CONbits.OCTSEL = 1;
    OC3CONSET = 0x8000; // Enable OC1

    OCPin3= 0b1011; // map OC4 to RD3
    OC4CON = 0x0000; // Turn off OC1 while doing setup.
    OC4R = 0x0000; // Initialize primary Compare Register
    OC4RS = 0; // Initialize secondary Compare Register
    OC4CON = 0x0006; // Configure for PWM mode
    OC4CONbits.OCTSEL = 1;
    OC4CONSET = 0x8000; // Enable OC4
    
    OCPin0= 0b1100; // map OC1 to RD0
    OC1CON = 0x0000; // Turn off OC1 while doing setup.
    OC1R = 0x0000; // Initialize primary Compare Register
    OC1RS = 0; // Initialize secondary Compare Register
    OC1CON = 0x0006; // Configure for PWM mode
    OC1CONbits.OCTSEL = 1;
    OC1CONSET = 0x8000; // Enable OC1
}

void setMotorsRotate(int ADCBufferValue){
         if(ADCBufferValue < 256){            //Backwards
            OCPin2= 0; // unmap OC3 to RD2
            OCLatPin2 = 0;
            OCPin3= 0b1011; // map OC4 to RD3
            OC4RS = ADCBufferValue*4; // left backwards
            
            OCPin0= 0; // unmap OC1 to RD0
            OCLatPin1 = 0;
            OCPin2= 0b1011; // map OC3 to RD2
            OC3RS = ADCBufferValue*4; // Right Backwards
         }
         else if (ADCBufferValue < 512){      //CounterClockwise
             
            OCPin1 = 0b1011; // unmap OC2 to RD1
            OCLatPin1 = 0;
            
            OCPin3= 0b1011; // map OC4 to RD3
            OC4RS = ADCBufferValue*2; // left backwards
            
            OCPin0= 0b1100; // map OC1 to RD0
            OC1RS = ADCBufferValue*2; //Right Forwards
            OCPin2= 0; // map OC3 to RD2
            OCLatPin2 = 0;
         }
         else if (ADCBufferValue >= 768 && ADCBufferValue < 1024){      //Right
            OCPin1 = 0b1011; // map OC2 to RD1 
            OC2RS = (ADCBufferValue*3)/2; // left forward
            OCPin3= 0; // map OC4 to RD3
            OCLatPin3 = 0;
            OCPin0= 0; // map OC1 to RD0
            OCLatPin0 = 0;
            OCPin2= 0b1011; // map OC3 to RD2
            OC3RS = (ADCBufferValue*3)/2; // Right Backwards    
         }
         else {                  //Forwards
            OCPin1 = 0b1011; // map OC2 to RD1  
            OC2RS = ADCBufferValue; // left forward
            OCPin3= 0; // map OC4 to RD3
            OCLatPin3 = 0;
            OCPin0= 0b1100; // map OC1 to RD0
            OC1RS = ADCBufferValue; //Right Forwards
            OCPin2= 0; // map OC3 to RD2
            OCLatPin2 = 0;
         }
         printVoltage(ADCBufferValue);
         
 
}

void setMotorsSweepForward(int ADCBufferValue){
    
    if(ADCBufferValue < 512){   //Left is higher
        OCPin1 = 0b1011; // map OC2 to RD1
        OC2RS = 1023; // left forward
        OCPin3= 0; // unmap OC4 to RD3
        OCLatPin3 = 0;
        OCPin0= 0b1100; // map OC1 to RD0
        OC1RS = ADCBufferValue*2; //Right Forwards
        OCPin2= 0; // unmap OC3 to RD2
        OCLatPin2 = 0;
    }
    else{
        OCPin1 = 0b1011; // map OC2 to RD1
        OC2RS = (1023-ADCBufferValue)/2; // left forward
        OCPin3= 0; // unmap OC4 to RD3
        OCLatPin3 = 0;
        OCPin0= 0b1100; // map OC1 to RD0
        OC1RS = 1023; //Right Forwards
        OCPin2= 0; // unmap OC3 to RD2
        OCLatPin2 = 0; 
        
    }
    printVoltage(ADCBufferValue);
}

void setMotorsSweepBackward(int ADCBufferValue){
    
    if(ADCBufferValue < 512){   //Left is higher 
        OCPin1 = 0; // unmap OC2 to RD1
        OCLatPin1 = 0;
        OCPin3= 0b1011; // map OC4 to RD3
        OC4RS = 1023; // left backwards
        OCPin0= 0; // unmap OC1 to RD0
        OCLatPin0 = 0;
        OCPin2= 0b1011; // map OC3 to RD2
        OC3RS = ADCBufferValue*2; // Right Backwards 
    }
    else{
        OCPin1 = 0; // unmap OC2 to RD1
        OCLatPin1 = 0;
        OCPin3= 0b1011; // map OC4 to RD3
        OC4RS = (1023-ADCBufferValue)/2; // left backwards
        OCPin0= 0; // unmap OC1 to RD0
        OCLatPin0 = 0;
        OCPin2= 0b1011; // map OC3 to RD2
        OC3RS = 1023; // Right Backwards 
        
    }
    printVoltage(ADCBufferValue);
}

void setMotorsIdle(){
        OCPin1 = 0; // unmap OC2 to RD1
        OCLatPin1 = 0;
        OCPin3= 0b1011; // map OC4 to RD3
        OC4RS = 0; // left backwards
        OCPin0= 0; // unmap OC1 to RD0
        OCLatPin0 = 0;
        OCPin2= 0b1011; // map OC3 to RD2
        OC3RS = 0; // Right Backwards
}