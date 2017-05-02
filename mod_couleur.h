#ifndef COULEUR_H
#define	COULEUR_H

extern char Couleur;
extern unsigned int t;

void mod_couleur_init(void);
void selection_filtre(int n);
void mod_couleur(void);

#define ERROR_STATE 0//le mode des moteurs lorsquil y a une erreur a la detection des couleurs

#endif	/* COULEUR_H */