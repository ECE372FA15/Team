/* 
 * File:   pwm.h
 * Authors: Brandon Lipjanic, Jonny Hawkins, Abigail Francis, Pierce Simpson
 * Team 203
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

void initPWM();
void setMotorsRotate(int ADCBufferValue);
void setMotorsSweepForward(int ADCBufferValue);
void setMotorsSweepBackward(int ADCBufferValue);
void setMotorsIdle();

void setMotorsBackward(int s);
void setMotorsForward(int s);
#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

