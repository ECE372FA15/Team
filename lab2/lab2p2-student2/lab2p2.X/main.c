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
#include "passcode.h"
#define run

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

    char passWord[passwords][wordLen] ; //[nump][lenp]; 
    char temp[wordLen];               //string to hold characters as they are typed in
    int pwItt = 0;              //index of the password being typed in by user 
    int pwStoreIndex = 0;       //index for string# in passWord[][] array
                                //index is used to add pws to passWord[][]
    
    int numCharsPrinted = 0;    // counter to keep things tidy on the display 
    int modeStateEnable = 0;    // enables the second state machine 
    int i = 0, j = 0;
    int match = 0;
    int count = 0;
    ANSELE = 0;
    SYSTEMConfigPerformance(40000000);
    initLCD();
    clearLCD();
    writeLCD(0b00001111, 0, 50);
    initTimer1();
    initKeypad();
    enableInterrupts();
    clearBuff(temp,wordLen); 
    //initialize temp to NULL
    for (i = 0; i < wordLen; i++){
        temp [i] = NULL;
    }
    //initialize passcode array to NULL
    for(i = 0; i < passwords; i++){
        for(j = 0; j < wordLen; j++){
            passWord[i][j] = NULL;
        }
    }
    // initialize the state machine output 
    printStringLCD("Enter");
    
