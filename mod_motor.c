#include "config.h"

unsigned char state;
int vitesse=0;
//state designe le mode des moteurs
//0: stop
//1: vitesse lente
//2: vitesse normale
//3: stop

void mod_motor_init(){      //procesus obtenu de la fiche de documentation
    RB4PPS = 0b00001110;
    RA5PPS = 0b00001110;    //DEL4
    RA1PPS = 0b00001111;
    RB5PPS = 0b00001111;    //DEL5
    TRISAbits.TRISA5 = 0b0;
    TRISAbits.TRISA1 = 0b0;
    TRISBbits.TRISB4 = 0b1;
    TRISBbits.TRISB5 = 0b1;
    PWM3CON = 0;
    PWM4CON = 0;
    PR2 = PERIOD2;
    PWM3DCH = 0x00;
    PWM3DCL = 0x00;
    PWM4DCH = 0x00;
    PWM4DCL = 0x00;
    
    PIR1bits.TMR2IF = 0b0; 
    T2CONbits.CKPS = 0b000;
    T2CONbits.ON = 1;
    
    while(!TMR2IF);         //attendre TMR2IF=1; il ne faut pas que TMR2 cause une interruption
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB5 = 0;
    PWM3CONbits.EN = 1;
    PWM4CONbits.EN = 1;
}

void drive(){
    signed long value = correction;
    if(value<(-vitesse))value=(-vitesse);
    if(value>vitesse)value=vitesse;
    unsigned int l = vitesse + value;
    unsigned int r = vitesse - value;
    PWM3DCH = (unsigned short)(l >> 2);
    PWM3DCL = (unsigned short)((l & 0b11) << 6);
    PWM4DCH = (unsigned short)(r >> 2);
    PWM4DCL = (unsigned short)((r & 0b11) << 6);
}
void stop(){
    PWM3DCH = 0x00;
    PWM3DCL = 0x00;
    PWM4DCH = 0x00;
    PWM4DCL = 0x00;
}

void mod_motor(){  
    switch(state){
        case 0:
            if(vitesse!=0)vitesse-=32;   
            else vitesse=0;
            drive();
            break;
        case 1:
            vitesse=DCSMSP;
            drive();
            break;
        case 2:
            if(vitesse<DCSP)vitesse+=16;;
            drive();
            break;
        case 3:
            vitesse = 0;
            drive();
            break;
        default:
            if(vitesse)vitesse-=32;
            drive();
            break;
    }
}