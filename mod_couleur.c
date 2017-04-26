#include "config.h"

char Couleur = 0;
char n = 0;
unsigned int t = 0;
unsigned int freq_1 = 0;
unsigned int freq_2 = 0;
unsigned int freq_3 = 0;
unsigned int freq_4 = 0;
float rouge = 0;
float bleu = 0;
float vert = 0;

char sign = 0;

void mod_couleur() {
    if(Couleur){
            if(n == 0)
                freq_1 = t;//sans filtre
            else if (n == 1)
                freq_2 = t;//bleu
            else if (n == 2)
                freq_3 = t;//rouge
            else
                freq_4 = t;//vert

            Couleur = 0;

            n++;
            selection_filtre(n);
            T1GGO_nDONE = 1;
        }   
        if(n == 5){
            n = 0;
            S2 = 1;
            S3 = 0;
        }

        if(n == 4){
            bleu = freq_2 * 100.0f /freq_1;
            rouge = freq_3 * 100.0f /freq_1;
            vert = freq_4 * 100.0f /freq_1;
            if(bleu > 140 && rouge > 140){//0.35
                sign=1;//BLEU
            }
            if(rouge < 90 && bleu < 90){//0.35
                sign=2;//VERT
            }
            if(rouge > 95 && rouge < 105 && bleu > 95 && bleu < 105 && vert < 105){//0.6
                sign=3;//ROUGE
            }
            if(rouge > 105 && rouge < 140 && bleu > 105 && bleu < 140 && vert < 100){
                sign=0;//BLANC
            }    
        }
}

void mod_couleur_init(){
    OSCCON = 0b11110000;
    OPTION_REG = 0b11010101;
    
    S2 = 1;
    S3 = 0;
    
    T1CKIPPS = 0b00010110;
    
    T1CON = 0b10000001;
    
    TMR1H = 0;
    TMR1L = 0;
    
    T1GCON = 0b11110001;
    
    TMR1GIE = 1;
    TMR1IF = 1;
}

void selection_filtre(int a){
    if(a == 1){
        S2 = 0;
        S3 = 1; //bleu
    }
    else if(a == 2){
        S2 = 0;
        S3 = 0;  //rouge
    }
    else {
        S2 = 1;
        S3 = 1; //vert
    }
}