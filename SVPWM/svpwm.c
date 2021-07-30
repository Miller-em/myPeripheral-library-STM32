#include "math.h"
#include "svpwm.h"

struct SVPWM Svpwm;
float Sin_Table[SinPointNum];

void singen(void){
    uint16_t i;
    for (i=0; i<SinPointNum; i++){
        Sin_Table[i] = sin(DoublePI*i/SinPointNum);
    }
}

void Svpwm_Module(uint16_t Point){
    uint8_t N = 0, Sector=0;
    uint8_t A,B,C;
    float t1, t2;
    float sqrt_3 = SQRT_3;
    float tmp;
    float m = K;
    float Sintheta, Costheta;       //Sine, Cos table
    float U1, U2, U3;
    float ta, tb, tc;
    float phaseU, phaseV, phaseW;
    float Ubeta, Ualpha;

    Svpwm.Udc = 1;
    if (Point < Sin270Num)
        Costheta = Sin_Table[Point+Sin90Num];
    else
        Costheta = Sin_Table[Point-Sin270Num];  //Ualpha = U*cos(theta), Ubeta = U*sin(theta)
    Sintheta = Sin_Table[Point];

    // calc sector
    Ubeta = 0.56 * Costheta;
    Ualpha = -0.56 * Sintheta;
    U1 = Ubeta;
    U2 = (sqrt_3*Ualpha - Ubeta) / 2;
    U3 = -(sqrt_3*Ualpha + Ubeta) / 2;
    A = (U1 > 0) ? 1 : 0;
    B = (U2 > 0) ? 1 : 0;
    C = (U3 > 0) ? 1 : 0;
    N = 4*C + 2*B + A;
    switch (N)
    {
        case 3:
            Sector = 1;
            break;
        case 1:
            Sector = 2;
            break;
        case 5:
            Sector = 3;
            break;
        case 4:
            Sector = 4;
            break;
        case 6:
            Sector = 5;
            break;
        case 2:
            Sector = 6;
            break;
    }
    switch (Sector) {
        case 1:
            t1 = (sqrt_3*Ts/Svpwm.Udc)*U2;
            t2 = (sqrt_3*Ts/Svpwm.Udc)*U1;
            break;
        case 2:
            t1 = -(sqrt_3*Ts/Svpwm.Udc)*U2;
            t2 = -(sqrt_3*Ts/Svpwm.Udc)*U3;
            break;
        case 3:
            t1 = (sqrt_3*Ts/Svpwm.Udc)*U1;
            t2 = (sqrt_3*Ts/Svpwm.Udc)*U3;
            break;
        case 4:
            t1 = -(sqrt_3*Ts/Svpwm.Udc)*U1;
            t2 = -(sqrt_3*Ts/Svpwm.Udc)*U2;
            break;
        case 5:
            t1 = (sqrt_3*Ts/Svpwm.Udc)*U3;
            t2 = (sqrt_3*Ts/Svpwm.Udc)*U2;
            break;
        case 6:
            t1 = -(sqrt_3*Ts/Svpwm.Udc)*U3;
            t2 = -(sqrt_3*Ts/Svpwm.Udc)*U1;
            break;
    }
    ta = (1 - t1 - t2) / 2;     //tmin
    tb = ta + t1;   //tmid
    tc = tb + t2;   //tmax
    switch (Sector) {
        case 1:
            phaseU = ta;
            phaseV = tb;
            phaseW = tc;
            break;
        case 2:
            phaseU = tb;
            phaseV = ta;
            phaseW = tc;
            break;
        case 3:
            phaseU = tc;
            phaseV = ta;
            phaseW = tb;
            break;
        case 4:
            phaseU = tc;
            phaseV = tb;
            phaseW = ta;
            break;
        case 5:
            phaseU = tb;
            phaseV = tc;
            phaseW = ta;
            break;
        case 6:
            phaseU = ta;
            phaseV = tc;
            phaseW = tb;
            break;
    }
    TIM1->CCR1 = Tim1_Period*phaseU;
    TIM1->CCR2 = Tim1_Period*phaseV;
    TIM1->CCR3 = Tim1_Period*phaseW;
}

/************************************************************************************************************/
//Tim init function, Set the peroid of Timx
//[input]：TGA_FREQ
//         type: unsigned short
//         desc: target freq of Sine wave，range：20~300HZ
/************************************************************************************************************/
uint16_t TIMx_Per_Set(float set_f)
{
    static float temp;
    temp = Time_CLK;				// Tim Clock	Tcy = 1/Time_CLK；Tm = 1/Sin_FRQ； Tc=Tm/Tcy;
    temp /= set_f;					// the Cnt in one cycle of sine wave's freq as Sin_FRQ
    temp /= SinPointNum;			// The Cnt value corresponding to one cycle of the carrier
    temp /= 2;						// Cycle cnt value in addition and subtraction mode
    return (uint16_t)temp;
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static uint16_t i = 0;

    if(htim==&htim1)
    {
        HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
        Svpwm_Module(i++);
        HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
        if(i==SinPointNum)
            i = 0;
    }
}