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

void printTimeLCD(int hundredthsOfSeconds){
    int hundrethsMilliSeconds = 0;
    int tenthsMilliSeconds = 0;
    int onesSeconds = 0;
    int tensSeconds = 0;
  //  int onesMinutes = 0;
  //  int tensMinutes = 0;
    int temp = 0;
    
    char hundrethsMilliSecondsC = '';
    char tenthsMilliSecondsC = '';
    char onesSecondsC = '';
    char tensSecondsC = '';
    
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
    tensSecondsC = onesSeconds + '0';
    
    printCharLCD(tensSecondsC);
    printCharLCD(onesSecondsC);
    printCharLCD(":");
    printCharLCD(tenthsMilliSecondsC);
    printCharLCD(hundrethsMilliSecondsC);
    //Convert to char* pass into printStringLCD
    
    
    
     
}

void writeRunning(int hundredthsOfSeconds){

//TODO implement functionality that will write this to our LCD..
           printStringLCD("RUNNING:");
           printTimeLCD(hundredthsOfSeconds);
}

void writeStopped(int hundredthsOfSeconds){

//TODO implement functionality that will write this to our LCD..
           printStringLCD("STOPTED:");
           printTimeLCD(hundredthsOfSeconds);
}


/* This function should take in a two-byte word and writes either the lower or upper
 * byte to the last four bits of LATG. Additionally, according to the LCD data sheet
 * It should set LCD_RS and LCD_E with the appropriate values and delays.
 * After these commands are issued, there should be a delay.
 * The command type is a simplification. From the data sheet, the RS is '1'
 * when you are simply writing a character. Otherwise, RS is '0'.
 */
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower){
    
    //TODO: What to do we with the other 4 bits? Do they just get discarded? 
    // SLN, Yes, this fucnt gets called twice in a row....

     E = 0; // set enable low to reduce future headaches 
    
     delayUs(delayAfter);
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
     
    RS = commandType; 
    E = 1;  delayUs(delayAfter);         //TODO: How long do these delays need to be??? 
    E = 0;  delayUs(delayAfter);
    
}


/* Using writeFourBits, this function should write the two bytes of a character
 * to the LCD.
 */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter){
    
    //commandType is data or command:LCD_WRITE_DATA and LCD_WRITE_CONTROL
    writeFourBits(word, commandType, delayAfter, UPPER); 
    writeFourBits(word, commandType, delayAfter, LOWER);
}

/* Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
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
    delayMs(15); 
    
    //assign 1st set of values
    writeFourBits(0b00110011,0,LCD_DELAY_standard,UPPER);
    
    //wait 5ms
    delayMs(5); 
    
    writeFourBits(0b00110011,0,LCD_DELAY_standard,UPPER);
 
    //wait 100Us
    delayUs(100);
    
    writeLCD(0b00110010,0,LCD_DELAY_standard);
    
    writeLCD(0b00101000,0,LCD_DELAY_standard);
    
    writeLCD(0b00001000,0,LCD_DELAY_standard);
    
    writeLCD(0b00000001,0,LCD_DELAY_clear);
    
    writeLCD(0b00000110,0,LCD_DELAY_standard);
    
    
    

    // Function Set (specifies data width, lines, and font.

    // 4-bit mode initialization is complete. We can now configure the various LCD
    // options to control how the LCD will function.

    // TODO: Display On/Off Control
        // Turn Display (D) Off
    // TODO: Clear Display (The delay is not specified in the data sheet at this point. You really need to have the clear display delay here.
    // TODO: Entry Mode Set
        // Set Increment Display, No Shift (i.e. cursor move)
    // TODO: Display On/Off Control
        // Turn Display (D) On, Cursor (C) Off, and Blink(B) Off


}

/*
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void printStringLCD(const char* s) {
    //TODO:call printCharLCD for each char of char* s
    
    char* i = NULL;
    
    for(i=s; *i; i++){
        printCharLCD(*i);
    }
}

/*
 * Clear the display.
 */
void clearLCD(){
    
    writeLCD(1,0,LCD_DELAY_clear);
    
}

/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void moveCursorLCD(unsigned char x, unsigned char y){
    
    //uint8_t is an unsigned integer of size 8 bits. This is included in the <stdint.h> library.
    //You'll see this crap pop up all over embedded programming
    //y corresponds to columns in the LCD
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

/*
 * This function is called in lab1p2.c for testing purposes.
 * If everything is working properly, you should get this to look like the video on D2L
 * However, it is suggested that you test more than just this one function.
 */
void testLCD1(){
    initLCD();
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
  //  moveCursorLCD(2,3);
  //  printStringLCD("Test");
   // for(i = 0; i < 1000; i++) delayUs(1000);
   // clearLCD();
}

void testWriteLCD(){
    
    while(1){
        
        writeLCD('a',1,1000);
        delayUs(1000);
    }
}
// 1 for increment          0 for dectement
// 1 for display shift      0 for cursor move 
void entryModeSet(int increment_decrement,int cursor_move){
    int word = 4;
    word |= (increment_decrement<<2);
    word |= cursor_move;
    writeLCD(word, 0, LCD_DELAY_standard);
}

  