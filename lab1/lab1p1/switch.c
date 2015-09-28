
// File:         switch.c
// Date:         9/24/2015
// Authors:      Brandon Lipjanic
//               Jonathan Hawkins
//               Abigail Francis
//               Pierce Simpson

#include <proc/p32mx470f512l.h>


#define INPUT 1
#define OUTPUT 0

//changed switch to reflect assignment of TRD0 on reg G pin 12

void initSW(){
    //TODO: Initialize the appropriate pins to work with the external switch using a
    //change notification interrupt.
    TRISGbits.TRISG13 = INPUT;   // Enable input for switch
    CNCONGbits.ON = 1;          // Turn on CN device
    CNENGbits.CNIEG13 = 1;       // Enable CN interrupt for pin
    IEC1bits.CNDIE = 1;         // Enable overall CN Interrupt
    IFS1bits.CNDIF = 0;         // Put Interrupt flag down
    CNPUGbits.CNPUG13 = 1;       // Enable Internal Pull-up resistor
    IPC8bits.CNIP = 3;

}


