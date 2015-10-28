
#include "pwm.h"

//void initPWM(){
//    RPD1Rbits.RPD1R = 0b1011; // map OC2 to RD1
//    OC2CON = 0x0000; // Turn off OC1 while doing setup.
//    OC2R = 0x0000; // Initialize primary Compare Register
//    OC2RS = 0x0000; // Initialize secondary Compare Register
//    OC2CON = 0x0006; // Configure for PWM mode
//    OC2CONSET = 0x8000; // Enable OC2
//
//   //!!!!!!!!!!!! is the next line right? idk... 
//    RPD0Rbits.RPD0R= 0b1100; // map OC1 to RD0
//    OC1CON = 0x0000; // Turn off OC1 while doing setup.
//    OC1R = 0x0000; // Initialize primary Compare Register
//    OC1RS = 0x0000; // Initialize secondary Compare Register
//    OC1CON = 0x0006; // Configure for PWM mode
//    OC1CONSET = 0x8000; // Enable OC1
//
//    RPD2Rbits.RPD2R= 0b1011; // map OC3 to RD2
//    OC3CON = 0x0000; // Turn off OC1 while doing setup.
//    OC3R = 0x0000; // Initialize primary Compare Register
//    OC3RS = 0x0000; // Initialize secondary Compare Register
//    OC3CON = 0x0006; // Configure for PWM mode
//    OC3CONSET = 0x8000; // Enable OC1
//
//    RPD3Rbits.RPD3R= 0b1011; // map OC4 to RD3
//    OC1CON = 0x0000; // Turn off OC1 while doing setup.
//    OC1R = 0x0000; // Initialize primary Compare Register
//    OC1RS = 0x0000; // Initialize secondary Compare Register
//    OC1CON = 0x0006; // Configure for PWM mode
//    OC1CONSET = 0x8000; // Enable OC1
//}


void initRightMotor(){
    // nothing todo because pwm already initialized 
} 
void initLeftMotor(){
    // nothing todo because pwm already initialized 
} 
//
//void setPwm1(int duty);//{}
//void setPwm2(int duty);//{}
//void setPwm3(int duty);//{}
//void setPwm4(int duty);//{}
void leftMotorForward(int speed){
    setPwm4(speed);
    setPwm2(0);
}
void leftMotorBackward(int speed){
    setPwm4(0);
    setPwm2(speed);
}
void leftMotorStop(){
    leftMotorForward(0);
}

void rightMotorForward(int speed){
    setPwm3(speed);
    setPwm1(0);
}
void rightMotorBackward(int speed){
    setPwm3(0);
    setPwm1(speed);
}
void rightMotorStop(){
    rightMotorForward(0);
}


