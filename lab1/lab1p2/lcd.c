
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
#define DB4      LATDbits.LATD4      //DB4 Write data

//RS and enable pin definitions
#define TRIS_RS  TRISGbits.TRISG14  //RS Input/output
#define RS       LATGbits.LATG14    //RS Write data
#define TRIS_E   TRISGbits.TRISG0   //E Input/output
#define E        LATGbits.LATG0     //E Write data
#define TRIS_RW   TRISEbits.TRISE6   //
#define RW        LATEbits.LATE6     //

//Define command types
#define LCD_WRITE_DATA    1
#define LCD_WRITE_CONTROL 0

#define DELAY_AFTER 100

#define LOWER 1
#define UPPER 0


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
    int delay = LCD_DELAY_standard; 
     E = 0; // set enable low to reduce future headaches 
    
    
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
     if(commandType == 0){ 
         delay = LCD_DELAY_clear;} 
     
    RS = commandType; delayUs(delay);
    E = 1;  delayUs(delay);         //TODO: How long do these delays need to be??? 
    E = 0;  delayUs(delay);
    delayUs(delay);
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
    // Setup D, RS, and E to be outputs (0).
    RS = 0; // LATGbits.LATG0
    E = 0;  // LATGbits.LATG0

    TRIS_D7 = 0;  // TRISGbits.TRISG1
    TRIS_D6 = 0;  // TRISFbits.TRISF0
    TRIS_D5 = 0;  // TRISDbits.TRISD13
    TRIS_D4 = 0;  // TRISDbits.TRISD7

    TRIS_RS = 0;  // TRISGbits.TRISG13
    TRIS_E = 0;   // TRISGbits.TRISG0
    
    // Initialization sequence utilizes specific LCD commands before the general configuration
    // commands can be utilized. The first few initilition commands cannot be done using the
    // WriteLCD function. Additionally, the specific sequence and timing is very important.

    // Enable 4-bit interface
    
    // wait 15 ms or more after VDD reaches 4.5V
    E = 0; 
    delayUs(0xFFFF);// this is maxval... hope it works!
    delayUs(0xFFFF);
    delayUs(0xFFFF);
     RS = 0; RW = 0; DB7 = 0; DB6 = 0; DB5 = 1; DB4 = 1;
    // wait 4.1 mS or more 
    delayUs(0xFFFF);// this is maxval... hope it works!
    delayUs(0xFFFF);// this is maxval... hope it works!
    delayUs(0xFFFF);// this is maxval... hope it works!
     E = 1; E = 0;
     
     RS = 0; RW = 0; DB7 = 0; DB6 = 0; DB5 = 1; DB4 = 1; 
    // wait 100uS or more 
    delayUs(0xFFFF);// this is maxval... hope it works!
     E = 1; E = 0;
     
     RS = 0; RW = 0;  DB7 = 0; DB6 = 0; DB5 = 1; DB4 = 1; 
     delayUs(LCD_DELAY_standard);
     E = 1; E = 0;
    
     RS = 0; RW = 0; DB7 = 0; DB6 = 0; DB5 = 1; DB4 = 0; 
     delayUs(LCD_DELAY_standard);
     E = 1; E = 0; 
     
     RS = 0; RW = 0;  DB7 = 0; DB6 = 0; DB5 = 1; DB4 = 0; 
     delayUs(LCD_DELAY_standard);
     E = 1; E = 0; 
     
     RS = 0; RW = 0; DB7 = 1; DB6 = 0; DB5 = 0; DB4 = 0; 
     delayUs(LCD_DELAY_standard);
     E = 1; E = 0; 
     
     RS = 0; RW = 0; DB7 = 0; DB6 = 0; DB5 = 0; DB4 = 0; 
     delayUs(LCD_DELAY_standard); 
     E = 1; E = 0;
     
     RS = 0; RW = 0; DB7 = 1; DB6 = 0; DB5 = 0; DB4 = 0; 
     delayUs(LCD_DELAY_standard);
     E = 1; E = 0; 
     
     RS = 0; RW = 0; DB7 = 0; DB6 = 0; DB5 = 0; DB4 = 0; 
     delayUs(LCD_DELAY_standard);
     E = 1; E = 0; 
     
     RS = 0; RW = 0; DB7 = 0; DB6 = 0; DB5 = 0; DB4 = 1; 
     delayUs(LCD_DELAY_standard);
     E = 1; E = 0; 
     
     RS = 0; RW = 0; DB7 = 0; DB6 = 0; DB5 = 0; DB4 = 0; 
     delayUs(LCD_DELAY_standard);
     E = 1; E = 0; 
     
     RS = 0; RW = 0; DB7 = 0; DB6 = 1; DB5 = 1; DB4 = 0; 
     delayUs(LCD_DELAY_standard);
     E = 1; E = 0;   
     
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
    
   // LATG &= 0x0000;
    
}

/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void moveCursorLCD(unsigned char x, unsigned char y){


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
    initLCD();
    int i = 0;
    printStringLCD("Test");
    for(i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
    moveCursorLCD(2,3);
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