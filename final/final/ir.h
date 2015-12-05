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
#define IR5tri TRISBbits.TRISB4 //J11 pin 30
#define IR6tri TRISBbits.TRISB5 //J11 pin 29
#define IR7tri TRISBbits.TRISB8 //J10 pin 33
#define IR8tri TRISBbits.TRISB9 //J10 pin 34
//                                       front

//               IR1port                IR2port                IR3port 
//              J11 pin 34             J11 pin 33             J11 pin 32
    
//left           IR4port                                       IR5port      right 
//              J11 pin 31             [top down view]       J11 pin 30
    
//               IR6port                IR7port                IR8port 
//              J11 pin 29             J10 pin 33             J10 pin 34
//                                      back
#define IR1port PORTBbits.RB0
#define IR2port PORTBbits.RB1
#define IR3port PORTBbits.RB2
#define IR4port PORTBbits.RB3
#define IR5port PORTBbits.RB4
#define IR6port PORTBbits.RB5
#define IR7port PORTBbits.RB8
#define IR8port PORTBbits.RB9
#define black 0
#define white 1


#ifndef irstateTypeEnum
#define irStateTypeEnum
typedef enum irstateTypeEnum{
    findLine,  // turn in circles until line is found 
    turnLeft,  // turn left
    turnRight, // turn right 
    motorPiviotLeft_,
    motorPiviotRight_,
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