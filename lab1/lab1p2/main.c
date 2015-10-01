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

#endif 

// ******************************************************************************************* //

int main(void)
{
    char data = 'A';
        //initLCD(); 
       // printCharLCD(data);
    
        delayUs(0xFFFF);
        delayUs(0xFFFF);
        delayUs(0xFFFF);
        delayUs(0xFFFF);
        delayUs(0xFFFF);
        E = 0;
        RS = 0;
        RW = 0;
        DB7 = 0;
        DB6 = 0;
        DB5 = 0;
        DB4 = 0;
        delayUs(0xFFFF);
        E = 1; 
        delayUs(0xFFFF);
        delayUs(0xFFFF);
        delayUs(0xFFFF);
        delayUs(0xFFFF);
        delayUs(0xFFFF);
        delayUs(0xFFFF);
        E = 0; 
        delayUs(0xFFFF);
        
        RS = 0;
        RW = 0;
        DB7 = 1;
        DB6 = 1;
        DB5 = 1;
        DB4 = 1;
        delayUs(0xFFFF);
        E = 1;
        delayUs(0xFFFF);
        delayUs(0xFFFF);
        delayUs(0xFFFF);
        delayUs(0xFFFF);
        delayUs(0xFFFF);
        delayUs(0xFFFF);
        E = 0; 
        delayUs(0xFFFF);
        while (1);
        //data = data + 1;
        printCharLCD(0b01010101); 
        //initLCD(); 
       // printCharLCD('A');
        //testLCD1();
     //   testLCD2();
    
    
    return 0;
}
