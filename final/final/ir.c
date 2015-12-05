

#include "lcd.h"
#include "ir.h"
#include "timer.h"
#include "pwm.h"

#define debug_ir
//#define use_digital_ir
#define use_analog_ir

//><><><><><><><><> for reference only <><><><><><><><><><><><

//#define IR1tri TRISBbits.TRISB0 //J11 pin 34
//#define IR2tri TRISBbits.TRISB1 //J11 pin 33
//#define IR3tri TRISBbits.TRISB2 //J11 pin 32
//#define IR4tri TRISBbits.TRISB3 //J11 pin 31
//#define IR1port PORTBbits.RB0
//#define IR2port PORTBbits.RB1
//#define IR3port PORTBbits.RB2
//#define IR4port PORTBbits.RB3

void initIR() {
    // init read and write ports 
    // these may need to be changed to analog reads... 
    trackLineState = maintainSetting;
    lastTrackLineState = maintainSetting;

#ifdef use_digital_ir
    // since using analog pins, configure... 
    ANSELBbits.ANSB0 = 0;
    ANSELBbits.ANSB1 = 0;
    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB3 = 0;
    ANSELBbits.ANSB4 = 0;
    ANSELBbits.ANSB5 = 0;
    ANSELBbits.ANSB8 = 0;
    ANSELBbits.ANSB9 = 0;

    IR1tri = 1; //TRISBbits.TRISB0 //J11 pin 34
    //****************TESTING********************
    IR2tri = 1; //TRISBbits.TRISB1 //J11 pin 33
    IR3tri = 1; //TRISBbits.TRISB2 //J11 pin 32
    IR4tri = 1; //TRISBbits.TRISB3 //J11 pin 31
    IR5tri = 1; //TRISBbits.TRISB3 //J11 pin 31
    IR6tri = 1; //TRISBbits.TRISB3 //J11 pin 31
    IR7tri = 1; //TRISBbits.TRISB3 //J11 pin 31
    IR8tri = 1; //TRISBbits.TRISB3 //J11 pin 31

    // maybe pull ups...
    //        CNPUBbits.CNPUB0 = 0;
    //        CNPUBbits.CNPUB1 = 0;
    //        CNPUBbits.CNPUB2 = 0;
    //        CNPUBbits.CNPUB3 = 0;
#endif
#ifdef use_analog_ir

    IR1tri = 1; //TRISBbits.TRISB0 //J11 pin 34
    //****************TESTING********************
    IR2tri = 1; //TRISBbits.TRISB1 //J11 pin 33
    IR3tri = 1; //TRISBbits.TRISB2 //J11 pin 32
    IR4tri = 1; //TRISBbits.TRISB3 //J11 pin 31
    IR5tri = 1; //TRISBbits.TRISB3 //J11 pin 31
    IR6tri = 1; //TRISBbits.TRISB3 //J11 pin 31
    IR7tri = 1; //TRISBbits.TRISB3 //J11 pin 31
    IR8tri = 1; //TRISBbits.TRISB3 //J11 pin 31



#endif

}

