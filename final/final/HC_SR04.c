
#include <proc/p32mx470f512l.h>

#include "HC_SR04.h"
#include "ir.h"

#define TRIG LATGbits.LATG13
#define ECHO PORTGbits.RG0

#define TRISTRIG TRISGbits.TRISG13
#define TRISECHO TRISGbits.TRISG0

volatile HC_SR04_StateType lastTask3StateMachineState = Stop1;
volatile HC_SR04_StateType task3StateMachineState = Stop1;

//TO Set the Pulse High the Trigger Pin 
int FindDistance(){
    TRISTRIG = 0;
    TRISECHO = 1;
    int Distance = 0;
    TRIG = 0;
    delayUs(2);
    
    TRIG = 1;
    delayUs(10);
    TRIG = 0;
   // delayUs(200);
    Distance = CalculateDistance();
    return Distance;
    
}


//               IR3port 
//               pin 32

//               IR4port 
//               pin 31

// IR2port                    IR1port 
// pin 33                     pin 34

//The demonstration of the third task for the demonstration
int task3StateMachine(){
    
    HC_SR04_StateType nextState;
    int irData = 0; 
    int FWD_sensors_not_black_1 = 3;    // b0' 0011
    int FWD_sensors_not_black_2 = 7;    // b0' 0111
    int motorSpeed = 75; 
    int turnMotorSpeed = 75; 
    int objectDistanceThreshold = 100; /// I have no idea what this should be 
    
    // the only difference between the state machine brandon gave me and this
    // is that this one expands the RotateRight and FWD states into RotateRight1
    // and rotateRight2, FWD1 and FWD2, the point being that the (1) states
    // sets the motor state, and then the (2) states poll for data
    
    switch(task3StateMachineState){
        case Stop1:
            setMotorsIdle();    // Both 0
            delayUs(50000);     // delay .5 seconds 
            lastTask3StateMachineState = Stop1;
            task3StateMachineState = rotateRight1; 
            break;
        case rotateRight1:
            motorPiviotRight(turnMotorSpeed);   // leftFwd(75), RightBack(75) ... I think 
            lastTask3StateMachineState = rotateRight1;
            task3StateMachineState = rotateRight2; 
            break;
        case rotateRight2:
            //motorPiviotRight(turnMotorSpeed);   // leftFwd(75), RightBack(75) ... I think 
            irData = readIR(); // ir.c->readIR())
            if(irData == FWD_sensors_not_black_2 || irData == FWD_sensors_not_black_1  ){ 
                // FWd sensors not black
                task3StateMachineState = rotateRight2; 
            }else{
                // Fwd sensors black... once you go black you never go back...
                task3StateMachineState = Detect;                 
            }
            lastTask3StateMachineState = rotateRight2;
            break;
        case Detect:
            setMotorsIdle();                    // Both 0
            if(FindDistance() > objectDistanceThreshold){// wait for pulse from Us sensor 
                // the FindDistance() has a delay in it...
                // no objcet
                task3StateMachineState = FWD1; 
            }else{
                // objcet detected 
                task3StateMachineState = rotateRight1; 
            }
            lastTask3StateMachineState = Detect;
            break;
        case FWD1: // go FwD
            setMotorsForward(motorSpeed);       // rightFwd(100) leftFwd(100); 
            lastTask3StateMachineState = FWD1;
            task3StateMachineState = FWD2; 
            break;
        case FWD2: // go FwD 
            lastTask3StateMachineState = FWD2;
            task3StateMachineState = FWD2; 
            break;
            return -1; // return failure because state machine failed
    }
    return 0; // return pass
}

int CalculateDistance(){
    int Distance = 0;
   
    int count = 0;
    while(ECHO == 0);
    while(ECHO == 1){
        count = count + 1;
        delayUs(1);
    }
    
   
    Distance = count/102 ;
    
   
    return Distance;
    
    
}

void testUltraSonicSensor(){
     int Distance = 0;
     char Dist [3];
     
     int i = 0;
    
     printStringLCD("Test");
    
    while(1){
    
    Distance = FindDistance();
    sprintf(Dist, "%d", Distance);
    printStringLCD(Dist);
    printStringLCD("in");
    for(i=0; i < 1000 ; i++){
        
    
    delayUs(1000);
    }
    
    clearLCD();
   
    }
}