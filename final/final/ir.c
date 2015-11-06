

#include "lcd.h"
#include "ir.h"
#include "timer.h"
#include "pwm.h"

#define debug_ir
#define use_digital_ir

//><><><><><><><><> for refrence only <><><><><><><><><><><><

//#define IR1tri TRISBbits.TRISB0 //J11 pin 34
//#define IR2tri TRISBbits.TRISB1 //J11 pin 33
//#define IR3tri TRISBbits.TRISB2 //J11 pin 32
//#define IR4tri TRISBbits.TRISB3 //J11 pin 31
//#define IR1port PORTBbits.RB0
//#define IR2port PORTBbits.RB1
//#define IR3port PORTBbits.RB2
//#define IR4port PORTBbits.RB3

void initIR(){
    // init read and write ports 
    // these may need to be changed to analog reads... 
    trackLineState      = maintainSetting;
    lastTrackLineState  = maintainSetting; 

    #ifdef use_digital_ir
        // since using analog pins, configure... 
        ANSELBbits.ANSB0 = 0;
        ANSELBbits.ANSB1 = 0;
        ANSELBbits.ANSB2 = 0;
        ANSELBbits.ANSB3 = 0;

        IR1tri = 1; //TRISBbits.TRISB0 //J11 pin 34
        IR2tri = 1; //TRISBbits.TRISB1 //J11 pin 33
        IR3tri = 1; //TRISBbits.TRISB2 //J11 pin 32
        IR4tri = 1; //TRISBbits.TRISB3 //J11 pin 31

        // maybe pull ups...
//        CNPUBbits.CNPUB0 = 0;
//        CNPUBbits.CNPUB1 = 0;
//        CNPUBbits.CNPUB2 = 0;
//        CNPUBbits.CNPUB3 = 0;
    #endif
    #ifdef use_analog_ir
        // since using analog pins, configure... 
        ANSELBbits.ANSB0 = 1;
        ANSELBbits.ANSB1 = 1;
        ANSELBbits.ANSB2 = 1;
        ANSELBbits.ANSB3 = 1;
        
        // idl what else you do for analog -jonny 

    #endif
}

void printIR(){
    
    // gather data from ports 
    // may need to swap port1-2-3-4 function inupts with global definitions...
    
    int irData = readIR(); 

    clearLCD();
  //  to test, without readIR(), use this code...
    printCharLCD(IR1port + '0');
    printCharLCD(IR2port + '0');
    printCharLCD(IR3port + '0');
    printCharLCD(IR4port + '0');
//
//    printCharLCD((irData & 1) + '0'); // print first bit 
//    printCharLCD(((irData & 2) >> 1) + '0'); // print second bit 
//    printCharLCD(((irData & 4) >> 2) + '0'); // print third bit 
//    printCharLCD(((irData & 8) >> 3) + '0'); // print fourth bit    
}

void testMotorAndIR(){
    
    int data = 0;
    data = readIR();
    clearLCD(); 
    
    if( data == 0b1111){
        setMotorsBackward(100);
        printStringLCD("backward");
        //setMotorsSweepForward(1023);
    }
    else if (data == 0){
        setMotorsForward(100);
        printStringLCD("forward");
    }
    
    moveCursorLCD(1,1);
    printCharLCD((((data & 8) >> 3) + '0'));
    printCharLCD((((data & 4) >> 2) + '0')); 
    printCharLCD((((data & 2) >> 1) + '0'));
    printCharLCD((((data & 1) >> 0) + '0'));

    
}

void testIR(){
    
    printIR();

//    for(i = 0; i < 1000; i++){
//    delayUs(1000);
//    }

    printStringLCD("testing");

//    for(i = 0; i < 1000; i++){
//    delayUs(1000);
//    }
}

// function polls all 4 IR led's and returns a 4 bit number where each bit 
// corosponds to the logic reading of the respective led 
int readIR(){
 
    // read all data 
    int one = IR1port; 
    
    int two = IR2port;  
    
    int three = IR3port;  
    
    int four = IR4port;
    
    // return data as one number
    return (one + (two << 1) + (three << 2) + (four << 3) ); 
    
}

