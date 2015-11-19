

#include "lcd.h"
#include "ir.h"
#include "timer.h"
#include "pwm.h"

#define debug_ir
#define use_digital_ir
//#define use_analog_ir

//><><><><><><><><> for reference only <><><><><><><><><><><><

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
        //****************TESTING********************
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
        
        // idl what else you do for analog -jonny     ANSELE = 0;
  
    //Just in case digital thresholds don't work like we want, uncomment the next
    //four lines
    //ANSELBbits.ANSB0 = 0; 
    //ANSELBbits.ANSB1 = 0;
    //ANSELBbits.ANSB2 = 0;
    //ANSELBbits.ANSB3 = 0;
   // ANSELBbits.ANSB5 = 0;
    AD1CON1bits.FORM = 0; // 16 unsigned integer
    AD1CON1bits.SSRC = 7; // Auto-convert mode
    AD1CON1bits.ASAM = 1; // Auto-sampling
    AD1CON2bits.VCFG = 0; // Use board refernece voltages
    AD1CON2bits.CSCNA = 0; // Disable scanning
    AD1CON2bits.SMPI = 15; // 15 burritos
    AD1CON2bits.ALTS = 0; // Only Mux A
    AD1CON3bits.ADRC = 0; // Use PBCLK
    AD1CON3bits.SAMC = 2; // 2 Tad per sample
    AD1CON3bits.ADCS = 0xFF; // 512 times the PBCLK
    AD1CHSbits.CH0NA = 0; // Use Vref- as negative reference
    
    AD1CHS = 0x00050000;
    AD1CSSL = 0;
    IFS0bits.AD1IF = 0;
    IEC0bits.AD1IE = 1;
    IPC5bits.AD1IP = 7;


    IFS0bits.AD1IF = 0;         // Clear A/D conversion interrupt.
   // AD1CON1bits.ADON = 1;       // Turn on A/D
    AD1CON1bits.ADON = 0;       // Turn off A/D

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

void analogPrintIR(){
        // gather data from ports 
    // may need to swap port1-2-3-4 function inupts with global definitions...
    
    int irData = analogReadIR(); 

    clearLCD();

    printCharLCD((irData % 10) + '0'); // print first digit 
    printCharLCD(((irData % 100)/10) + '0'); // print second digit 
    printCharLCD(((irData % 1000)/100) + '0'); // print third digit
    printCharLCD(((irData % 10000)/1000) + '0'); // print fourth digit
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
// corresponds to the logic reading of the respective led 
int readIR(){
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
        return (one + (two << 1) + (three << 2) + (four << 3) ); 
    #endif
}

int analogReadIR(){
    // we might have to turn the "whole adc" off and then on each
    // time we do a read, but IDK how to do that so....
                       // #define ADCDone     AD1CON1bits.SSRC
                       // #define ADCFlag     IFS0bits.AD1IF
                       //  ADCFlag = 0;            // reset adc thing 
                       //  while(ADCDone == 0 );
                       //  setMotorsSweepForward(ADC1BUF0);

    
        AD1CON1bits.ADON = 0;       // Turn off A/D for good measure 
        ANSELBbits.ANSB0 = 1;       // set led to read 
        AD1CON1bits.ADON = 1;       // Turn on A/D
        IFS0bits.AD1IF = 0;         // reset adc thing 
        while(!AD1CON1bits.SSRC);   // wait for adc to finish 
        int one_ = ADC1BUF0/103 + 1;    // get value 
        AD1CON1bits.ADON = 0;       // Turn off A/D
        ANSELBbits.ANSB0 = 0;       // set led off

        ANSELBbits.ANSB1 = 1;       // set led to on
        AD1CON1bits.ADON = 1;       // Turn on A/D
        IFS0bits.AD1IF = 0;         // reset adc thing 
        while(!AD1CON1bits.SSRC);   // wait for adc to finish 
        int two_ = ADC1BUF0/103 + 1;
        AD1CON1bits.ADON = 0;       // Turn off A/D
        ANSELBbits.ANSB1 = 0;       // set led to off

        ANSELBbits.ANSB2 = 1;       // set led to on
        AD1CON1bits.ADON = 0;       // Turn off A/D
        IFS0bits.AD1IF = 0; // reset adc thing 
        while(!AD1CON1bits.SSRC); // wait for adc to finish 
        int three_ = ADC1BUF0/103 + 1;
        AD1CON1bits.ADON = 0;       // Turn off A/D
        ANSELBbits.ANSB2 = 0;       // set led to off

        ANSELBbits.ANSB3 = 1;       // set led to on
        AD1CON1bits.ADON = 0;       // Turn off A/D
        IFS0bits.AD1IF = 0; // reset adc thing 
        while(!AD1CON1bits.SSRC); // wait for adc to finish 
        int four_ = ADC1BUF0/103 + 1;
        AD1CON1bits.ADON = 0;       // Turn off A/D
        ANSELBbits.ANSB3 = 0;       // set led to off

        return  (one_ + (two_ * 10) + (three_ * 100) + (four_ * 1000) ); 

}

int trackLine(){
    
    irStateType nextState = maintainSetting; 
    //increased motor speed from 85 to 100
    int motorSpeed = 90; // full speed ahead!!
    int secondMotorSpeed = 515; 
    char str[6] = {0,0,0,0,0,0};
    int irData = 0; 
    
    // possible irData values 0-15
    
    switch(trackLineState){
    // motor movement definitions are in pwm .h and .c files 
        case findLine:  // turn in circles until line is found 
            motorFindLine(motorSpeed);
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
                #ifdef use_analog_ir
                    nextState = parseIRData(irData);
                #endif 
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

irStateType parseIRDataAnalog(int data){
    
    
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
        //Middle front, middle back, right, left
        case 0b0000:        //bbbb
            return goFwd; 
        case 0b0001:        //bbbw
            return turnRight;
        case 0b0010:        //bbwb
            return turnLeft;  
        case 0b0011:        //bbw.... haha bbw...
            return goFwd;
        case 0b0100:        //bwbb
            //TESTING
            return goFwd;
            //break ;
        case 0b0101://bwbw
            return turnRight;
            //break ;
        case 0b0110:        //bwwb
            return turnLeft;
            // ;
        case 0b0111:        //bwww
            return goFwd;
        case 0b1000:        //wbbb
            return goFwd;
            //break ;
        case 0b1001:        //wbbw
            return turnRight;
            break ;
        case 0b1010:        //wbwb
            return turnLeft;
            break ;
        case 0b1011:        //wbww
            return goFwd; 
            //return turnRight;
        case 0b1100:        //wwbb
            return turnRight;
            break ;
        case 0b1101:        //wwbw
            return turnRight;
            break ; 
        case 0b1110:        //wwwb
            return turnLeft;
            break ;// maybe goBck;
        case 0b1111:        //wwww
            return goBck;
         
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