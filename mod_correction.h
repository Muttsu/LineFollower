/* 
 * File:   mod_correction.h
 * Author: Muutt
 *
 * Created on February 10, 2017, 11:18 AM
 */

#ifndef MOD_CORRECTION_H
#define	MOD_CORRECTION_H




//PROTOTYPES////////////////////////////////////////////////////////////////////
void Mod_Correction_Init(void);
void PID_Init(void);

void UpdateIR(void);
uint GetPos(void);

long GetCorrection(void); //do not use, for tests only

void StartPID(void);
void UpdateCorrection(void);
////////////////////////////////////////////////////////////////////////////////
    
//////CONFIGURATIONS////////////////////////////////////////////////////////////
#define K1 4020025
#define K2 -8020000
#define K3 4000000
#define DIVIDER 1
////////////////////////////////////////////////////////////////////////////////




#endif	/* MOD_CORRECTION_H */
