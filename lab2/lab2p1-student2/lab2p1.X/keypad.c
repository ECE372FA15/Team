#include <xc.h>
#include "keypad.h"
#include "timer.h"
#include "variableDefs.h"

//I need to know what Pins to use
#define ROW1 LATEbits.LATE7     //Row 1/Pin 2 on keypad RE5/J10 7 on expansion board
#define ROW2 LATCbits.LATC14    //Row 2/Pin 7 on keypad RC14/J10 17 on expansion board
#define ROW3 LATDbits.LATD11    //Row 3/Pin 6 on keypad RD11/J10 15 on expansion board
#define ROW4 LATEbits.LATE1     //Row 4/Pin 4 on keypad RE1/J10 11 on expansion board
#define ODC0 ODCEbits.ODCE7     //Row 1/Pin 2 on keypad ODC
#define ODC1 ODCCbits.ODCC14    //Row 2/Pin 7 on keypad ODC
#define ODC2 ODCDbits.ODCD11    //Row 3/Pin 6 on keypad ODC
#define ODC3 ODCEbits.ODCE1     //Row 4/Pin 4 on keypad ODC
#define COL1 PORTEbits.RE3     //Column 1/Pin 3 on keypad RE3/J10 9 on expansion board
#define COL2 PORTEbits.RE7     //Column 2/Pin 1 on keypad RE7/J10 5 on expansion board
#define COL3 PORTDbits.RD5     //Column 3/Pin 5 on keypad RD5/J10 15 on expansion board
#define CNENKey 


/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */

int initKeypad(void){
    //Set analog mode off
    ANSELE = 0;
    
    // Set Input/output pins
    TRISEbits.TRISE7 = OUTPUT;
    TRISCbits.TRISC14 = OUTPUT;
    TRISDbits.TRISD11 = OUTPUT;
    TRISEbits.TRISE1 = OUTPUT;
    TRISEbits.TRISE3 = INPUT;
    TRISEbits.TRISE7 = INPUT;
    TRISDbits.TRISD5 = INPUT;
    
    //enable ODC for rows
    ODC0 = 1;
    ODC1 = 1;
    ODC2 = 1;
    ODC3 = 1;
    
    CNPUDbits.CNPUD5 = 1;
    CNPUEbits.CNPUE3 = 1;
    CNPUEbits.CNPUE7 = 1;
    
    //set up CN interrupts 
    CNCONDbits.ON = 1;                  // Enable overall D interrupt
    CNCONEbits.ON = 1;                  // Enable overall E interrupt
    CNENEbits.CNIEE3 = ENABLED;         // Enable E3 pin CN
    CNENEbits.CNIEE7 = ENABLED;         // Enable E7 pin CN
    CNENDbits.CNIED5 = ENABLED;         // Enable D6 pin CN
    
    IPC8bits.CNIP = 7;                  // Set interrupt priority highest
    
    IEC1bits.CNEIE = ENABLED;           // Enable interrupt
    IEC1bits.CNDIE = ENABLED;           // EnABLE interrupt
    IFS1bits.CNEIF = 0;
    IFS1bits.CNDIF = 0;
    
}

/* This function will be called AFTER you have determined that someone pressed
 * SOME key. This function is to figure out WHICH key has been pressed.
 * This function should return -1 if more than one key is pressed or if
 * no key is pressed at all. Otherwise, it should return the ASCII character of
 * the key that is pressed.
 */
char scanKeypad(void){
    int key = -1;
    
          
    ROW1 = 1;
    ROW2 = 0;
    ROW3 = 0;
    ROW4 = 0;
    if(COL1 == 0) key = 1;
    if(COL2 == 0) key = 2;
    if(COL3 == 0) key = 3;
    
    ROW1 = 0;
    ROW2 = 1;
    ROW3 = 0;
    ROW4 = 0;
    if(COL1 == 0) key = 4;
    if(COL2 == 0) key = 5;
    if(COL3 == 0) key = 6;
    
    ROW1 = 0;
    ROW2 = 0;
    ROW3 = 1;
    ROW4 = 0;
    if(COL1 == 0) key = 7;
    if(COL2 == 0) key = 8;
    if(COL3 == 0) key = 9;
    
    ROW1 = 0;
    ROW2 = 0;
    ROW3 = 0;
    ROW4 = 1;
    if(COL1 == 0) key = 42;   //ASCII value of *
    if(COL2 == 0) key = 0;
    if(COL3 == 0) key = 35;   //ASCII value of #
    
          
    return key;
}

void testKeypad(void){
    
    COL1 = HIGH;

    COL2 = HIGH;
   
    COL3 = HIGH;
    delayUs(10000);
    COL1 = LOW;
    
    COL2 = LOW;
 
    COL3 = LOW;

    
}
