#include "config.h"

void Servo_Init(){
    RA5PPS = 0b00001110;
    RA1PPS = 0b00001111;
    //TRISC |= 0b11000000;
    PWM3CON = 0;
    PWM4CON = 0;
    PR2 = PERIOD2;
    PWM3DCH = 0;
    PWM3DCL &= 0b00111111;
    PWM4DCH = 0;
    PWM4DCL &= 0b00111111;
    
    PIR1bits.TMR2IF = 0; 
    T2CONbits.CKPS = 0b000;
    T2CONbits.ON = 1;
    
    while(!TMR2IF);
    //TRISC &= 0b00111111;
    PWM3CON |= 0b10000000;
    PWM4CON |= 0b10000000;
}

void Drive(){
    extern signed long correction;
    signed long value = (correction<-512?-512:(correction>512?512:correction));
    unsigned int s = DUTY_CYCLE_SET_POINT + value;
    unsigned int t = DUTY_CYCLE_SET_POINT - value;
    PWM3DCH = (unsigned short)(s>>2);
    PWM3DCL = (unsigned short)((s&0b11)<<6);
    PWM4DCH = (unsigned short)(t>>2);
    PWM4DCL = (unsigned short)((t&0b11)<<6);
}