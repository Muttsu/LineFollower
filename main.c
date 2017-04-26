/*
 * File:   main.c
 * Author: Muttsu
 *
 * Created on February 8, 2017, 5:49 PM
 * Main entry point with the main routine and ISR
 */

#include "config.h" //includes general configuration and declarations

bit cycle = 0; //main routine semaphore

void main() {
    
    //Initiation process
    init();
    TMR3_init();
    
    mod_ultrason_init();
    mod_correction_init();
    mod_motor_init();
    mod_couleur_init();
    
    for(;;){
        if(cycle){
            mod_ultrason();
         
            mod_motor();
            
            mod_couleur();
            
            //End cycle
            cycle = 0;
        }        
    }
}

void interrupt ISR(){
    //main routine timing (5ms)
    if(PIR5bits.TMR3IF){
        //main routine timing (5ms)
        cycle=1;
        
        TMR3H = TMR3H_INIT;
        TMR3L = TMR3L_INIT;
        PIR5bits.TMR3IF = 0;
    }
    
    
    //ultrasound routine timing
    if(IOCIF)                           //interruption sur la broche RC3
    {
        if (!mesure_ultrason_done)T5CONbits.TMR5ON ^= 1;
        if (!T5CONbits.TMR5ON) mesure_ultrason_done = 1;
        
        IOCIF = 0;
        IOCCF3 = 0;
    }
    
    
    //color sensor routine timing
    if(TMR1GIF){
        t = (TMR1H << 8) | TMR1L;
        Couleur = 1;
        TMR1H = 0;
        TMR1L = 0;
        TMR1GIF = 0;
    }
}