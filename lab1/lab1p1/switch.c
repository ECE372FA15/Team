/*
 * File:   switch.c
 * Author: Garrett
 *
 * Created on September 19, 2015, 10:46 AM
 */

#define INPUT 1
#define OUTPUT 0

void initSW(){
    //TODO: Initialize the appropriate pins to work with the external switch using a
    //change notification interrupt.
    TRISDbits.TRISD6 = INPUT;   // Enable input for switch
    CNCONDbits.ON = 1;          // Turn on CN device
    CNENDbits.CNIED6 = 1;       // Enable CN interrupt for pin
    IEC1bits.CNDIE = 1;         // Enable overall CN Interrupt
    IFS1bits.CNDIF = 0;         // Put Interrupt flag down
    CNPUDbits.CNPUD6 = 1;       // Enable Internal Pull-up resistor

}


