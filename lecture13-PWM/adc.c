/* 
 * File:   adc.h
 * Authors: Brandon Lipjanic, Jonny Hawkins, Abigail Francis, Pierce Simpson
 * Team 203
 */

#include <xc.h>

// Init the ADC to read voltages from the pot.
void initADC(){
   
    ANSELE = 0;
  
    
    //ANSELBbits.ANSB0 = 0; 
    ANSELBbits.ANSB5 = 0;
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
    AD1CON1bits.ADON = 1;       // Turn on A/D
}
//Converts the digital value to an analog value (voltage) and prints it to the LCD.
void printVoltage(int ADCBufferValue){
    
    float tempVoltage = ADCBufferValue;
    char s [8];
    tempVoltage = tempVoltage / 1024;
    tempVoltage = tempVoltage * 3.3;
    sprintf(s, "%.2f", tempVoltage);
   
    printStringLCD(s);
}