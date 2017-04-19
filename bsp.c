#include "config.h"

void init(){
    OSCCON = 0b11110000;
    OPTION_REG = 0b11010000 | TMR0_PS;
    TMR0IE = 1;
    GIE=GENERAL_INTERRUPT_ENABLE;
    ANSELA = 0;
    ANSELC = 0;
    TRISA = 0;
    TRISC = 0xFF;
}

void TMR4_init(){
    
}