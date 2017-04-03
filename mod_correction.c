#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>

#include "config.h"

#define MULTIPLIER 6
#define SET_POINT 21
#define ERROR -1

char IR[] = {0,0,0,0,0,0,1,1};

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
    static uint meanSum,sum,proportional,integral,differential,_proportional,error;
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

void PID_Init(){
    PID1CON = 0b10000101;
    PID1K1 = (unsigned short)(Kp + Ki*T + Kd/T);
    PID1K2 = (unsigned short)(0 - (Kp + 2*Kd/T));
    PID1K3 = (unsigned short)Kd/T;
    PID1SET = SET_POINT;
}

uint GetPos(){
    static uint meanSum,sum,value;
    meanSum = sum = 0;
    for (char i = 0; i < 8; i++){
        meanSum += IR[i]*i*MULTIPLIER;
        sum += IR[i];
    }
    if(sum==0){
        return (value<21?0:42);
    }
    value = meanSum/sum;
    return value;
}

long GetPID(){
    
    uint pos = GetPos();
    PID1SETH = (uint)(SET_POINT >> 8);
    PID1SETL = (uint)(SET_POINT & 0x00ff);
    PID1INH = (uint)(pos >> 8);
    PID1INL = (uint)(pos & 0x00ff);
    
    while(PID1CONbits.PID1BUSY);
    
    long value = PID1OUTHH;
    value <<= 8;
    value = PID1OUTHL;
    value <<= 8;
    value = PID1OUTLH;
    value <<= 8;
    value = PID1OUTLL;
    
    return value;
}