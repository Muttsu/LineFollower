#include "config.h"

#define SET_POINT 7

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
    ANSELC = 0x00;
    TRISC = 0xFF;
    PORTC = 0x00;
    UpdateIR();
    PID_Init();
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
    static char a,n;
    a = n = 0;
    for (char i = 8; i > 0; i--){
        //meanSum += IR[i]*i*MULTIPLIER;
        if((IR.value>>(i-1))&0b1){
            a = i-1;
            n++;
        }
    }
    return (a+a+n-1);
}

void StartPID(){                //Mis a nouveau des PID1IN
    unsigned int pos = GetPos();
    
    PID1SETH = (unsigned short)(7 >> 8);
    PID1SETL = (unsigned short)(7 & 0x00ff);
    
    //PID1INH = (unsigned short)(pos >> 8);
    PID1INL = (unsigned short)(pos & 0x00ff);
}

void UpdateCorrection(){        //Mis a nouveau de la correction
    correction = PID1OUTHH;
    correction <<= 8;
    correction |= PID1OUTHL;
    correction <<= 8;
    correction |= PID1OUTLH;
    correction <<= 8;
    correction |= PID1OUTLL;
    correction >>= DIVIDER;
}