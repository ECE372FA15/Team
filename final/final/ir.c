
#include "lcd.h"
#include "ir.h"
#include "timer.h"
#include "pwm.h"
#include "adc.h"

//#define debug_ir
//#define use_digital_ir
#define use_analog_ir

void initIR() {
    // init read and write ports 
    // these may need to be changed to analog reads... 
    trackLineState = maintainSetting;
    lastTrackLineState = maintainSetting;


    IR1tri = 1; //TRISBbits.TRISB0 //J11 pin 34
    IR2tri = 1; //TRISBbits.TRISB1 //J11 pin 33
    IR3tri = 1; //TRISBbits.TRISB2 //J11 pin 32
    IR4tri = 1; //TRISBbits.TRISB3 //J11 pin 31
    IR5tri = 1; //TRISBbits.TRISB4 //J11 pin 30
    IR6tri = 1; //TRISBbits.TRISB5 //J11 pin 29
    IR7tri = 1; //TRISBbits.TRISB8 //J11 pin 33
    IR8tri = 1; //TRISBbits.TRISB9 //J11 pin 32
}

void analogPrintIR(int irData) {
    // gather data from ports 

    clearLCD();

    printIRStateCode(lastTrackLineState);
    printCharLCD(' ');

    printCharLCD(((irData % 100) / 10) + '0'); // print first digit 
    printCharLCD(((irData % 100000000) / 10000000) + '0'); // print second digit 
    printCharLCD(((irData % 100000) / 10000) + '0'); // print third digit

    moveCursorLCD(1, 1);
    printStringLCD("   ");

    printCharLCD(((irData % 10000) / 1000) + '0'); // print fourth digit 
    printCharLCD(((irData % 1000000) / 100000) + '0'); // print fifth digit 
    printCharLCD((irData % 10) + '0'); // print sixth digit 
    printCharLCD(((irData % 10000000) / 1000000) + '0'); // print seventh digit
    printCharLCD(((irData % 1000) / 100) + '0'); // print eigth digit

    return;
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

//Test function to make sure IR works

void testIR() {
#ifdef use_digital_ir
    printIR();
#endif
    moveCursorLCD(1, 2);
    printStringLCD("testing");

}
// function polls all 4 IR led's and returns a 4 bit number where each bit 
// corresponds to the logic reading of the respective led 

int analogReadIR() {

    int data = 0;

    int one_ = readADC(9); // get value for AN9
    int two_ = readADC(8); // get value for AN8
    int three_ = readADC(5); // get value for AN5
    int four_ = readADC(4); // get value for AN4
    int five_ = readADC(3); // get value for AN3
    int six_ = readADC(2); // get value for AN2
    int seven_ = readADC(1); // get value for AN1
    int eight_ = readADC(0); // get value for AN0

    data = (one_ + (two_ * 10) + (three_ * 100) + (four_ * 1000) +
            (five_ * 10000) + (six_ * 100000) + (seven_ * 1000000) +
            (eight_ * 10000000));

    //send data to LCD
    analogPrintIR(data);

    //Create voltage thresholds for states
    if (one_ >= 5) {
        one_ = 1;
    } else {
        one_ = 0;
    }
    if (two_ >= 5) {
        two_ = 1;
    } else {
        two_ = 0;
    }
    if (three_ >= 5) {
        three_ = 1;
    } else {
        three_ = 0;
    }
    if (four_ >= 5) {
        four_ = 1;
    } else {
        four_ = 0;
    }
    if (five_ >= 5) {
        five_ = 1;
    } else {
        five_ = 0;
    }
    if (six_ >= 5) {
        six_ = 1;
    } else {
        six_ = 0;
    }
    if (seven_ >= 5) {
        seven_ = 1;
    } else {
        seven_ = 0;
    }
    if (eight_ >= 5) {
        eight_ = 1;
    } else {
        eight_ = 0;
    }

    //return 0-1 voltages
    return (one_ + (two_ * 10) + (three_ * 100) + (four_ * 1000) +
            (five_ * 10000) + (six_ * 100000) + (seven_ * 1000000) +
            (eight_ * 10000000));


}

int trackLine(int i) {

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

            irData = analogReadIR();
            // nextState = parseNewIRData(irData);
            if (i == 0) {
                nextState = turnLeft;
                delayUs(1000000);
            } else {
                nextState = turnRight;
                delayUs(5000000);
            }
            // only change states if necessary 
            if (nextState != lastTrackLineState) {
                trackLineState = nextState;
                lastTrackLineState = maintainSetting;
            } else {
                trackLineState = maintainSetting;
            }
            break;

    }

}

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


    //declare counter to keep track of nodes

    // since the DEFAULT value is goFwd, don't bother 
    // defining the cases in which we will go Fwd,
    // Focus on the other cases 

    switch (data) {
            //Middle front, middle back, right, left
        case 00000000:
        case 01000100:
        case 11111011:
        case 11111111://

            return turnRight;
            break;
        case 011: //

            return turnLeft;
            break;
        case 0111: //

            return motorPiviotLeft_;
            break;
        case 01111: //

            return motorPiviotRight_;
            break;
        default:
            return goFwd;
    }
    // default is to findLine

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
        case goBck: // go backward 
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