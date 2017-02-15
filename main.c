/*
 * File:   main.c
 * Author: Muttsu
 *
 * Created on February 8, 2017, 5:49 PM
 * Main entry point with the main routine and ISR
 */

#include "config.h" //includes general configuration and declarations

void main() {
    init(); //included in bsp.c
    for(;;){
        
    }
}

void interrupt ISR(){
    if(TMR0IF){
        
        TMR0IF = 0;
        TMR0 = TMR0_INIT;
    }
}