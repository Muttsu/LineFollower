#include "config.h"

void init(){
    OSCCON = 0b11110000;
    OPTION_REG = 0b11010000 | TMR0_PS;
    TMR0IE = TMR0_IE;
    GIE=GENERAL_INTERRUPT_ENABLE;
}