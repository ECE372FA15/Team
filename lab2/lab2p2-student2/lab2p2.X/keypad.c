#include <xc.h>
#include "keypad.h"
#include "timer.h"
#include "variableDefs.h"

//I need to know what Pins to use
#define ROW1 LATEbits.LATE5     //Row 1/Pin 2 on keypad RE5/J10 7 on expansion board
#define ROW2 LATCbits.LATC14    //Row 2/Pin 7 on keypad RC14/J10 17 on expansion board
#define ROW3 LATDbits.LATD11    //Row 3/Pin 6 on keypad RD11/J10 15 on expansion board
#define ROW4 LATEbits.LATE1     //Row 4/Pin 4 on keypad RE1/J10 11 on expansion board

#define ODC0 ODCEbits.ODCE5     //Row 1/Pin 2 on keypad ODC
#define ODC1 ODCCbits.ODCC14    //Row 2/Pin 7 on keypad ODC
#define ODC2 ODCDbits.ODCD11    //Row 3/Pin 6 on keypad ODC
#define ODC3 ODCEbits.ODCE1     //Row 4/Pin 4 on keypad ODC

#define COL1 PORTEbits.RE3     //Column 1/Pin 3 on keypad RE3/J10 9 on expansion board
#define COL2 PORTEbits.RE7     //Column 2/Pin 1 on keypad RE7/J10 5 on expansion board
#define COL3 PORTDbits.RD5     //Column 3/Pin 5 on keypad RD5/J10 13 on expansion board
#define CNENKey 


/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */

int initKeypad(void){
    //Set analog mode off
    ANSELE = 0;
    
    // Set Input/output pins
    TRISEbits.TRISE5 = OUTPUT;
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
    
    //CNPUDbits.CNPUD5 = 1;
    //CNPUEbits.CNPUE3 = 1;
    //CNPUEbits.CNPUE7 = 1;
    
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
    
    // set up the pins! to insure a change when any button is pressed! 
    keypadRefresh();
    
    
}

/* This function will be called AFTER you have determined that someone pressed
 * SOME key. This function is to figure out WHICH key has been pressed.
 * This function should return -1 if more than one key is pressed or if
 * no key is pressed at all. Otherwise, it should return the ASCII character of
 * the key that is pressed.
 */

void keypadRefresh(void){
    ROW1 = 0;
    ROW2 = 0;
    ROW3 = 0;
    ROW4 = 0;
    
}

int scanKeypad(void){
    int key = -1;
    int kpdDly = 700;
    
    ROW1 = 0;
    ROW2 = 1;
    ROW3 = 1;
    ROW4 = 1;
    delayUs(kpdDly);
    if(COL1 == 0){ key = '1';  keypadRefresh(); return key; }
    if(COL2 == 0){ key = '2';  keypadRefresh(); return key; }
    if(COL3 == 0){ key = '3';  keypadRefresh(); return key; }
    
    ROW1 = 1;
    ROW2 = 0;
    ROW3 = 1;
    ROW4 = 1;
    delayUs(kpdDly);
    if(COL1 == 0){ key = '4';  keypadRefresh(); return key; }
    if(COL2 == 0){ key = '5';  keypadRefresh(); return key; }
    if(COL3 == 0){ key = '6';  keypadRefresh(); return key; }
    
    ROW1 = 1;
    ROW2 = 1;
    ROW3 = 0;
    ROW4 = 1;
    delayUs(kpdDly);
    if(COL1 == 0){ key = '7';  keypadRefresh(); return key; }
    if(COL2 == 0){ key = '8';  keypadRefresh(); return key; }
    if(COL3 == 0){ key = '9';  keypadRefresh(); return key; }
    
    ROW1 = 1;
    ROW2 = 1;
    ROW3 = 1;
    ROW4 = 0;
    delayUs(kpdDly);
    if(COL1 == 0){ key = '*';  keypadRefresh(); return key; }//42;   //ASCII value of *
    if(COL2 == 0){ key = '0';  keypadRefresh(); return key; }
    if(COL3 == 0){ key = '#';  keypadRefresh(); return key; }//35;   //ASCII value of #
    
    keypadRefresh();
    return key;
}

void printOutput(const char* output){
    
    clearLCD();
    printStringLCD(output);
    delayUs(2000000);
    
}


void testKeypad(void){
    
//    ROW1 = HIGH;
//
//    ROW2 = HIGH;
//   
//    ROW3 = HIGH;
//    
//    ROW4 = HIGH;
//    delayUs(50000);
    
    ROW1 = LOW;
    
    ROW2 = LOW;
 
    ROW3 = LOW;
    
    ROW4 = LOW;

    
}

void jTestKeypad(){
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><
//<><><><><><><><><><><><><><><><><  function tests keypad  ><><><<><><><><><><><><><><><><
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><
    
// User can press keys see them on the display when the "code" is entered, the displat clears
// hardware initialization handled outside of code...
    
    char c; int i = 12; 
    char code[4] = "1234";//{'1','2','3','4'}; 
    char last1;
    char last2;
    char last3;
    char last4; 
    clearLCD();
    printCharLCD('B'); printCharLCD('e'); printCharLCD('g'); printCharLCD('i'); printCharLCD('n');
    moveCursorLCD(1,1);
    printCharLCD('T'); printCharLCD('e'); printCharLCD('s'); printCharLCD('t');
    delayUs(2000000);
    clearLCD();
    i = 0; 
    while(1){

        // scan and print 
        c = scanKeypad();
        if(c != -1){
          if( c == '0'  || c == '1'  || c == '2'  || c == '3'  || c == '4'  || c == '5'  ||
                   c == '6'  || c == '7'  || c == '8'  || c == '9'  || c == '*'  || c == '#')  
          printCharLCD((char)c);
          i ++; 
          last4 = last3;
          last3 = last2;
          last2 = last1;
          last1 = c; 
        }
        // check move conditions 
        if( i == 8){
           moveCursorLCD(1,1);
        }else if ( i == 16){
           moveCursorLCD(1,0);
           i = 0; 
        }
        if(last1 == code[3] && last2 == code[2] && last3 == code[1] && last4 == code[0])
        {
            clearLCD(); 
            i = 0;
            moveCursorLCD(0,1);
        }
            
            delayUs(100000); 
    }
};
//         //   clearLCD(); rmoved to balance timeing in isr
//            writeLCD(0b00001111, 0, 50);
//            
//           printStringLCD("STOPTED:");
//           moveCursorLCD(1,1);
//           printTimeLCD(hundredthsOfSeconds);