int trackLine(){
    
    irStateType nextState = maintainSetting; 
    int motorSpeed = 100; // full speed ahead!!
    char str[6] = {0,0,0,0,0,0};
    int irData = 0; 
    
    // possible irData values 0-15
    
    switch(trackLineState){
    // motor movement definitions are in pwm .h and .c files 
        case findLine:  // turn in circles until line is found 
            setMotorsSweepForward(1023);
            lastTrackLineState = findLine;
                #ifdef debug_ir
                     clearLCD();
                     printStringLCD("findLine");
                #endif
            trackLineState = maintainSetting; 
             break; 
        case turnLeft:  // turn left
            setMotorsSweepForward(1023);
            lastTrackLineState = turnLeft; 
                #ifdef debug_ir
                     clearLCD();
                     printStringLCD("turnLeft");
                #endif
            trackLineState = maintainSetting; 
             break; 
        case turnRight: // turn right 
            setMotorsSweepForward(1);
            lastTrackLineState = turnRight; 
                #ifdef debug_ir
                     clearLCD();
                     printStringLCD("turnRight");
                #endif
            trackLineState = maintainSetting; 
             break; 
        case goFwd:     // go forward 
            setMotorsForward(motorSpeed);
            lastTrackLineState = goFwd; 
                #ifdef debug_ir
                     clearLCD();
                     printStringLCD("goFwd");
                #endif
            trackLineState = maintainSetting; 
             break; 
        case goBck:     // go backward
            setMotorsBackward(motorSpeed);
            lastTrackLineState = goBck; 
                #ifdef debug_ir
                     clearLCD();
                     printStringLCD("goBck");
                #endif
            trackLineState = maintainSetting; 
             break;  
        case stop:       // stop! 
            setMotorsIdle(); 
            lastTrackLineState = stop;
                #ifdef debug_ir
                     clearLCD();
                     printStringLCD("stop");
                #endif
            trackLineState = maintainSetting; 
             break; 
        case maintainSetting:
            // check the ir data 
            nextState = parseIRData(readIR());
            // only change states if necessary 
            if(nextState != lastTrackLineState){
                trackLineState = nextState; 
            }else{
                trackLineState = maintainSetting; 
            }
            break; 
            
    }
    
    #ifdef debug_ir
//        clearLCD(); 
//        printCharLCD(((nextState & 8) >> 3) + '0');
//        printCharLCD(((nextState & 4) >> 2) + '0'); 
//        printCharLCD(((nextState & 2) >> 1) + '0');
//        printCharLCD(((nextState & 1) >> 0) + '0');
//        
//        printCharLCD(((trackLineState & 8) >> 3) + '0');
//        printCharLCD(((trackLineState & 4) >> 2) + '0'); 
//        printCharLCD(((trackLineState & 2) >> 1) + '0');
//        printCharLCD(((trackLineState & 1) >> 0) + '0');
//        
//        moveCursorLCD(1,2);
//        printCharLCD(((lastTrackLineState & 8) >> 3) + '0');
//        printCharLCD(((lastTrackLineState & 4) >> 2) + '0'); 
//        printCharLCD(((lastTrackLineState & 2) >> 1) + '0');
//        printCharLCD(((lastTrackLineState & 1) >> 0) + '0');

    #endif
    
}


irStateType parseIRData(int data){
    //  IR emitter/ collecter configuration (for refrence)
    
// IR1port                    IR2port 
// pin 34                     pin 33
//               IR3port 
//               pin 32

//               IR4port 
//               pin 31

//    0000      findLine
//    0001  turnLeft
//    0010  turnRight 
//    0011  goFwd
//    0100  
//    0101  
//    0110  
//    0111  turnRight 
//    1000  
//    1001  
//    1010  
//    1011  
//    1100  
//    1101  turnLeft
//    1110  
//    1111  goFwd
    
    // table is not filled out all of the way...
    //IDK what to do for some of it 
    switch(data){
        case 0b0000:
            return findLine; 
        case 0b0001:
            return turnLeft;
        case 0b0010:
            return turnRight;
        case 0b0011:
            return goFwd;
        case 0b0100:
            break;
        case 0b0101:
            break;
        case 0b0110:
            break;
        case 0b0111:
            return turnRight; 
        case 0b1000:
            break;
        case 0b1001:
            break;
        case 0b1010:
            break;
        case 0b1011:
            break;
        case 0b1100:
            break;
        case 0b1101:
            return turnLeft; 
        case 0b1110:
            break;
        case 0b1111:
            return goFwd; 
    }
    // default is to findLine
    return findLine; 
};