#ifdef run  
    while(1){
        
  //<><><><>  button de bounce stuff  <><><><><><><><><><><><><><><><><><><><><><>        
        switch(state){
            case printKey:
                modeStateEnable = 1; 
                temp[pwItt] = keyScanned; 
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
                //enableInterrupts();
            break;
            
            case waitForRelease:
               // enableInterrupts(); 
            break;    
        }
//<><><><> END button de bounce stuff  <><><><><><><><><><><><><><><><><><><><><><>  
        
//!!! TODO !!! every exit branch of the state machine WILL:
//        enable/disable interrupts
//        set the next state (even if it does not change)
//        set modeStateEnable to 1 or 0
        
//    THIS will help with debugging  
        
//<><><><>  Mode setting state machine <><><><><><><><><><><><><><><><><><><><><><>       
    if(modeStateEnable == 1){ // need to ensure this is correct...
            disableInterrupts();    //messing with printing?
            modeStateEnable = 0;    //wait for key input
        // the newKeyPressed variable gets changed to 1 everytime a key press is detected    
        switch(modeState){
           case firstStar:                  //interrupts are ENABLED DELETEME
               if(temp[1] == '*'){
                   modeState = set;         // the state that allows you to add pws 
                   modeStateEnable = 0;     //wait for new key to be pressed
                   clearLCD();
                   printStringLCD("Set Mode");
                   moveCursorLCD(2,1);
                   enableInterrupts(); 
               }
               else{
                   modeState = dispBad;
                   modeStateEnable = 1;     //goto state
                   disableInterrupts();
               }  
                break;   
                
           case dispGood:               //interrupts are DISABLED DELETEME
               printOutput("Good");
               clearLCD();         
               printStringLCD("Enter"); //prompt enter state
               clearBuff(wordLen,temp); // clear the temp string 
               pwItt = 0;               // reset the pw itterator 
               modeState = dispEnter;   //switch state
               modeStateEnable = 0;     //wait for new key to be pressed
               enableInterrupts();  
                break;
                
            case dispBad:               //interrupts are DISABLED DELETEME
               printOutput("Bad");  
               clearLCD();              
               printStringLCD("Enter"); // prompt enter state
               modeState = dispEnter;   // switch state
               clearBuff(wordLen,temp); // clear the temp string 
               pwItt = 0;               // reset the pw itterator 
               modeStateEnable = 0;     // wait for new key to be pressed
               enableInterrupts();  
                break;
                
           case dispEnter:             //interrupts are DISABLED DELETEME
               clearLCD();
               printStringLCD("Enter");
               moveCursorLCD(2,1);
               printStringLCD(temp);    // print the characters as they are entered 
               if(pwItt == 4){ 
                   
                   ////////////////////////////////////////////////
                   //I had issues passing passWord[][] into a function checkValid
                   //the following is the contents of the function
                   ///////////////////////////////////////////////
//////                count = 0;
//////                match = 0;
//////                for (i = 0; i < passwords; i ++){
//////                    for (j = 0; j < wordLen; j++){
//////                        if (temp[j] == passWord[i][j]){
//////                            count = count + 1;
//////                        }
//////                    }
//////                    if (count == wordLen){
//////                            match = 1;
//////                            count = 0;
//////                    } 
//////                    else {
//////                        count = 0;
//////                    }   
//////                }
                   ///////////////////////////////////////////////
                   if( checkValid(temp,passWord) == 0){ 
                   //if( match == 0){ 
                       modeState = dispBad;     // 0 means invalid pw
                       modeStateEnable = 1;     //goto state
                       disableInterrupts();     
                   }
                   else{
                       modeState = dispGood;     //1 means valid pw
                       modeStateEnable = 1;     //goto state
                       disableInterrupts();
                       printCharLCD('&');
                   }
               }
               else if(temp[0] == '*'){
                   modeState = firstStar;
                   modeStateEnable = 0; //wait for new key to be pressed 
                   enableInterrupts(); 
               }
               else if(temp[0] == '#'){
                   modeState = dispBad;
                   modeStateEnable = 1; //continue
                   disableInterrupts();
               }
               else{
                   modeState = dispEnter;
                   modeStateEnable = 0;//wait for new key to be pressed 
                   enableInterrupts();
               }
               
                break;
           case dispValid://-
               printOutput("Valid   "); 
               clearLCD();
               printStringLCD("Enter");
               ////////////////////////////////////////////////////////////////////////
               //i suck at pointers this neeeds to go in addNewPw
               ////////////////////////////////////////////////////////////////////////
//////               count = 0;
//////               match = 0;
//////               for (i = 0; i < passwords; i ++){
//////                    for (j = 0; j < wordLen; j++){
//////                        if (temp[j] == passWord[i][j]){
//////                            count = count + 1;
//////                        }
//////                    }
//////                    if (count == wordLen){
//////                            match = 1;
//////                            count = 0;
//////                    } 
//////                    else {
//////                        count = 0;
//////                    }   
//////                }
               
               
//               //
//               //
//               while (i < passwords){
//                   while (j < wordLen){
//                       if (temp[j] == passWord[i][j]){
//                           j ++;
//                           match = 1;
//                       }
//                       else {
//                           j = wordLen;
//                           match = 0;
//                       }
//                   }
//                   if (match == 1){
//                       i = passwords;
//                   }
//                   else{
//                       i++;
//                   }
//               }
               ///////////////////////////////////////////////////////////////////////
               if(addNewPw(temp,passWord) == 0){           // if password is not in list 
               //if(match == 0){           // if password is not in list 
                   strcpy(passWord[pwStoreIndex], temp);    // add it
                   pwStoreIndex++;                          // increment itterator 
               }
               modeState = dispEnter;
               clearBuff(wordLen,temp); // clear the temp string 
               pwItt = 0;               // reset the pw itterator
               modeStateEnable = 0;     //wait for new key to be pressed 
               enableInterrupts();  
                break;
                
           case dispInvalid://-
               printOutput("Invalid "); 
               clearLCD();
               printStringLCD("Enter");
               modeState = dispEnter;
               clearBuff(wordLen,temp); // clear the temp string 
               pwItt = 0;               // reset the pw itterator 
               modeStateEnable = 0;     //wait for new key to be pressed 
               enableInterrupts(); 
                break;
                
           case set:
//               clearLCD();
//               printStringLCD("Set Mode"); 
//               moveCursorLCD(2,1); 
//               printStringLCD(temp);
               printCharLCD(keyScanned); // might work better to press key pressed 
               if(keyScanned == '*' || keyScanned == '#'){ // if an invalid key was entered 
                    modeState = dispInvalid; // if new pw is not valid 
                    modeStateEnable = 1; //next state needs to be executed
                   disableInterrupts();
               }
               else if(pwItt == 6){ // pw == "**xxxx"...
                   temp[0] = temp[2]; temp[1] = temp[3];    // remove leading "**" 
                   temp[2] = temp[4]; temp[3] = temp[5]; temp[4] = NULL; temp[5] = NULL; 
                 
                   modeState = dispValid;
                   modeStateEnable = 1; //next state needs to be executed
                   disableInterrupts();
               }
               else {
               modeStateEnable = 0; //next state needs to be executed
               enableInterrupts();
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
