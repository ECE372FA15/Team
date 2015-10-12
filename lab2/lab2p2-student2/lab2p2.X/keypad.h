/* 
 * File:   keypad.h
 * Author: user
 *
 * Created on February 5, 2015, 11:42 AM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

#include "variableDefs.h"

int initKeypad(void);
int scanKeypad(void);
void printOutput(const char* output);
void testKeypad(void);
void jTestKeypad(void);
void keypadRefresh(void);

#endif	/* KEYPAD_H */

