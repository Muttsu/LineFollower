#include "config.h"

unsigned char state;
//state designe le mode des moteurs
//0: vitesse normale
//1: vitesse lente
//2: non implemente
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
    signed long value = (correction<-DCSP?-DCSP:(correction>DCSP?DCSP:correction));
    unsigned int l = DCSP + value;
    unsigned int r = DCSP - value;
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
void slow_drive(){
    signed long value = (correction<-DCSMSP?-DCSMSP:(correction>DCSMSP?DCSMSP:correction));
    unsigned int l = DCSMSP + value;
    unsigned int r = DCSMSP - value;
    PWM3DCH = (unsigned short)(l >> 2);
    PWM3DCL = (unsigned short)((l & 0b11) << 6);
    PWM4DCH = (unsigned short)(r >> 2);
    PWM4DCL = (unsigned short)((r & 0b11) << 6);
}

void mod_motor(){  
    switch(state){
        case 0:
            drive();
            
            break;
        case 1:
            //BLEU;
            slow_drive();
            if(!PID1CONbits.BUSY)UpdateCorrection();
            StartPID();
            break;
        case 2:
            //VERT;
            drive();
            
            break;
        case 3:
            //ROUGE;
            stop();
            break;
        default:
            break;
    }
}