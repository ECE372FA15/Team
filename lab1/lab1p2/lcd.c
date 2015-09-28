
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

#define LCD_DATA  LATB
#define LCD_RS  LATBbits.LATB7
#define LCD_E   LATBbits.LATB6

#define TRIS_D7  TRISGbits.TRISG1
#define TRIS_D6  TRISFbits.TRISF0
#define TRIS_D5  TRISDbits.TRISD13
#define TRIS_D4  TRISDbits.TRISD7
#define TRIS_RS  TRISGbits.TRISB7
#define TRIS_E   TRISGbits.TRISB6

#define LCD_WRITE_DATA    1
#define LCD_WRITE_CONTROL 0

#define LOWER 1
#define UPPER 0

#define LETTER_t 0b01110100
#define DELAY_AFTER 100 //TODO: Find the ream value this is a placeholder

/* This function should take in a two-byte word and writes either the lower or upper
 * byte to the last four bits of LATB. Additionally, according to the LCD data sheet
 * It should set LCD_RS and LCD_E with the appropriate values and delays.
 * After these commands are issued, there should be a delay.
 * The command type is a simplification. From the data sheet, the RS is '1'
 * when you are simply writing a character. Otherwise, RS is '0'.
 */
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower){
    
    //TODO: What to do we with the other 4 bits? Do they just get discarded?
    
    //If the user enters a 1 for the lower input it writes lower byte to the last four bits of LATB
    if(lower == LOWER){
        LATBbits.LATB15 = (word & 0b00001000)>> 3;
        LATBbits.LATB14 = (word & 0b00000100)>> 2;
        LATBbits.LATB13 = (word & 0b00000010)>> 1;
        LATBbits.LATB12 = (word & 0b00000001);
    }
    
    //If the user enters a 0 for the lower input it writes upper byte to the last four bits of LATB
    else if(lower == UPPER){
        LATBbits.LATB15 = (word & 0b10000000)>> 7;
        LATBbits.LATB14 = (word & 0b01000000)>> 6;
        LATBbits.LATB13 = (word & 0b00100000)>> 5;
        LATBbits.LATB12 = (word & 0b00010000)>> 4;
    }
    
    //Don't write if they don't enter a 0 or 1 for lower
    
    LCD_RS = commandType; delayUs(5);
    LCD_E = 1;  delayUs(5);         //TODO: How long do these delays need to be??? 
    LCD_E = 0;  delayUs(5);
    delayUs(delayAfter);
}


/* Using writeFourBits, this function should write the two bytes of a character
 * to the LCD.
 */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter){
    
    //TODO: IS THIS RIGHT?
    writeFourBits(word, commandType, delayAfter, UPPER); 
    writeFourBits(word, commandType, delayAfter, LOWER);
}

/* Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
void printCharLCD(char c) {
    //TODO: Confirm --> The RS value is set in writeFourBits so no need to do it in here.
    writeLCD(c,LCD_WRITE_DATA, DELAY_AFTER);
}
/*Initialize the LCD
 */
void initLCD(void) {
    // Setup D, RS, and E to be outputs (0).

    // Initialization sequence utilizes specific LCD commands before the general configuration
    // commands can be utilized. The first few initilition commands cannot be done using the
    // WriteLCD function. Additionally, the specific sequence and timing is very important.

    // Enable 4-bit interface

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
void testLCD(){
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
void testWriteLCD(){
    initLCD();
    int i = 0;
    writeLCD(LETTER_t, LCD_WRITE_DATA, 5); //Should write the letter t.
    for(i = 0; i < 2000; i++) delayUs(1000); //Delays for 2 seconds.
    clearLCD();
}