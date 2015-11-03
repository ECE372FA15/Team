
#ifndef IR_H
#define IR_H

#include "lcd.h"

#define IR1tri TRISBbits.RB0 //J11 pin 34
#define IR2tri TRISBbits.RB1 //J11 pin 33
#define IR3tri TRISBbits.RB2 //J11 pin 32
#define IR4tri TRISBbits.RB3 //J11 pin 31
#define IR1port PORTBbits.RB0
#define IR2port PORTBbits.RB1
#define IR3port PORTBbits.RB2
#define IR4port PORTBbits.RB3


void initIr();

void printIR(unsigned int port1,unsigned int port2,unsigned int port3,unsigned int port4);





#endif // IR_H