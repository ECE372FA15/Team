
#include <proc/p32mx470f512l.h>

#include "HC_SR04.h"

#define TRIG LATGbits.LATG13
#define ECHO PORTGbits.RG0

#define TRISTRIG TRISGbits.TRISG13
#define TRISECHO TRISGbits.TRISG0



//TO Set the Pulse High the Trigger Pin 
int FindDistance(){
    TRISTRIG = 0;
    TRISECHO = 1;
    int Distance = 0;
    TRIG = 0;
    delayUs(2);
    
    TRIG = 1;
    delayUs(10);
    TRIG = 0;
   // delayUs(200);
    Distance = CalculateDistance();
    return Distance;
    
}
int CalculateDistance(){
    int Distance = 0;
   
    int count = 0;
    while(ECHO == 0);
    while(ECHO == 1){
        count = count + 1;
        delayUs(1);
    }
    
   
    Distance = count/102 ;
    
   
    return Distance;
    
    
}

void testUltraSonicSensor(){
     int Distance = 0;
     char Dist [3];
     
     int i = 0;
    
     printStringLCD("Test");
    
    while(1){
    
    Distance = FindDistance();
    sprintf(Dist, "%d", Distance);
    printStringLCD(Dist);
    printStringLCD("in");
    for(i=0; i < 1000 ; i++){
        
    
    delayUs(1000);
    }
    
    clearLCD();
   
    }
}