/* 
 * File:   adc.h
 * Authors: Brandon Lipjanic, Jonny Hawkins, Abigail Francis, Pierce Simpson
 * Team 203
 */

#include <xc.h>
#include "adc.h"

void initADC() {

    //Map pins to analog
    ANSELBbits.ANSB0 = 0;
    ANSELBbits.ANSB1 = 0;
    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB3 = 0;
    ANSELBbits.ANSB4 = 0;
    ANSELBbits.ANSB5 = 0;
    ANSELBbits.ANSB8 = 0;
    ANSELBbits.ANSB9 = 0;


    AD1CON1bits.FORM = 0; // 16 unsigned integer
    AD1CON1bits.SSRC = 7; // Auto-convert mode
    AD1CON1bits.ASAM = 1; // Auto-sampling
    AD1CON2bits.VCFG = 0; // Use board refernece voltages
    AD1CON2bits.CSCNA = 0; // Disable scanning
    AD1CON2bits.SMPI = 0; // 1 burrito
    AD1CON2bits.ALTS = 0; // Only Mux A
    AD1CON3bits.ADRC = 0; // Use PBCLK
    AD1CON3bits.SAMC = 2; // 2 Tad per sample
    AD1CON3bits.ADCS = 1; // 4 times the PBCLK
    AD1CHSbits.CH0NA = 0; // Use Vref- as negative reference
    AD1CHSbits.CH0SA = 0; //Scan in AN0 to AN9
    AD1CHSbits.CH0SA = 1; //Scan in AN0 to AN9
    AD1CHSbits.CH0SA = 2; //Scan in AN0 to AN9
    AD1CHSbits.CH0SA = 3; //Scan in AN0 to AN9
    AD1CHSbits.CH0SA = 4; //Scan in AN0 to AN9
    AD1CHSbits.CH0SA = 5; //Scan in AN0 to AN9
    AD1CHSbits.CH0SA = 8; //Scan in AN0 to AN9
    AD1CHSbits.CH0SA = 9; //Scan in AN0 to AN9
    AD1CSSL = 0; //Disable scanning again
    IFS0bits.AD1IF = 0; //put the flag down
    //    IEC0bits.AD1IE = 1; //Enable ADC interrupts
    //    IPC5bits.AD1IP = 7; //Enable ADC priority
    AD1CON1bits.ADON = 1; // Turn on A/D
}

void printVoltage(int ADCBufferValue) {

    float tempVoltage = ADCBufferValue;
    char s [8];
    tempVoltage = tempVoltage / 1024;
    tempVoltage = tempVoltage * 3.3;
    sprintf(s, "%.2f", tempVoltage);

    printStringLCD(s);
}