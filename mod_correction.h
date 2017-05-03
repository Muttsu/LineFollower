/* 
 * File:   mod_correction.h
 * Author: Muutt
 *
 * Created on February 10, 2017, 11:18 AM
 */

#ifndef MOD_CORRECTION_H
#define	MOD_CORRECTION_H


extern long correction;


//PROTOTYPES////////////////////////////////////////////////////////////////////
void mod_correction_init(void);
void PID_Init(void);

void UpdateIR(void);
uint GetPos(void);

void StartPID(void);
void UpdateCorrection(void);
////////////////////////////////////////////////////////////////////////////////

//////CONFIGURATIONS////////////////////////////////////////////////////////////
#define K1 1002      //default: 201
#define K2 -1000     //default: -401
#define K3 0000      //default: 200
#define DIVIDER 4   //2^DIVIDER
////////////////////////////////////////////////////////////////////////////////




#endif	/* MOD_CORRECTION_H */
