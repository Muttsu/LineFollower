/*
 * File:   main.c
 * Author: Muttsu
 *
 * Created on February 8, 2017, 5:49 PM
 * Main entry point with the main routine and ISR
 */

#include "config.h" //includes general configuration and declarations

void init(void);

void main() {
    init(); //included in bsp.c
    for(;;){
        
    }
}

void interrupt ISR(){
    
}

void init(){
    OSCCON = 0b11110000;
    OPTION_REG = 0b11010000 | TMR0_PS;
    TMR0IE = TMR0_IE;
    GIE=GENERAL_INTERRUPT_ENABLE;
}