#include "config.h"

#define SET_POINT 7                     //ne pas changer

//char IR[] = {0,0,0,0,0,0,0,0};
union{
    struct{
        unsigned b0:1;
        unsigned b1:1;
        unsigned b2:1;
        unsigned b3:1;
        unsigned b4:1;
        unsigned b5:1;
        unsigned b6:1;
        unsigned b7:1;
    };
    char value;
}IR;

signed long correction;

void mod_correction_init(){
    ANSELC = 0;
    TRISC = 0xFF;
    PORTC=0;
    UpdateIR();
    PID_Init();
    PID1INH = 0;
}

void PID_Init(){
    PID1CON = 0x85;
    PID1K1H = (unsigned char) ((K1 & 0xFF00) >> 8);
    PID1K1L = (unsigned char)  (K1 & 0x00FF);
    PID1K2H = (unsigned char) ((K2 & 0xFF00) >> 8);
    PID1K2L = (unsigned char)  (K2 & 0x00FF);
    PID1K3H = (unsigned char) ((K3 & 0xFF00) >> 8);
    PID1K3L = (unsigned char)  (K3 & 0x00FF);
}

void UpdateIR(){
    IR.b0 = IR0;
    IR.b1 = IR1;
    IR.b2 = IR2;
    IR.b3 = IR3;
    IR.b4 = IR4;
    IR.b5 = IR5;
    IR.b6 = IR6;
    IR.b7 = IR7;
}

uint GetPos(){
    UpdateIR();
    static unsigned int meanSum,sum,value;
    meanSum = sum = 0;
    for (char i = 0; i < 8; i++){
        //meanSum += IR[i]*i*MULTIPLIER;
        if((IR.value>>i)&1){
            meanSum += i<<1;
            sum++;
        }
    }
    if(sum==0)value = 7;
    else if (sum==1)value = meanSum;
    else if (sum==2)value = (meanSum>>1);
    else if (sum==4)value = (meanSum>>2);
    else if (sum==8)value = (meanSum>>3);
    else value = meanSum/sum;
    return value;
}

//long GetCorrection(){
//    uint pos = GetPos();
//    
//    PID1SETH = (unsigned short)(SET_POINT >> 8);
//    PID1SETL = (unsigned short)(SET_POINT & 0x00ff);
//    
//    //PID1INH not used
//    PID1INL = (unsigned short)(pos & 0x00ff);
//    
//    while(PID1CONbits.PID1BUSY);
//    
//    long value = PID1OUTHH;
//    value <<= 8;
//    value |= PID1OUTHL;
//    value <<= 8;
//    value |= PID1OUTLH;
//    value <<= 8;
//    value |= PID1OUTLL;
//    
//    return value;
//}

void StartPID(){
    unsigned int pos = GetPos();
    
    PID1SETH = (unsigned short)(SET_POINT >> 8);
    PID1SETL = (unsigned short)(SET_POINT & 0x00ff);
    
    //PID1INH = (unsigned short)(pos >> 8);
    PID1INL = (unsigned short)(pos & 0x00ff);
}

void UpdateCorrection(){
    correction = PID1OUTHH;
    correction <<= 8;
    correction |= PID1OUTHL;
    correction <<= 8;
    correction |= PID1OUTLH;
    correction <<= 8;
    correction |= PID1OUTLL;
    correction >>= DIVIDER;
}