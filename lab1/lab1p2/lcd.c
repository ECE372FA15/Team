// File:         lcd.c
// Date:         9/24/2015
// Authors:      Brandon Lipjanic
//               Jonathan Hawkins
//               Abigail Francis
//               Pierce Simpson

/* TODO: Make define statements for each pin used in the LCD
 */
#include <xc.h>
#include "lcd.h"
#include "timer.h"
//#define softwareInit
//#define LCD_DATA  LATG
// 46 uS
#define LCD_DELAY_standard 50
// 1.7 mS microsecond
#define LCD_DELAY_clear 1700

#ifdef pins
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
//data pin definitions 
#define TRIS_D7 TRISGbits.TRISG1    //DB7 Input/output 
#define DB7      LATGbits.LATG1      //DB7 Write data
#define TRIS_D6 TRISFbits.TRISF0    //DB6 Input/output 
#define DB6      LATFbits.LATF0      //DB6 Write data
#define TRIS_D5 TRISDbits.TRISD13   //DB5 Input/output 
#define DB5      LATDbits.LATD13     //DB5 Write data
#define TRIS_D4 TRISDbits.TRISD7    //DB4 Input/output 
#define DB4      LATDbits.LATD7      //DB4 Write data

#define TRIS_LCD_busy
#define LCD_busy 

//RS and enable pin definitions
#define TRIS_RS  TRISGbits.TRISG14  //RS Input/output
#define RS       LATGbits.LATG14    //RS Write data
#define TRIS_E   TRISEbits.TRISE4   //E Input/output
#define E        LATEbits.LATE4     //E Write data
#define TRIS_RW   TRISEbits.TRISE6   //
#define RW        LATEbits.LATE6     //

//Define command types
#define LCD_WRITE_DATA    1
#define LCD_WRITE_CONTROL 0

#define DELAY_AFTER 100

#define LOWER 1
#define UPPER 0


void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower){
    
     E = 0; // set enable low to reduce future headaches 
     
     delayUs(delayAfter);
    RS = commandType; 
    RW = 0;
    //If the user enters a 1 for the lower input it writes lower byte to the last four bits of LATG
    if(lower == LOWER){
        DB7 = (word & 0b00001000) >> 3;
        DB6 = (word & 0b00000100) >> 2;
        DB5 = (word & 0b00000010) >> 1;
        DB4 = (word & 0b00000001);
    }
    
    //If the user enters a 0 for the lower input it writes upper byte to the last four bits of LATG
    else if(lower == UPPER){
        DB7 = (word & 0b10000000) >> 7;
        DB6 = (word & 0b01000000) >> 6;
        DB5 = (word & 0b00100000) >> 5;
        DB4 = (word & 0b00010000) >> 4;
    }
    
    //Don't write if they don't enter a 0 or 1 for lower
     
    
    E = 1;  
    delayUs(delayAfter);         //TODO: How long do these delays need to be??? 
    E = 0; 
    delayUs(delayAfter);
    
}

void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter){
    
    //commandType is data or command:LCD_WRITE_DATA and LCD_WRITE_CONTROL
    writeFourBits(word, commandType, delayAfter, UPPER); 
    writeFourBits(word, commandType, delayAfter, LOWER);
}

void printCharLCD(char c) {
    //LCD_WRITE_DATA is the RS value
    writeLCD(c,LCD_WRITE_DATA, LCD_DELAY_standard);
}

void initLCD(void) {
    TRIS_RS = 0;  // TRISGbits.TRISG13
    TRIS_E = 0;   // TRISGbits.TRISG0
    TRIS_D7 = 0;
    TRIS_D6 = 0;
    TRIS_D5 = 0;
    TRIS_D4 = 0;
    TRIS_RW = 0; //  TRISEbits.TRISE6   //
    RW = 0;
    E = 0;  // LATGbits.LATG0
    int i = 0;
    
    //wait 15ms
    //delayMs(15); 
    delayUs(15000);
    //assign 1st set of values
    writeFourBits(0b00110011,0,LCD_DELAY_standard,UPPER);
    
    //wait 4.5ms
   // delayMs(5);
    delayUs(4500);
    
    writeFourBits(0b00110011,0,LCD_DELAY_standard,UPPER);
 
    //wait 100Us
    delayUs(100);
    
    writeLCD(0b00110010,0,LCD_DELAY_standard);
    
    writeLCD(0b00101000,0,LCD_DELAY_standard);
    
    writeLCD(0b00001000,0,LCD_DELAY_standard);
    
    writeLCD(0b00000001,0,LCD_DELAY_clear);
    
    writeLCD(0b00000110,0,LCD_DELAY_standard);
    

}


