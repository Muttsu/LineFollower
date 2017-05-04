/*
 * File:   main.c
 * Author: Muttsu
 *
 * Created on February 8, 2017, 5:49 PM
 * Main entry point with the main routine and ISR
 */

#include "config.h" //includes general configuration and declarations

bit cycle = 0; //main routine semaphore
bit Couleur = 0;

void main() {
    
    //Initiation process
    bsp_init();
    TMR3_init();
    
    mod_ultrason_init();
    mod_correction_init();
    mod_motor_init();
    mod_couleur_init();
    
    for(;;){
            
//        if(Couleur){//routine pour capturer la couleur
//            t = (TMR1H << 8) | TMR1L;
//            TMR1H = 0;
//            TMR1L = 0;
//            mod_couleur();
//            Couleur = 0;
//        }
        
        if(cycle){//routine principale
            mod_ultrason();
            
            //Correction module main routine
            //Uses mod_correction
            if(!PID1CONbits.BUSY)UpdateCorrection();
            StartPID();
         
            mod_motor();
            //la routine de correction est incluse dans mod_motor()
            
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
    if(INTCONbits.IOCIF)                           //interruption sur la broche RB3
    {
        if (!mesure_ultrason_done)T5CONbits.TMR5ON ^= 1;
        if (!T5CONbits.TMR5ON) mesure_ultrason_done = 1;
        
        INTCONbits.IOCIF = 0;
        IOCBFbits.IOCBF7 = 0;
    }
    
    
    //color sensor routine timing
    if(PIR1bits.TMR1GIF){
        Couleur = 1;
        PIR1bits.TMR1GIF = 0;
    }
}