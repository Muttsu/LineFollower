#ifndef COULEUR_H
#define	COULEUR_H

extern char Couleur;
extern char n;
extern unsigned int t;
extern unsigned int freq_1;
extern unsigned int freq_2;
extern unsigned int freq_3;
extern unsigned int freq_4;
extern float rouge;
extern float bleu;
extern float vert;

extern char sign;

void mod_couleur_init(void);
void selection_filtre(int a);
void mod_couleur(void);

#endif	/* COULEUR_H */