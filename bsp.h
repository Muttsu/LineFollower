/* 
 * File:   bsp.h
 * Author: Muttsu
 *
 * Created on February 10, 2017, 3:55 PM
 */

#ifndef BSP_H
#define	BSP_H

//GENERAL BOARD CONFIGURATIONS//////////////////////////////////////////////////
#define GENERAL_INTERRUPT_ENABLE 1 //set to 1 to enable interrupts
#define TMR0_IE 1
#define TMR0_INIT 56             //timer0 set to flag every ms
#define TMR0_PS 1               //
////////////////////////////////////////////////////////////////////////////////

//PORT AND LATCH RESERVATION////////////////////////////////////////////////////
#define IR0 RC0
#define IR1 RC1
#define IR2 RC2
#define IR3 RC3
#define IR4 RC4
#define IR5 RC5
#define IR6 RC6
#define IR7 RC7
////////////////////////////////////////////////////////////////////////////////

void init(void);

#endif	/* BSP_H */