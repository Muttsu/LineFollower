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
    //IR[3] = 1;
    //IR[4] = 1;
    
    PID_Init();
    long val0 = 0;
    uint pos = 0;
    val0 = GetPID();
    pos = GetPos();
    long val1 = 0;
    val1 = GetPID();
    long val2 = 0;
    val2 = GetPID();
    extern char IR[];
    IR[6] = IR[7] = 0;
    IR[3] = IR[4] = 1;
    pos= GetPos();
    long val3 = 0;
    val3 = GetPID();
    long val4 = 0;
    val4 = GetPID();
    long val5 = 0;
    val5 = GetPID();
    long val6 = 0;
    val6 = GetPID();
    long val7 = 0;
    val7 = GetPID();
    long val8 = 0;
    val8 = GetPID();
    long val9 = 0;
    val9 = GetPID();
    long vala = 0;
    vala = GetPID();
    //value = GetError();
    for(;;){
        
    }
}

void interrupt ISR(){
    if(TMR0IF){
        
        TMR0IF = 0;
        TMR0 = TMR0_INIT;
    }
}