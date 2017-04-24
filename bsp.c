#include "config.h"

void B_init(){
    OSCCON = 0b11110000;
    OPTION_REG = 0b11010000 | TMR0_PS;
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    TRISA = 0;
    TRISC = 0xFF;
}

void TMR3_init(){
    PIE5bits.TMR3IE = 0;
    T3CONbits.TMR3CS = 0b00;
    T3CONbits.T3CKPS = 0;
    TMR3H = TMR3H_INIT;
    TMR3L = TMR3L_INIT;
    T3CONbits.TMR3ON = 1;
}