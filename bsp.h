/* 
 * File:   bsp.h
 * Author: Muttsu
 *
 * Created on February 10, 2017, 3:55 PM
 */

#ifndef BSP_H
#define	BSP_H

//GENERAL BOARD CONFIGURATIONS//////////////////////////////////////////////////
#define TMR0_INIT 100               //timer0 set to flag every ms
#define TMR3H_INIT 0x63
#define TMR3L_INIT 0xc0
////////////////////////////////////////////////////////////////////////////////

//PORT AND LATCH RESERVATION////////////////////////////////////////////////////
#define M0      RB4
#define M1      RB5

#define IR0     RC0
#define IR1     RC1
#define IR2     RC2
#define IR3     RC3
#define IR4     RC4
#define IR5     RC5
#define IR6     RC6
#define IR7     RC7

#define T_US    RB6
#define C_US    RB7

#define S2          LATA0
#define S3          LATA1
#define out         RA2
////////////////////////////////////////////////////////////////////////////////

void init(void);
void TMR3_init(void);

#endif	/* BSP_H */