#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>

#include "MOD_Correction.h"

#define SET_POINT 3500
#define uint unsigned int

int CalcError(uint Kp, uint Ki, uint Kd, uint DIVIDER){
    uint sensors[]={0,0,0,0,0,0,0,0};
    uint meanSum = 0;
    uint sum = 0;
    for (char i = 0; i < 6; i++){
        /*set sensors i/o
         following code assumes that i/o array is at correct value*/
        meanSum += sensors[i]*i*1000;
        sum += sensors[i];
    }
    if (sum!=0){
        uint position = meanSum/sum;
        uint proportional = position - SET_POINT;
        static uint _proportional = 0;
        static uint integral = 0;
        integral += proportional;
        uint differential = proportional - _proportional;
        uint error = Kp*+Ki*integral+Kd*differential;
        _proportional = proportional;
        return error/DIVIDER;
    }
    else{
        return -1;
    }
}