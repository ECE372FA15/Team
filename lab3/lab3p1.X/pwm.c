/* 
 * File:   pwm.h
 * Author: gvanhoy
 *
 * Created on October 8, 2015, 9:14 AM
 */

#include <xc.h>


void initPWM(){

   //!!!!!!!!!!!! is the next line right? idk... 
    RPD0Rbits.RPD0R= 0b1100; // map OC1 to RD0
    OC1CON = 0x0000; // Turn off OC1 while doing setup.
    OC1R = 0x0000; // Initialize primary Compare Register
    OC1RS = 0x0000; // Initialize secondary Compare Register
    OC1CON = 0x0006; // Configure for PWM mode
    OC1CONbits.OCTSEL = 1;
    OC1CONSET = 0x8000; // Enable OC1
    
    RPD1Rbits.RPD1R = 0b1011; // map OC2 to RD1
    OC2CON = 0x0000; // Turn off OC1 while doing setup.
    OC2R = 0x0000; // Initialize primary Compare Register
    OC2RS = 0x0000; // Initialize secondary Compare Register
    OC2CON = 0x0006; // Configure for PWM mode
    OC2CONbits.OCTSEL = 1;
    OC2CONSET = 0x8000; // Enable OC2

    RPD2Rbits.RPD2R= 0b1011; // map OC3 to RD2
    OC3CON = 0x0000; // Turn off OC1 while doing setup.
    OC3R = 0x0000; // Initialize primary Compare Register
    OC3RS = 0x0000; // Initialize secondary Compare Register
    OC3CON = 0x0006; // Configure for PWM mode
    OC3CONbits.OCTSEL = 1;
    OC3CONSET = 0x8000; // Enable OC1

    RPD3Rbits.RPD3R= 0b1011; // map OC4 to RD3
    OC4CON = 0x0000; // Turn off OC1 while doing setup.
    OC4R = 0x0000; // Initialize primary Compare Register
    OC4RS = 0x0000; // Initialize secondary Compare Register
    OC4CON = 0x0006; // Configure for PWM mode
    OC4CONbits.OCTSEL = 1;
    OC4CONSET = 0x8000; // Enable OC4
}


void setPwm1(int duty){
  //  OC1R = duty;
    OC1RS = duty;
}
void setPwm2(int duty){
   // OC2R = duty;
    OC2RS = duty;
}
void setPwm3(int duty){
  //  OC3R = duty;
    OC3RS = duty;
}
void setPwm4(int duty){
  //  OC4R = duty;
    OC4RS = duty;
}