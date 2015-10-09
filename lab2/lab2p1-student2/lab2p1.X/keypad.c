#include <xc.h>
#include "keypad.h"
#include "timer.h"

//I need to know what Pins to use
#define ODC0 
#define ODC1
#define ODC2
#define ODC3
#define CNPU0
#define CNPU1
#define CNPU2
#define CNENKey

/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */
void initKeypad(void){

}

/* This function will be called AFTER you have determined that someone pressed
 * SOME key. This function is to figure out WHICH key has been pressed.
 * This function should return -1 if more than one key is pressed or if
 * no key is pressed at all. Otherwise, it should return the ASCII character of
 * the key that is pressed.
 */
int scanKeypad(void){
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