void printIR() {

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

void analogPrintIR() {
    // gather data from ports 
    // may need to swap port1-2-3-4 function inupts with global definitions...


    ////////    printIRStateCode(lastTrackLineState);
    ////////    printCharLCD(' ');
    ////////
    ////////    printCharLCD(((irData & 128) >> 7) + '0');
    ////////    printCharLCD(((irData & 64) >> 6) + '0');
    ////////    printCharLCD(((irData & 32) >> 5) + '0');
    ////////
    ////////    moveCursorLCD(1, 1);
    ////////    printStringLCD("   ");
    ////////    printCharLCD(((irData & 16) >> 4) + '0');
    ////////
    ////////    printCharLCD(((irData & 4) >> 2) + '0');
    ////////    printCharLCD(((irData & 2) >> 1) + '0');
    ////////    printCharLCD(((irData & 1) >> 0) + '0');
    ////////
    ////////    printCharLCD(((irData & 8) >> 3) + '0');

    int irData = analogReadIR();

    clearLCD();

    printIRStateCode(lastTrackLineState);
    printCharLCD(' ');

    printCharLCD(((irData % 100000000) / 10000000) + '0'); // print eight digit
    printCharLCD(((irData % 10000000) / 1000000) + '0'); // print seventh digit
    printCharLCD(((irData % 1000000) / 100000) + '0'); // print sixth digit 

    moveCursorLCD(1, 1);
    printStringLCD("   ");

    printCharLCD(((irData % 100000) / 10000) + '0'); // print fifth digit
    printCharLCD(((irData % 1000) / 100) + '0'); // print third digit
    printCharLCD(((irData % 100) / 10) + '0'); // print second digit 
    printCharLCD((irData % 10) + '0'); // print first digit 

    printCharLCD(((irData % 10000) / 1000) + '0'); // print fourth digit
    
    
   
   
   
}

void testMotorAndIR() {

    int data = 0;
    data = readIR();
    clearLCD();

    if (data == 0b1111) {
        setMotorsBackward(100);
        printStringLCD("backward");
        //setMotorsSweepForward(1023);
    } else if (data == 0) {
        setMotorsForward(100);
        printStringLCD("forward");
    }

    moveCursorLCD(1, 1);
    printCharLCD((((data & 8) >> 3) + '0'));
    printCharLCD((((data & 4) >> 2) + '0'));
    printCharLCD((((data & 2) >> 1) + '0'));
    printCharLCD((((data & 1) >> 0) + '0'));


}

void testIR() {
#ifdef use_digital_ir
    printIR();
#endif
#ifdef use_analog_ir
    analogPrintIR();
#endif
    moveCursorLCD(1, 2);
    printStringLCD("testing");

}

// function polls all 4 IR led's and returns a 4 bit number where each bit 
// corresponds to the logic reading of the respective led 

int readIR() {
#ifdef use_analog_ir
#endif 

#ifdef use_digital_ir
    // read all data 
    int one = !IR1port;
    //****************TESTING********************
    int two = !IR2port;
    //****************TESTING********************
    int three = !IR3port;
    //****************TESTING********************
    int four = !IR4port;

    // return data as one number
    //****************TESTING********************
    return (one + (two << 1) + (three << 2) + (four << 3));
#endif
}

int readNewIR() {
#ifdef use_analog_ir
#endif 

#ifdef use_digital_ir
    // read all data 
    int one = !IR8port;
    int two = !IR7port;
    int three = !IR6port;
    int four = !IR5port;
    int five = !IR4port;
    int six = !IR3port;
    int seven = !IR2port;
    int eight = !IR1port;

    // return data as one number
    //****************TESTING********************
    return (one + (two << 1) + (three << 2) + (four << 3) + (five << 4) + (six << 5) + (seven << 6) + (eight << 7));
#endif
}

int analogReadIR() {
    // we might have to turn the "whole adc" off and then on each
    // time we do a read, but IDK how to do that so....
    // #define ADCDone     AD1CON1bits.SSRC
    // #define ADCFlag     IFS0bits.AD1IF
    //  ADCFlag = 0;            // reset adc thing 
    //  while(ADCDone == 0 );
    //  setMotorsSweepForward(ADC1BUF0);



    if (IFS0bits.AD1IF == 1) { //Check if ADC flag is up
        int one_ = ADC1BUF0 / 103 + 1; // get value for AN0
        int two_ = ADC1BUF1 / 103 + 1;
        int three_ = ADC1BUF2 / 103 + 1;
        int four_ = ADC1BUF3 / 103 + 1;
        int five_ = ADC1BUF4 / 103 + 1;
        int six_ = ADC1BUF5 / 103 + 1;
        int seven_ = ADC1BUF8 / 103 + 1;
        int eight_ = ADC1BUF9 / 103 + 1;
        IFS0bits.AD1IF = 0;
        return (one_ + (two_ * 10) + (three_ * 100) + (four_ * 1000) +
                (five_ * 10000) + (six_ * 100000) + (seven_ * 1000000) +
                (eight_ * 10000000));
    }

}

int trackLine() {

    irStateType nextState = maintainSetting;
    //increased motor speed from 85 to 100
    int motorSpeed = 90; // full speed ahead!!
    int secondMotorSpeed = 515;
    char str[6] = {0, 0, 0, 0, 0, 0};
    int irData = 0;

    // possible irData values 0-15

    switch (trackLineState) {
            // motor movement definitions are in pwm .h and .c files 
        case findLine: // turn in circles until line is found 
            motorFindLine(motorSpeed);
            lastTrackLineState = findLine;
            trackLineState = maintainSetting;
            break;
        case turnLeft: // turn left
            setMotorsLeft(motorSpeed);
            lastTrackLineState = turnLeft;
            trackLineState = maintainSetting;
            break;
        case turnRight: // turn right 
            setMotorsRight(motorSpeed);
            lastTrackLineState = turnRight;
            trackLineState = maintainSetting;
            break;
        case goFwd: // go forward 
            setMotorsForward(motorSpeed);
            lastTrackLineState = goFwd;
            trackLineState = maintainSetting;
            break;
        case goBck: // go backward
            setMotorsBackward(motorSpeed);
            lastTrackLineState = goBck;
            trackLineState = maintainSetting;
            break;
        case stop: // stop! 
            setMotorsIdle();
            lastTrackLineState = stop;
            trackLineState = maintainSetting;
            break;
        case maintainSetting:
            // check the ir data 
#ifdef use_digital_ir
            irData = readNewIR(); // changed from readIR()
            nextState = parseIRData(irData);
#endif
#ifdef use_analog_ir
            irData = analogReadIR();
            nextState = parseIRData(irData);
#endif 
            // only change states if necessary 
            if (nextState != lastTrackLineState) {
                trackLineState = nextState;
                lastTrackLineState = maintainSetting;
            } else {
                trackLineState = maintainSetting;
            }
            break;

    }

#ifdef debug_ir
    clearLCD();

    // the following print Char statments output the state name as a 3 char
    // code ### and code info  ( as shown below )

    // ### 000
    //    00000

#ifdef use_analog_ir
    analogPrintIR();
#endif

#ifdef use_digital_ir
    printIRStateCode(lastTrackLineState);
    printCharLCD(' ');

    printCharLCD(((irData & 128) >> 7) + '0');
    printCharLCD(((irData & 64) >> 6) + '0');
    printCharLCD(((irData & 32) >> 5) + '0');

    moveCursorLCD(1, 1);
    printStringLCD("   ");
    printCharLCD(((irData & 16) >> 4) + '0');

    printCharLCD(((irData & 4) >> 2) + '0');
    printCharLCD(((irData & 2) >> 1) + '0');
    printCharLCD(((irData & 1) >> 0) + '0');

    printCharLCD(((irData & 8) >> 3) + '0');

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

#endif

}

irStateType parseIRDataAnalog(int data) {


}

irStateType parseIRData(int data) {
    //  IR emitter/ collecter configuration (for refrence)

    //               IR3port 
    //               pin 32

    //               IR4port 
    //               pin 31

    // IR2port                    IR1port 
    // pin 33                     pin 34

    // table is not filled out all of the way...
    //IDK what to do for some of it 
    switch (data) {
            //Middle front, middle back, right, left
        case 0b0000: //bbbb
            return goFwd;
        case 0b0001: //bbbw
            return turnRight;
        case 0b0010: //bbwb
            return turnLeft;
        case 0b0011: //bbw.... haha bbw...
            return goFwd;
        case 0b0100: //bwbb
            //TESTING
            return goFwd;
            //break ;
        case 0b0101://bwbw
            return turnRight;
            //break ;
        case 0b0110: //bwwb
            return turnLeft;
            // ;
        case 0b0111: //bwww
            return goFwd;
        case 0b1000: //wbbb
            return goFwd;
            //break ;
        case 0b1001: //wbbw
            return turnRight;
            break;
        case 0b1010: //wbwb
            return turnLeft;
            break;
        case 0b1011: //wbww
            return goFwd;
            //return turnRight;
        case 0b1100: //wwbb
            return turnRight;
            break;
        case 0b1101: //wwbw
            return turnRight;
            break;
        case 0b1110: //wwwb
            return turnLeft;
            break; // maybe goBck;
        case 0b1111: //wwww
            return goBck;

    }
    // default is to findLine
    return findLine;
};

irStateType parseNewIRData(int data) {
    //  IR emitter/ collecter configuration (for refrence)
    //                                       front

    //               IR1port                IR2port                IR3port 
    //              J11 pin 34             J11 pin 33             J11 pin 32

    //left           IR4port                                       IR5port      right 
    //              J11 pin 31             [top down view]       J11 pin 30

    //               IR6port                IR7port                IR8port 
    //              J11 pin 29             J10 pin 33             J10 pin 34
    //                                      back



    // since the DEFAULT value is goFwd, don't bother 
    // defining the cases in which we will go Fwd,
    // Focus on the other cases 
    switch (data) {
            //Middle front, middle back, right, left
        case 0b01: //

            return turnRight;
        case 0b011: //

            return turnLeft;
        case 0b0111: //

            return motorPiviotLeft_;
        case 0b01111: //

            return motorPiviotRight_;

    }
    // default is to findLine
    return goFwd;
};

void printIRStateCode(irStateType data) {

    // table is not filled out all of the way...
    //IDK what to do for some of it 
    switch (data) {
        case findLine: // turn in circles until line is found 
            printStringLCD("FL ");
            return;
        case turnLeft: // turn left
            printStringLCD("TL ");
            return;
        case turnRight: // turn right 
            printStringLCD("TR ");
            return;
        case goFwd: // go forward 
            printStringLCD("FWD");
            return;
        case goBck: // fo backward 
            printStringLCD("BCK");
            return;
        case maintainSetting: // keep previous states speed setting 
            printStringLCD("MS ");
            return;
        case motorPiviotLeft_:
            printStringLCD("PL ");
            return;
        case motorPiviotRight_:
            printStringLCD("PR ");
            return;
        case stop: // stop! 
            printStringLCD("S! ");
            return;
    }
    return;
};