void printStringLCD(const char* s) {
  
    char* i = NULL;
    
    for(i=s; *i; i++){
        printCharLCD(*i);
    }
}

void clearLCD(){
    
    writeLCD(1,0,LCD_DELAY_clear);
    
}

/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void moveCursorLCD(unsigned char x, unsigned char y){
    
    unsigned char LSB_address = y - 1;
    
    //Need to have 1 in the most significant bit place to change cursor position by writing to DD RAM
    LSB_address |= 0x80;
    
     //Check rows
    switch(x){
        
       //x is row 1
        case 1:
            //write corresponding row and column to specified cursor
             writeLCD(LSB_address,0,LCD_DELAY_standard);
        // x is row 2
        case 2:
             writeLCD(LSB_address | 0x40,0,LCD_DELAY_standard);
            
    }

}

void testLCD1(){
    //initLCD();
    int i = 0;
    printCharLCD('c');
    for(i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
    printStringLCD("Hello!");
    moveCursorLCD(1, 2);
    for(i = 0; i < 1000; i++) delayUs(1000);
    printStringLCD("Hello!");
    for(i = 0; i < 1000; i++) delayUs(1000);
}

 //Testing writeLCD function
void testLCD2(){
  //  initLCD();
    int i = 0;
    printStringLCD("Test");
    for(i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();

}

void testWriteLCD(){
    
    while(1){
        
        writeLCD('a',1,1000);
        delayUs(1000);
    }
}

void entryModeSet(int increment_decrement,int cursor_move){
    int word = 4;
    word |= (increment_decrement<<2);
    word |= cursor_move;
    writeLCD(word, 0, LCD_DELAY_standard);
}



void printTimeLCD(int hundredthsOfSeconds){
    int hundrethsMilliSeconds = 0;
    int tenthsMilliSeconds = 0;
    int onesSeconds = 0;
    int tensSeconds = 0;
  //  int onesMinutes = 0;
  //  int tensMinutes = 0;
    int temp = 0;
    
    char hundrethsMilliSecondsC = ' ';
    char tenthsMilliSecondsC = ' ';
    char onesSecondsC = ' ';
    char tensSecondsC = ' ';
    
    //Hundreths Place
    hundrethsMilliSeconds = hundredthsOfSeconds % 10;
    temp = hundredthsOfSeconds / 10;
    hundrethsMilliSecondsC = hundrethsMilliSeconds + '0';
    //Tenths place
    tenthsMilliSeconds = temp % 10;
    temp = temp / 10;
    tenthsMilliSecondsC = tenthsMilliSeconds + '0';
    //Ones Place
    onesSeconds = temp % 10;
    temp = temp / 10;
    onesSecondsC = onesSeconds + '0';
    //Tens Place
    tensSeconds = temp % 10;
    temp = temp / 10;
    tensSecondsC = tensSeconds + '0';
    
    
    
    printCharLCD(hundredthsOfSeconds/600000 + '0');
    printCharLCD( hundredthsOfSeconds/60000 + '0');
    printCharLCD(':');
    printCharLCD(tensSecondsC);
    printCharLCD(onesSecondsC);
    printCharLCD(':');
    printCharLCD(tenthsMilliSecondsC);
    printCharLCD(hundrethsMilliSecondsC);
    //Convert to char* pass into printStringLCD
}

void testPrintTimeLCD(){
    int i = 0;
    printTimeLCD(123456); //SHould print 12:34
    for(i = 0; i < 1000; i++){
        delayUs(1000);
    }
}