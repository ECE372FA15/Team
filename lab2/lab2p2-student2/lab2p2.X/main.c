// ******************************************************************************************* //
// File:         main.c
// Date:         
// Authors:      
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include <string.h>
#include "lcd.h"
#include "timer.h"
#include "keypad.h"
#include "config.h"
#include "interrupt.h"
#include "variableDefs.h"
#define run

#define nump = 10;
#define lenp = 4; 

//#define TEST


typedef enum stateTypeEnum{
   scanKey, printKey, dbPress, dbRelease, waitForPress, waitForRelease, firstStar,
           dispGood, dispBad, dispEnter, dispValid, dispInvalid, set
} stateType;

volatile stateType modeState = dispEnter; 
volatile stateType state = waitForPress;
volatile int dummyVariable = 0;
volatile int keyScanned = -1;

int main(void)
{
    char passWord[10][6] ; //[string #][ char in string][nump][lenp]; 
    char temp[6];               //string to hold characters as they are typed in
    int pwItt = 0;              //index of the password being typed in by user 
    int pwStoreIndex = 0;       //index for string# in passWord[][] array
                                //index is used to add pws to passWord[][]
    
    int numCharsPrinted = 0;    // counter to keep things tidy on the display 
    int modeStateEnable = 1;    // enables the second state machine 
    
    ANSELE = 0;
    SYSTEMConfigPerformance(40000000);
    initLCD();
    clearLCD();
    writeLCD(0b00001111, 0, 50);
    initTimer1();
    initKeypad();
    //enableInterrupts();
    
    
#ifdef run  
    while(1){
        
   //<><><><>  button de bounce stuff  <><><><><><><><><><><><><><><><><><><><><><>        
        switch(state){

            
           case dispGood:
               printOutput("Good    ");
                break;
           case dispBad:
               printOutput("Bad     ");
                break;
           case dispEnter:
               clearLCD();
               printStringLCD("Enter   ");
               state = waitForPress;
                break;
           case dispValid://-
               printOutput("Valid   "); 
                break;
           case dispInvalid://-
               printOutput("Invalid "); 
                break;
            case printKey:
                modeStateEnable = 1; 
                temp[pwItt] = (char)keyScanned; 
                pwItt++;
                state = waitForRelease; 
            break;
            case scanKey:
                keyScanned  = scanKeypad(); 
                state = printKey;
            break;
            
            case dbPress:   
                delayUs(DBDelayTime);
                state = scanKey;
            break;
            
            case dbRelease:
                delayUs(DBDelayTime);
                state = waitForPress;
            break;
            
            case waitForPress:
               // while(state = waitForPress);        //This state will change in the ISR when the keypad is pressed.
               // while(state == waitForPress);        //This state will change in the ISR when the keypad is pressed.
            break;
            
            case waitForRelease:
                enableInterrupts(); 
                //while(state = waitForRelease);      //This state will change in the ISR when the keypad is released.
                //while(state == waitForRelease);      //This state will change in the ISR when the keypad is released.
            break;    
        }
//<><><><> END button de bounce stuff  <><><><><><><><><><><><><><><><><><><><><><>  
        
        
//<><><><>  Mode setting state machine <><><><><><><><><><><><><><><><><><><><><><>       
    if(modeStateEnable == 1){ // need to ensure this is correct...
            modeStateEnable = 0; 
        // the newKeyPressed variable gets changed to 1 everytime a key press is detected    
        switch(modeState){
           case firstStar:
               if(temp[1] == '*'){
                   modeState = set; // the state that allows you to add pws 
               }else{
                   modeState = dispBad;
               }  
               
                break;                
           case dispGood:
               printOutput("Good");
                break;
           case dispBad:
               printOutput("Bad");
                break;
           case dispEnter:
               clearLCD();
               printStringLCD("Enter");
               moveCursorLCD(2,1);
               printCharLCD(temp); 
               
               if(temp[0] == '*'){
                   modeState = firstStar;
               }else if(temp[0] == '#'){
                   modeState = dispBad;
               }else if(pwItt == 3){ // 0-3...
                   if(checkValid(temp, passWord) == 0){ 
                       modeState = dispBad;// 0 means invalid pw
                   }else{
                       modeState = dispGood; //1 means valid pw
                   }
               }else{
                   modeState = dispEnter;
               }
                break;
           case dispValid://-
               printOutput("Valid   "); 
               strcpy(passWord[pwStoreIndex],temp); // move in the new pw
               
                break;
           case dispInvalid://-
               printOutput("Invalid "); 
                break;
           case set://-
               clearLCD()
               printStringLCD("Set Mode"); 
               moveCursorLCD(2,1);  
               if(temp[pwItt] == '*' || temp[pwItt] == '#'){ // if an invalid key was entered 
                    modeState = dispInvalid; // if new pw is not valid 
               }
               
               printCharLCD(temp[pwItt]); // might work better to press key pressed 
               
               if(pwItt = 5){ // "**xxxx"...
                   temp[0] = temp[2]; temp[1] = temp[3];    // remove leading "**" 
                   temp[2] = temp[4]; temp[3] = temp[5]; temp[4] = '/0'; 
                   
                   addNewPw(temp, passWord); 
                   modeState = dispValid;
               }
                break;   
        }   
        }
//<><><><> END Mode setting state machine <><><><><><><><><><><><><><><><><><><><><><>   
        
    }
    
    return 0;
}
#endif

#ifdef TEST

while(1) jTestKeypad();
return 0;
}
#endif

#ifdef run
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
    
    disableInterrupts(); 
    
    dummyVariable = PORTEbits.RE3 = 1;
    dummyVariable = PORTEbits.RE7 = 1;
    dummyVariable = PORTDbits.RD5 = 1;
    
    IFS1bits.CNEIF = 0; //Put the CN flag down
    IFS1bits.CNDIF = 0;
    
    if(state == waitForPress){
        disableInterrupts();
        state = dbPress;
        return; 
    }
    
    if(state == waitForRelease){
        state = dbRelease; 
        enableInterrupts(); 
        return; 
    }
    
    enableInterrupts(); 
}
#endif

