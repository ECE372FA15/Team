/* 
 * File:   adc.h
 * Authors: Brandon Lipjanic, Jonny Hawkins, Abigail Francis, Pierce Simpson
 * Team 203
 */

#ifndef ADC_H
#define	ADC_H

void initADC();
int readADC(int numPin);
void printVoltage(int ADCBufferValue);

#endif	/* ADC_H */

