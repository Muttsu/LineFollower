/* 
 * File:   mod_correction.h
 * Author: Muutt
 *
 * Created on February 10, 2017, 11:18 AM
 */

#ifndef MOD_CORRECTION_H
#define	MOD_CORRECTION_H




//PROTOTYPES////////////////////////////////////////////////////////////////////
void mod_correction_init(void);
void PID_Init(void);

void UpdateIR(void);
uint GetPos(void);

long GetCorrection(void); //do not use, for tests only

void StartPID(void);
void UpdateCorrection(void);
////////////////////////////////////////////////////////////////////////////////
    
//////CONFIGURATIONS////////////////////////////////////////////////////////////
#define K1 201      //default: 201
#define K2 -401     //default: -401
#define K3 200      //default: 200
#define DIVIDER 1   //2^DIVIDER
////////////////////////////////////////////////////////////////////////////////




#endif	/* MOD_CORRECTION_H */
