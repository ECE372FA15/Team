
// File:         interrupt.c
// Date:         9/24/2015
// Authors:      Brandon Lipjanic
//               Jonathan Hawkins
//               Abigail Francis
//               Pierce Simpson

#include <xc.h>

void enableInterrupts(){
    unsigned int val;

    // set the CP0 cause IV bit high
    asm volatile("mfc0   %0,$13" : "=r"(val));
    val |= 0x00800000;
    asm volatile("mtc0   %0,$13" : "+r"(val));

    INTCONSET = _INTCON_MVEC_MASK;

    unsigned int status = 0;
    asm volatile("ei    %0" : "=r"(status));
}

void disableInterrupts(){
    unsigned int status = 0;
    asm volatile("di    %0" : "=r"(status));
}