#include "config.h"

void bsp_init(){
    OSCCON = 0b11110000;
    OPTION_REG = 0b11010000;
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    INTCONbits.IOCIE = 1;
    
    ANSELA = 0;         //toutes les broches en analogique
    ANSELB = 0;
    ANSELC = 0;
    TRISA = 0xff;       //toutes les broches en entrée
    TRISB = 0xff;
    TRISC = 0xff;
}

void TMR3_init(){
    T3CONbits.TMR3CS = 0b00;
    T3CONbits.T3CKPS = 0b00;
    T3CONbits.T3SYNC = 0b0;
    T3CONbits.TMR3ON = 0b1;
    PIE5bits.TMR3IE = 0b1;
    TMR3Hbits.TMR3H = TMR3H_INIT;
    TMR3Lbits.TMR3L = TMR3L_INIT;
}