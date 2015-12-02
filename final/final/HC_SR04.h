 
#ifndef HC_SR04_H
#define	HC_SR04_H

#ifndef HC_SR04_stateTypeEnum
#define HC_SR04_StateTypeEnum
typedef enum HC_SR04_stateTypeEnum{
    Stop1,  // turn in circles until line is found 
    rotateRight1,  // turn left
    rotateRight2,  // turn left
    Detect, // turn right 
    FWD1,     // go forward 
    FWD2,     // go forward 
    wait
     
} HC_SR04_StateType;
#endif

int task3StateMachine();
HC_SR04_StateType task3NextState(HC_SR04_StateType lastState);
int FindDistance();
int CalculateDistance();

#endif

