#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>

#include "config.h"

#define MULTIPLIER 1000
#define SET_POINT 3500
#define ERROR -1

char IR[] = {0,0,0,0,0,0,0,0};

void UpdateIR(){
    IR[0] = IR0;
    IR[1] = IR1;
    IR[2] = IR2;
    IR[3] = IR3;
    IR[4] = IR4;
    IR[5] = IR5;
    IR[6] = IR6;
    IR[7] = IR7;
}

int CalcError(){
    static uint meanSum,sum,proportional, integral, differential, _proportional, error;
    for (char i = 0; i < 8; i++){
        meanSum += IR[i]*i*MULTIPLIER;
        sum += IR[i];
    }
    if (sum!=0){
        proportional = meanSum/sum - SET_POINT;
        integral += proportional;
        differential = proportional - _proportional;
        error = Kp*proportional+Ki*integral+Kd*differential;
        _proportional = proportional;
        return error/DIVIDER;
    }
    else{
        return ERROR;
    }
}