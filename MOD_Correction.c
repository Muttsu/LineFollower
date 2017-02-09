#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>

#define Kp 1
#define Ki 1
#define Kd 1
#define DIVIDER 1
#define SET_POINT 3500

uint16_t CalcError();

uint16_t CalcError(){
    uint16_t sensors[]={0,0,0,1,1,0,0,0};
    uint16_t meanSum = 0;
    uint16_t sum = 0;
    for (char i = 0; i < 6; i++){
        /*set sensors i/o
         following code assumes that i/o array is at correct value*/
        meanSum += sensors[i]*i*1000;
        sum += sensors[i];
    }
    if (sum!=0){
        uint16_t position = meanSum/sum;
        uint16_t proportional = position - SET_POINT;
        static uint16_t _proportional = 0;
        static uint16_t integral = 0;
        integral += proportional;
        uint16_t differential = proportional - _proportional;
        uint16_t error = Kp*+Ki*integral+Kd*differential;
        _proportional = proportional;
        return error/DIVIDER;
    }
    else{
        return -1;
    }
}
