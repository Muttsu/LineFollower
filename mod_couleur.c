#include "config.h"

unsigned int t = 0;

void mod_couleur() {
    static unsigned int freq_1,freq_2,freq_3,freq_4;
    static char rouge,bleu,vert;
    static char t_blanc,t_rouge,t_bleu,t_vert;
    static char n = 0;
    
    switch(n){
        case 0: 
            freq_1 = t;
            break;
        case 1:
            freq_2 = t;
            break;
        case 2:
            freq_3 = t;
            break;
        case 3:
            freq_4 = t;

            t_blanc<<=1;
            t_rouge<<=1;
            t_bleu<<=1;
            t_vert<<=1;
            
            bleu = freq_2 * 100 /freq_1;
            rouge = freq_3 * 100 /freq_1;
            vert = freq_4 * 100 /freq_1;
            if(rouge > 105 && rouge < 140 && bleu > 105 && bleu < 140 && vert < 100){
                t_blanc|=0b1;//BLANC
            } 
            if(bleu > 140 && rouge > 140){//0.35
                t_bleu|=0b1;//BLEU
            }
            if(rouge < 90 && bleu < 90){//0.35
                t_vert|=0b1;//VERT
            }
            if(rouge > 95 && rouge < 105 && bleu > 95 && bleu < 105 && vert < 105){//0.6
                t_rouge|=0b1;//ROUGE
            }
            else state = ERROR_STATE;
            
            if((t_rouge|0xf0)==0xff) state=0;
            else if((t_bleu|0xf0)==0xff) state=1;
            else if((t_vert|0xf0)==0xff) state=2;
            else if((t_blanc|0xf0)==0xff) state=2;
            else state=2;

            break;
    }
    n++;
    if(n == 4) n = 0;
    selection_filtre(n);
    TMR0 = 0;
    T1GCONbits.T1GGO_nDONE = 1;
}

void mod_couleur_init(){
    OSCCON = 0b11110000;
    OPTION_REG = 0b11010101;
    
    TRISAbits.TRISA2 = 0b0;
    TRISAbits.TRISA3 = 0b0;
    selection_filtre(0);
    
    TRISAbits.TRISA0 = 1;
    T1CKIPPS = 0b00000000;
    
    T1CON = 0b10000001;
    
    TMR1H = 0;
    TMR1L = 0;
    
    T1GCON = 0b11110001;
    
    PIE1bits.TMR1GIE = 1;
    PIR1bits.TMR1IF = 1;
}

void selection_filtre(int n){
    switch(n){
        case 0:
            S2 = 1;
            S3 = 0; //aucun filtre
            break;
        case 1:
            S2 = 0;
            S3 = 1; //bleu
            break;
        case 2:
            S2 = 0;
            S3 = 0; //rouge
            break;
        case 3:
            S2 = 1;
            S3 = 1; //vert
            break;
        default:
            break;
    }
}