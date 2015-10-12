#include "passcode.h"
#include <string.h>
//Compares entered password with stored passwords
int checkValid(char * str, char * passWord[][]){
    int i = 0;
    int match = 0;
    int temp = 0;
    for (i = 0; i < 10; i++){
        temp = strcmp(str, passWord[i]);    //returns 0 for match 
        if (temp == 0){
            match = 1;                      //match becomes 1 for any match
        }
    }
    //return 1 for valid, return 0 for not valid
    return match;
}

// checks a string to make sure it is a valid pw entry 
int checkNewPwValid(char * str){

    return 0;
}

