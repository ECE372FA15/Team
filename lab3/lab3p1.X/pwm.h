/* 
 * File:   pwm.h
 * Author: gvanhoy
 *
 * Created on October 8, 2015, 9:14 AM
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

void initPWM();

void setPwm1(int duty);//{}
void setPwm2(int duty);//{}
void setPwm3(int duty);//{}
void setPwm4(int duty);//{}

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

