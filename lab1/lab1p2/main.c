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
#define test

#ifdef test 
#define TRIS_D7 TRISGbits.TRISG1    //DB7 Input/output 
#define DB7      LATGbits.LATG1      //DB7 Write data
#define TRIS_D6 TRISFbits.TRISF0    //DB6 Input/output 
#define DB6      LATFbits.LATF0      //DB6 Write data
#define TRIS_D5 TRISDbits.TRISD13   //DB5 Input/output 
#define DB5      LATDbits.LATD13     //DB5 Write data
#define TRIS_D4 TRISDbits.TRISD7    //DB4 Input/output 
#define DB4      LATDbits.LATD4      //DB4 Write data

//RS and enable pin definitions
#define TRIS_RS  TRISGbits.TRISG14  //RS Input/output
#define RS       LATGbits.LATG14    //RS Write data
#define TRIS_E   TRISGbits.TRISG0   //E Input/output
#define E        LATGbits.LATG0     //E Write data
#define TRIS_RW   TRISEbits.TRISE6   //
#define RW        LATEbits.LATE6     //

#define Tio     TRISAbits.TRISA7
#define Ti      LATAbits.LATA7
#endif 

// ******************************************************************************************* //

int main(void)
{
    initLCD();
    testLCD2();
    Tio = 0; 
    while(1){
        Ti = 0;
        delayUs(1);
        Ti = 1; 
        delayUs(1);
        
    }
    return 0;
}
