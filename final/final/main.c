/* 
 * File: main.c
 * Authors: Brandon Lipjanic, Jonny Hawkins, Abigail Francis, Pierce Simpson
 * Team 203
 */
#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "interrupt.h"
#include "timer.h"
#include "pwm.h"
#include "adc.h"
#include "HC_SR04.h"

#include "ir.h"

#define TEST_TASK2

#ifndef STATETYPE_
#define STATETYPE_

typedef enum stateTypeEnum {
    trackLines, attackBot, snooze
} stateType;
#endif // STATETYPE_

volatile stateType mainState;


#ifdef TEST_SENSOR

int main(void) {
    SYSTEMConfigPerformance(40000000);

    initTimer3();
    initTimer1();
    initLCD();
    clearLCD();
    writeLCD(0b00001111, 0, 50);
    disableInterrupts();

    testUltraSonicSensor();
    return 0;
}
#endif

#ifdef TEST_TASK2

//Right, Fwd, Left, Fwd, Left, Fwd, Right, Fwd

int main(void) {

    SYSTEMConfigPerformance(40000000);
    // initialize 
    mainState = trackLines;
    initTimer3();
    initTimer1();
    initLCD();
    initADC();
    clearLCD();
    writeLCD(0b00001111, 0, 50);
    initPWM();
    initIR();
    disableInterrupts();
    int i = 0;
    int Distance = 0;
    char Dist [3];
    while (1) {
        // override 
        while (1) {
            trackLine(i);
            if (i == 0) {
                i = 1;
            } else {
                i = 0;
            }
        }

        setMotorsForward(100);
        Distance = FindDistance();


        while (Distance > 5) {
            Distance = FindDistance();

            delayUs(1000);
        }
        clearLCD();

        setMotorsRight(100);
        printStringLCD("Right");
        for (i = 0; i < 750; i++) {
            delayUs(1000);

        }
        clearLCD();

        setMotorsForward(100);
        printStringLCD("Fwd");
        for (i = 0; i < 700; i++) {
            delayUs(1000);

        }
        clearLCD();

        setMotorsLeft(100);
        printStringLCD("Left");
        for (i = 0; i < 700; i++) {
            delayUs(1000);
        }
        clearLCD();

        setMotorsForward(100);
        printStringLCD("Fwd");
        for (i = 0; i < 700; i++) {
            delayUs(1000);

        }
        clearLCD();


    }



    return 0;
}


#endif