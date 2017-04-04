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
            
            //Entry point for servo motor control using correction value obtained from PID
            
            
            cycle ^= 1;
        }        
    }
}

void interrupt ISR(){
    if(TMR0IF){
        
        //main routine timing (5ms)
        cycle ^= 1;// when the cycle is not completed in 5ms, it will skip the next cycle;
        //it it is yet not completed, the 2nd next cycle will not be skipped
        
        TMR0IF = 0;
        TMR0 = TMR0_INIT;
    }
}