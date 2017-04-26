#include "config.h"

char lancer_mesure_ultrason = 1;            //Sémaphore pour lancer la mesure de la distance   
char mesure_ultrason_done = 0;              //Sémaphore indiquant la fin de la mesure de la distance
char attente_ultrason = 0;                  //Sémaphore indiquant l'attente entre deux prise de mesure (recommendé de 50ms)
char attente_pulse = 0;                     //Sémaphore indiquant l'attente pendant le pulse qui commence la mesure (temps minimum d'attente: 10us)

unsigned int temps_ultrason;
char distance_objet;

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
    TRISB7 = 1;         //Broche sur laquelle je reçois le signal du capteur
    TRISB6 = 0;         //Broche sur laquelle j'envoi le signal pour démarrer l'analyse de distance
    
    IOCBN7 = 1;         //Interruption sur le front haut et bas de la broche RC3
    IOCBP7 = 1;
}

void analyse_distance()
{
    temps_ultrason = (TMR5L | (TMR5H<<8)); 
    distance_objet = temps_ultrason/57/8;   //Le 57 est donnée dans la fiche technique du capteur, le 8 viens du cycle d'horloge 
    mesure_ultrason_done = 0;  
    attente_ultrason = 1;                   //Attente pour le bon fonctionnement du capteur
}

void pulse_time()
{
    TMR5H = 0;
    TMR5L = 0;
    T_US = 1;                               //début du pulse pour engager la prise de donnée
    attente_pulse = 1;                      //annonce l'attente de au moins 10us
    lancer_mesure_ultrason = 0;             
}