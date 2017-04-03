/*
 * File:   main.c
 * Author: Muttsu
 *
 * Created on February 8, 2017, 5:49 PM
 * Main entry point with the main routine and ISR
 */

#include "config.h" //includes general configuration and declarations

char cycle = 0;

long correction = 0;

void main() {
    init(); //included in bsp.c
    Mod_Correction_Init();
    for(;;){
        if(cycle){
         
            //Correction module main routine
            if(!PID1CONbits.BUSY)correction = GetPID();
            
            StartPID();
            
            cycle = 0;
        }        
    }
}

void interrupt ISR(){
    if(TMR0IF){
        
        //main routine
        cycle = 1;
        
        TMR0IF = 0;
        TMR0 = TMR0_INIT;
    }
}