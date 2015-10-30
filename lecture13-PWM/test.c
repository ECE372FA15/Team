#include "pwm.h"
#include "timer.c"

//Test to check speed of the motors with software fcn

void test(){
    int i = 0;
    
    // Loop from 0 to 1023 by increments of 10 while calling the motors forward
    // function to check increasing motor speed
    
    for(i = 0; i < 1024; i+=10){
        setMotorsSweepForward(i);
        delayUs(100);
    }
    
    // Loop from 0 to 1023 by increments of 10 while calling the motors backward
    // function to check increasing motor speed
    
    for(i = 1020; i >= 0; i-=10){
        setMotorsSweepForward(i);
        delayUs(100);
    }
    
    // Loop from 0 to 1023 by increments of 10 while calling the motors forward
    // function to check increasing motor speed
    
    for(i = 0; i < 1024; i+=10){
        setMotorsSweepBackward(i);
        delayUs(100);
    }
    
    // Loop from 0 to 1023 by increments of 10 while calling the motors forward
    // function to check increasing motor speed
    
    for(i = 1020; i >= 0; i-=10){
        setMotorsSweepBackward(i);
        delayUs(100);
    }
    
}