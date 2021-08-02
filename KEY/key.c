#include "key.h"


u8 KEY_Scan(u8 mode)
{
    static u8 key_up=1;//按键按松开标志
    if(mode)key_up=1;  //支持连按
    if(key_up&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0))
    {
        HAL_Delay(10);//去抖动
        key_up=0;
        if(KEY1==0)return KEY1_PRES;
        else if(KEY2==0)return KEY2_PRES;
        else if(KEY3==0)return KEY3_PRES;
        else if(KEY4==0)return KEY4_PRES;
    }else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)key_up=1;
    return 0;// 无按键按下
}

void KEY_HANDLE(void){
    int t=0;
    t=KEY_Scan(0);		//得到键值
    switch(t)
    {
        case KEY1_PRES:
            PWM_k += 0.01;
            PWM_k = (PWM_k >= 1) ? 1 : PWM_k;
            break;
        case KEY2_PRES:
            PWM_k -= 0.01;
            PWM_k = (PWM_k <= 0) ? 0 : PWM_k;
            break;
        case KEY3_PRES:
            Sin_F += 1;
            Sin_F = (Sin_F >= 150) ? 150 : Sin_F;
            TIM2->ARR = (int)(50000/Sin_F)-1;
            break;
        case KEY4_PRES:
            Sin_F -= 1;
            Sin_F = (Sin_F <= 0) ? 0 : Sin_F;
            TIM2->ARR = (int)(50000/Sin_F)-1;
            break;
        default:
            HAL_Delay(10);
    }
}
