#ifndef __SVPWM_H_
#define __SVPWM_H_

#include <stdint.h>
#include "main.h"

#define SQRT_3 1.7320
#define SQRT_3_2 0.8660

#define Ts      1           //Ts为Timer_Period
#define K       2/3

#define SinPointNum     200
#define Sin90Num        50         //SinPointNum/4 --> degree 90
#define Sin270Num       150        //SinPointNum3/4 -> degree 270
#define DoublePI        6.2831852

#define Time_CLK        20000000    //Timer Freq
#define Sin_Freq        50          //Sine Wave Freq
#define Tim1_Period     1000        //Timer Peroid

struct SVPWM
{
    float Ualpha;
    float Ubeta;
    float Ua;
    float Ub;
    float Uc;
    float Ta;       //A phase time
    float Tb;       //B phase time
    float Tc;       //C phase time
    float Udc;
};

extern TIM_HandleTypeDef htim1;
void singen(void);
uint16_t TIMx_Per_Set(float set_f);

#endif
