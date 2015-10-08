
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

    //change notification interrupt.
    TRISAbits.TRISA6 = INPUT;   // Enable input for switch
    CNPUAbits.CNPUA6 = 1;       // Enable Internal Pull-up resistor

    
    int dummyVariable = PORTAbits.RA6 = 1;//Put the CN flag down
    
    
    //init other switch
    TRISDbits.TRISD6 = INPUT;   // Enable input for switch
    CNPUDbits.CNPUD6 = 1;       // Enable internal pull-up resistor
}


