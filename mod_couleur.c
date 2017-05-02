#include "config.h"

char Couleur = 0;
unsigned int t = 0;

void mod_couleur() {
    static unsigned int freq_1,freq_2,freq_3,freq_4;
    static float rouge,bleu,vert;
    static char n = 0;
    if(Couleur){
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
                
                bleu = freq_2 * 100.0f /freq_1;
                rouge = freq_3 * 100.0f /freq_1;
                vert = freq_4 * 100.0f /freq_1;
                if(rouge > 105 && rouge < 140 && bleu > 105 && bleu < 140 && vert < 100){
                    state = 0;//BLANC
                } 
                if(bleu > 140 && rouge > 140){//0.35
                    state = 1;//BLEU
                }
                if(rouge < 90 && bleu < 90){//0.35
                    state = 2;//VERT
                }
                if(rouge > 95 && rouge < 105 && bleu > 95 && bleu < 105 && vert < 105){//0.6
                    state = 3;//ROUGE
                }
                else state = ERROR_STATE;
                
                break;
        }

        Couleur = 0;
        
        n++;
        if(n==4)n=0;
        selection_filtre(n);
        T1GGO_nDONE = 1;
    }
}

void mod_couleur_init(){
    OSCCON = 0b11110000;
    OPTION_REG = 0b11010101;
    
    TRISAbits.TRISA0 = 0b0;
    TRISAbits.TRISA1 = 0b0;
    selection_filtre(0);
    
    TRISAbits.TRISA2 = 1;
    T1CKIPPS = 0b00000010;
    
    T1CON = 0b10000001;
    
    TMR1H = 0;
    TMR1L = 0;
    
    T1GCON = 0b11110001;
    
    PIE1bits.TMR1GIE = 1;
    PIE1bits.TMR1IE = 1;
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