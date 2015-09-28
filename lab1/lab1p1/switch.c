
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
    TRISAbits.TRISA7 = INPUT;   // Enable input for switch
    CNCONAbits.ON = 1;          // Turn on CN device
    CNENAbits.CNIEA7 = 1;       // Enable CN interrupt for pin
    CNPUAbits.CNPUA7 = 1;       // Enable Internal Pull-up resistor
    IFS1bits.CNAIF = 0;         // Put Interrupt flag down
    IPC8bits.CNIP = 6;
    IEC1bits.CNAIE = 1;         // Enable overall CN Interrupt
}


