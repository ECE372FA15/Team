#ifndef IR_H
#define IR_H

// allow global access to the ir state variables 
#ifndef IRSTATETYPE_
#define IRSTATETYPE_
typedef enum stateTypeEnum{
    findLine,  // turn in circles until line is found 
    turnLeft,  // turn left
    turnRight, // turn right 
    goFwd,     // go forward 
    goBck,     // fo backward 
    maintainSetting, // keep previous states speed setting 
    stop       // stop! 
} irStateType;
#endif // IRSTATETYPE_

volatile irStateType trackLineState = findLine;
volatile irStateType lastTrackLineState = findLine; 

#include <xc.h>
#include "lcd.h"

//define IR pins
#define IR1tri TRISBbits.TRISB0 //J11 pin 34
#define IR2tri TRISBbits.TRISB1 //J11 pin 33
#define IR3tri TRISBbits.TRISB2 //J11 pin 32
#define IR4tri TRISBbits.TRISB3 //J11 pin 31
#define IR1port PORTBbits.RB0
#define IR2port PORTBbits.RB1
#define IR3port PORTBbits.RB2
#define IR4port PORTBbits.RB3

// IR1port                    IR2port 
// IR1tri                     IR2tri


//               IR3port 
//               IR3tri
    
//               IR4port 
//               IR4tri




void initIr();

void printIR();

int readIR();

int trackLine();

irStateType parseIRData(int data);




#endif // IR_H