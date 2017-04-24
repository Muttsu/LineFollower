/*
 * File:   main.c
 * Author: Muttsu
 *
 * Created on February 8, 2017, 5:49 PM
 * Main entry point with the main routine and ISR
 */

#include "config.h" //includes general configuration and declarations

char cycle = 0;

void main() {
    
    //Initiation process
    B_init();
    TMR3_init();
    Mod_Correction_Init();
    Servo_Init();
    
    for(;;){
        if(cycle){
            //LATA5 = RC4;
         
            //Correction module main routine
            if(!PID1CONbits.BUSY)UpdateCorrection();
            StartPID();
            
            Drive();
            
            
            cycle = 0;
        }        
    }
}

void interrupt ISR(){
    if(PIR5bits.TMR3IF){
        //main routine timing (5ms)
        cycle=1;
        
        TMR3H = TMR3H_INIT;
        TMR3L = TMR3L_INIT;
        PIR5bits.TMR3IF = 0;
    }
}