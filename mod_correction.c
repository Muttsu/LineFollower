#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>

#include "config.h"

#define MULTIPLIER //unused
#define SET_POINT setPoint
#define ERROR -1

char IR[] = {0,0,0,0,0,0,0,0};
char setPoint = 7;

void Mod_Correction_Init(){
    setPoint = GetPos();
    PID_Init();
}

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

void PID_Init(){
    PID1CON = 0x85;    
    PID1K1H = (unsigned short) ((K1 & 0xFF00) >> 8);
    PID1K1L = (unsigned short)  (K1 & 0x00FF);
    PID1K2H = (unsigned short) ((K2 & 0xFF00) >> 8);
    PID1K2L = (unsigned short)  (K2 & 0x00FF);
    PID1K3H = (unsigned short) ((K3 & 0xFF00) >> 8);
    PID1K3L = (unsigned short)  (K3 & 0x00FF);
}

uint GetPos(){
    UpdateIR();
    static uint meanSum,sum,value;
    meanSum = sum = 0;
    for (char i = 0; i < 8; i++){
        //meanSum += IR[i]*i*MULTIPLIER;
        if(IR[i]){
            meanSum += i<<2;
            sum++;
        }
    }
    if(sum==0){
        return (value<21?0:42);
    }
    value = meanSum/sum;
    return value;
}

long GetCorrection(){
    uint pos = GetPos();
    
    PID1SETH = (unsigned short)(SET_POINT >> 8);
    PID1SETL = (unsigned short)(SET_POINT & 0x00ff);
    
    PID1INH = (unsigned short)(pos >> 8);
    PID1INL = (unsigned short)(pos & 0x00ff);
    
    while(PID1CONbits.PID1BUSY);
    
    long value = PID1OUTHH;
    value <<= 8;
    value |= PID1OUTHL;
    value <<= 8;
    value |= PID1OUTLH;
    value <<= 8;
    value |= PID1OUTLL;
    
    return value;
}

void StartPID(){
    uint pos = GetPos();
    
    PID1SETH = (unsigned short)(SET_POINT >> 8);
    PID1SETL = (unsigned short)(SET_POINT & 0x00ff);
    
    PID1INH = (unsigned short)(pos >> 8);
    PID1INL = (unsigned short)(pos & 0x00ff);
}

long GetPID(){
    long value = PID1OUTHH;
    value <<= 8;
    value |= PID1OUTHL;
    value <<= 8;
    value |= PID1OUTLH;
    value <<= 8;
    value |= PID1OUTLL;
    
    return value;
}