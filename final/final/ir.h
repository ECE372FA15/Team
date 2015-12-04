/* 
 * File:   ir.h
 * Authors: Brandon Lipjanic, Jonny Hawkins, Abigail Francis, Pierce Simpson
 * Team 203
 */

#ifndef IR_H
#define IR_H

#include <xc.h>
#include "lcd.h"

//define IR pins
#define IR1tri TRISBbits.TRISB0 //J11 pin 34
#define IR2tri TRISBbits.TRISB1 //J11 pin 33
#define IR3tri TRISBbits.TRISB2 //J11 pin 32
#define IR4tri TRISBbits.TRISB3 //J11 pin 31
#define IR5tri 
#define IR6tri 
#define IR7tri 
#define IR8tri

#define IR1port PORTBbits.RB0
#define IR2port PORTBbits.RB1
#define IR3port PORTBbits.RB2
#define IR4port PORTBbits.RB3
#define IR5port 
#define IR6port 
#define IR7port 
#define IR8port 
#define black 0
#define white 1


#ifndef irstateTypeEnum
#define irStateTypeEnum
typedef enum irstateTypeEnum{
    findLine,  // turn in circles until line is found 
    turnLeft,  // turn left
    turnRight, // turn right 
    goFwd,     // go forward 
    goBck,     // fo backward 
    maintainSetting, // keep previous states speed setting 
    stop       // stop! 
} irStateType;
#endif

#ifndef trackLineState_
#define trackLineState_
volatile irStateType trackLineState;
#endif // trackLineState_

#ifndef lastTrackLineState_
#define lastTrackLineState_
volatile irStateType lastTrackLineState; 
#endif // lastTrackLineStte_


//               IR3port 
//               pin 32

//               IR4port 
//               pin 31

// IR2port                    IR1port 
// pin 33                     pin 34

void initIR();

void printIR();

void analogPrintIR();

int readIR();

int analogReadIR();

int trackLine();

void testIR();

void testMotorAndIR();

irStateType parseNewIRData(int data);
int readNewIR(); 

irStateType parseIRData(int data);
irStateType parseIRDataAnalog(int data);
void printIRStateCode(irStateType data);


#endif // IR_H