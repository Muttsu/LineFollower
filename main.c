/*
 * File:   main.c
 * Author: Muttsu
 *
 * Created on February 8, 2017, 5:49 PM
 * Main entry point with the main routine and ISR
 */

#include "config.h" //includes general configuration and declarations

char cycle = 0;
extern long correction;

void main() {
    init(); //included in bsp.c
    Mod_Correction_Init();
    for(;;){
        if(cycle){
            //LATA5 = RC4;
         
            //Correction module main routine
            if(!PID1CONbits.BUSY)UpdateCorrection();
            StartPID();
            
            if(correction!=0)cycle = 0;
            
            //Entry point for servo motor control using correction value obtained from PID
            
            
            cycle = 0;
        }        
    }
}

void interrupt ISR(){
    if(TMR0IF){
        //main routine timing (5ms)
        if(!cycle)cycle=1;
        // when the cycle is not completed in 5ms, it will skip the next cycle;
        
        TMR0IF = 0;
        TMR0 = TMR0_INIT;
    }
}