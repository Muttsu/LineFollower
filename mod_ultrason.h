#ifndef MOD_ULTRASON_H
#define	MOD_ULTRASON_H

// *** Définitions d'étiquettes (macros) ***
  
#define DELAI_50MSEC    10
#define DELAI_10MSEC    2
#define TMR5L_INIT      0
#define TMR5H_INIT      0

extern bit lancer_mesure_ultrason;            //Sémaphore pour lancer la mesure de la distance   
extern bit mesure_ultrason_done;              //Sémaphore indiquant la fin de la mesure de la distance
extern bit attente_ultrason;                  //Sémaphore indiquant l'attente entre deux prise de mesure (recommendé de 50ms)
extern bit attente_pulse;                     //Sémaphore indiquant l'attente pendant le pulse qui commence la mesure (temps minimum d'attente: 10us)

extern unsigned int temps_ultrason;
extern char distance_objet;

// *** Prototypes ***
void analyse_distance(void);
void mod_ultrason_init(void);
void pulse_time(void);
void mod_ultrason(void);

#endif	/* MOD_ULTRASON_H */