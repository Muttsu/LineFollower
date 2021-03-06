#include "config.h"

char lancer_mesure_ultrason = 0;            //Sémaphore pour lancer la mesure de la distance   
char mesure_ultrason_done = 0;              //Sémaphore indiquant la fin de la mesure de la distance
char attente_ultrason = 0;                  //Sémaphore indiquant l'attente entre deux prise de mesure (recommendé de 50ms)
char attente_pulse = 0;                     //Sémaphore indiquant l'attente pendant le pulse qui commence la mesure (temps minimum d'attente: 10us)

unsigned int temps_ultrason;
unsigned int distance_objet;

// *** Initialisations générales ***
void mod_ultrason()
{
    //timing
    static char pulse = 0;
    static char att_ult = 0;    
    if(attente_pulse && (++pulse == DELAI_10MSEC))       // attente de 10ms pour le pulse en début d'analyse de distance                   
    {
        T_US = 0;                                                           
        lancer_mesure_ultrason = 1;                                         
        attente_pulse = 0;                                                  
        pulse = 0;                                                          
    }
    if(attente_ultrason && (++att_ult == DELAI_50MSEC))  //attente obligatoire pour le bon fonctionnement du capteur              
    {
        lancer_mesure_ultrason = 1;                                         
        attente_ultrason = 0;                                               
        att_ult = 0;                                                        
    }
    
    if(lancer_mesure_ultrason)
    {
        pulse_time();
    }
    else if(mesure_ultrason_done)
    {
        analyse_distance();
        mesure_ultrason_done = 0;
    }
}

void mod_ultrason_init()
{    
    TRISBbits.TRISB7 = 1;         //Broche sur laquelle je reçois le signal du capteur
    TRISBbits.TRISB6 = 0;         //Broche sur laquelle j'envoi le signal pour démarrer l'analyse de distance
    
    
    
    IOCBNbits.IOCBN7 = 1;         //Interruption sur le front haut et bas de la broche RB7
    IOCBPbits.IOCBP7 = 1;
    
    lancer_mesure_ultrason = 1;
}

void analyse_distance()
{
    static char test=0;
    
    temps_ultrason = (TMR5H);
    temps_ultrason <<= 8;
    temps_ultrason |= TMR5L; 
    attente_ultrason = 1;                   //Attente pour le bon fonctionnement du capteur
    
    test<<=1;
    if(temps_ultrason < 12000)test|=0b1; //lorsque il n'y a pas dobstacle la distance_objet donne 8 alors on lexclus du if
    if(test==0xff)state=3;//stop
    else if(!test)state=2;//vitesse normale
}

void pulse_time()
{
    TMR5H = 0;
    TMR5L = 0;
    T_US = 1;                               //début du pulse pour engager la prise de donnée
    attente_pulse = 1;                      //annonce l'attente de au moins 10us
    lancer_mesure_ultrason = 0;             
}