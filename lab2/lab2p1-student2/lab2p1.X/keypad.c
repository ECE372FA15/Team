#include <xc.h>
#include "keypad.h"
#include "timer.h"

//I need to know what Pins to use
#define ODC0 LATEbits.LATE7 //Row 1/Pin 2 on keypad RE5/J10 7 on expansion board
#define ODC1 LATCbits.LATC14 //Row 2/Pin 7 on keypad RC14/J10 17 on expansion board
#define ODC2 LATDbits.LATD11 //Row 3/Pin 6 on keypad RD11/J10 15 on expansion board
#define ODC3 LATEbits.LATE1 //Row 4/Pin 4 on keypad RE1/J10 11 on expansion board
#define CNPU0 PORTEbits.RE3 //Column 1/Pin 3 on keypad RE3/J10 9 on expansion board
#define CNPU1 PORTEbits.RE7 //Column 2/Pin 1 on keypad RE7/J10 5 on expansion board
#define CNPU2 PORTDbits.RD5 //Column 3/Pin 5 on keypad RD5/J10 15 on expansion board
#define CNENKey 
#define INPUT 1
#define OUTPUT 0
/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */
int initKeypad(void){
    //Set analog mode off
    ANSELE = 0;
    TRISEbits.TRISE7 = OUTPUT;
    TRISCbits.TRISC14 = OUTPUT;
    TRISDbits.TRISD11 = OUTPUT;
    TRISEbits.TRISE1 = OUTPUT;
    TRISEbits.TRISE3 = INPUT;
    TRISEbits.TRISE7 = INPUT;
    TRISDbits.TRISD5 = INPUT;
    
}

/* This function will be called AFTER you have determined that someone pressed
 * SOME key. This function is to figure out WHICH key has been pressed.
 * This function should return -1 if more than one key is pressed or if
 * no key is pressed at all. Otherwise, it should return the ASCII character of
 * the key that is pressed.
 */
char scanKeypad(void){
    int key = -1;
    
          
    ODC0 = 1;
    ODC1 = 0;
    ODC2 = 0;
    ODC3 = 0;
    if(CNPU0 == 0) key = 1;
    if(CNPU1 == 0) key = 2;
    if(CNPU2 == 0) key = 3;
    
    ODC0 = 0;
    ODC1 = 1;
    ODC2 = 0;
    ODC3 = 0;
    if(CNPU0 == 0) key = 4;
    if(CNPU1 == 0) key = 5;
    if(CNPU2 == 0) key = 6;
    
    ODC0 = 0;
    ODC1 = 0;
    ODC2 = 1;
    ODC3 = 0;
    if(CNPU0 == 0) key = 7;
    if(CNPU1 == 0) key = 8;
    if(CNPU2 == 0) key = 9;
    
    ODC0 = 0;
    ODC1 = 0;
    ODC2 = 0;
    ODC3 = 1;
    if(CNPU0 == 0) key = 42;   //ASCII value of *
    if(CNPU1 == 0) key = 0;
    if(CNPU2 == 0) key = 35;   //ASCII value of #
    
          
    return key;
}
