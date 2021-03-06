// File:         main.c
// Date:         9/24/2015
// Authors:      Brandon Lipjanic
//               Jonathan Hawkins
//               Abigail Francis
//               Pierce Simpson
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "config.h"
#include "interrupt.h"
//#define test
#define test

#ifdef test 
#define TRIS_D7 TRISGbits.TRISG1    //DB7 Input/output  
#define DB7      LATGbits.LATG1      //DB7 Write data   // i/o board j11 pin 5
#define TRIS_D6 TRISFbits.TRISF0    //DB6 Input/output 
#define DB6      LATFbits.LATF0      //DB6 Write data   // i/o board j11 pin 7
#define TRIS_D5 TRISDbits.TRISD13   //DB5 Input/output 
#define DB5      LATDbits.LATD13     //DB5 Write data   // i/o board j11 pin 9
#define TRIS_D4 TRISDbits.TRISD7    //DB4 Input/output 
#define DB4      LATDbits.LATD7      //DB4 Write data   // i/o board j11 pin 11

//RS and enable pin definitions
#define TRIS_RS  TRISGbits.TRISG14  //RS Input/output
#define RS       LATGbits.LATG14    //RS Write data   // i/o board j10 pin 4
#define TRIS_E   TRISEbits.TRISE4   //E Input/output
#define E        LATEbits.LATE4     //E Write data   // i/o board j10 pin 8
#define TRIS_RW   TRISEbits.TRISE6   //
#define RW        LATEbits.LATE6     //              // i/o board j10 pin 6     

#endif 

// ******************************************************************************************* //

int main(void)
{
    ANSELE = 0;
    SYSTEMConfigPerformance(40000000);
    initTimer2();
    initLCD();
    clearLCD();
    writeLCD(0b00001111, 0, 50);
    while(1){
         testLCD1();
        clearLCD();
        delayUs(50000);
    }
    return 0;
}
