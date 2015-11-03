
#ifndef IR_C
#define IR_C

#define 


void initIr(){
    
}

void printIR(unsigned int port1,unsigned int port2,unsigned int port3,unsigned int port4){
    
    // gather data from ports 
    // may need to swap port1-2-3-4 function inupts with global definitions...
    int one = port1; 
    int two = port2;
    int three = port3;
    int four = port4;
    
    clearLCD();
    
    printCharLCD(one + '0');
    printCharLCD(two + '0');
    printCharLCD(three + '0');
    printCharLCD(four + '0');
    
     
    
    
}

#endif // IR_C