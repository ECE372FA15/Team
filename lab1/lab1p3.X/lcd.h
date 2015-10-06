
// File:         lcd.h
// Date:         9/24/2015
// Authors:      Brandon Lipjanic
//               Jonathan Hawkins
//               Abigail Francis
//               Pierce Simpson
#ifndef LCD_H
#define LCD_H
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delay);
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower);
void initLCD(void);
void clearLCD(void);
void moveCursorLCD(unsigned char x, unsigned char y);
void printCharLCD(char c);
void printStringLCD(const char* s);
void testLCD1();
void testLCD2();
void testWriteLCD();

void writeRunning(int hundredthsOfSeconds);
void writeStopped(int hundredthsOfSeconds);
void printTimeLCD(int hundredthsOfSeconds);


void entryModeSet(int increment_decrement,int cursor_move);

#endif 