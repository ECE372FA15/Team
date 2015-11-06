

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
    printCharLCD(!IR1port + '0');
    printCharLCD(!IR2port + '0');
    printCharLCD(!IR3port + '0');
    printCharLCD(!IR4port + '0');
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
    moveCursorLCD(1,2);
    printStringLCD("testing");
    
}

// function polls all 4 IR led's and returns a 4 bit number where each bit 
// corosponds to the logic reading of the respective led 
int readIR(){
 
    // read all data 
    int one = !IR1port; 
    
    int two = !IR2port;  
    
    int three = !IR3port;  
    
    int four = !IR4port;
    
    // return data as one number
    return (one + (two << 1) + (three << 2) + (four << 3) ); 
    
}

int trackLine(){
    
    irStateType nextState = maintainSetting; 
    int motorSpeed = 90; // full speed ahead!!
    int secondMotorSpeed = 515; 
    char str[6] = {0,0,0,0,0,0};
    int irData = 0; 
    
    // possible irData values 0-15
    
    switch(trackLineState){
    // motor movement definitions are in pwm .h and .c files 
        case findLine:  // turn in circles until line is found 
            setMotorsSweepForward(secondMotorSpeed );
            lastTrackLineState = findLine;
            trackLineState = maintainSetting; 
             break; 
        case turnLeft:  // turn left
            setMotorsLeft(motorSpeed);
            lastTrackLineState = turnLeft; 
            trackLineState = maintainSetting; 
             break; 
        case turnRight: // turn right 
            setMotorsRight(motorSpeed);
            lastTrackLineState = turnRight; 
            trackLineState = maintainSetting; 
             break; 
        case goFwd:     // go forward 
            setMotorsForward(motorSpeed);
            lastTrackLineState = goFwd; 
            trackLineState = maintainSetting; 
             break; 
        case goBck:     // go backward
            setMotorsBackward(motorSpeed);
            lastTrackLineState = goBck; 
            trackLineState = maintainSetting; 
             break;  
        case stop:       // stop! 
            setMotorsIdle(); 
            lastTrackLineState = stop;
            trackLineState = maintainSetting; 
             break; 
        case maintainSetting:
            // check the ir data 
            irData = readIR();
            nextState = parseIRData(irData);
            // only change states if necessary 
            if(nextState != lastTrackLineState){
                trackLineState = nextState; 
                lastTrackLineState = maintainSetting; 
            }else{
                trackLineState = maintainSetting; 
            }
            break; 
            
    }
    
    #ifdef debug_ir
          clearLCD(); 
          printIRStateCode(lastTrackLineState); 
        moveCursorLCD(1,2);
          
        printCharLCD(((irData & 8) >> 3) + '0');
        printCharLCD(((irData & 4) >> 2) + '0'); 
        printCharLCD(((irData & 2) >> 1) + '0');
        printCharLCD(((irData & 1) >> 0) + '0');
        
//        printCharLCD(((trackLineState & 8) >> 3) + '0');
//        printCharLCD(((trackLineState & 4) >> 2) + '0'); 
//        printCharLCD(((trackLineState & 2) >> 1) + '0');
//        printCharLCD(((trackLineState & 1) >> 0) + '0');
        
//        printIR();
//        printCharLCD(((lastTrackLineState & 8) >> 3) + '0');
//        printCharLCD(((lastTrackLineState & 4) >> 2) + '0'); 
//        printCharLCD(((lastTrackLineState & 2) >> 1) + '0');
//        printCharLCD(((lastTrackLineState & 1) >> 0) + '0');

    #endif
    
}


irStateType parseIRData(int data){
    //  IR emitter/ collecter configuration (for refrence)
    
//               IR3port 
//               pin 32

//               IR4port 
//               pin 31

// IR2port                    IR1port 
// pin 33                     pin 34
    
    // table is not filled out all of the way...
    //IDK what to do for some of it 
    switch(data){
        case 0b0000:        //bbbb
            return goFwd; 
        case 0b0001:        //bbbw
            return goFwd;
        case 0b0010:        //bbwb
            return goFwd; // this is a classic wrong button manueuver 
        case 0b0011:        //bbw.... haha bbw...
            return goFwd;
        case 0b0100:        //bwbb
            return turnRight;
        case 0b0101:        //bwbw
            return turnLeft;
        case 0b0110:        //bwwb
            return turnRight;
        case 0b0111:        //bwww
            return turnLeft;
        case 0b1000:        //wbbb
            return turnLeft;
        case 0b1001:        //wbbw
            return turnRight;
        case 0b1010:        //wbwb
            return turnRight;
        case 0b1011:        //wbww
            return turnLeft;
        case 0b1100:        //wwbb
            return goFwd;
        case 0b1101:        //wwbw
            return goFwd; 
        case 0b1110:        //wwwb
            return findLine;// maybe goBck;
        case 0b1111:        //wwww
            return findLine; 
    }
    // default is to findLine
    return findLine; 
};

void printIRStateCode(irStateType data){

    // table is not filled out all of the way...
    //IDK what to do for some of it 
    switch(data){
        case findLine:  // turn in circles until line is found 
            printStringLCD("findLine");
            return;
        case turnLeft:  // turn left
            printStringLCD("turnLeft");
            return;
        case turnRight: // turn right 
            printStringLCD("turnRight");
            return;
        case goFwd:     // go forward 
            printStringLCD("goFwd");
            return;
        case goBck:     // fo backward 
            printStringLCD("goBck");
            return;
        case maintainSetting: // keep previous states speed setting 
            printStringLCD("maintainSetting");
            return;
        case stop:       // stop! 
            printStringLCD("stop!");
            return;
    }
    return; 
};