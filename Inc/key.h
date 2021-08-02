#ifndef __KEY_H
#define __KEY_H
#include "main.h"

#define KEY1  HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)//读取按键1
#define KEY2  HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin)//读取按键2
#define KEY3  HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin)//读取按键3
#define KEY4  HAL_GPIO_ReadPin(KEY4_GPIO_Port, KEY4_Pin)//读取按键4


#define KEY1_PRES	1		//KEY1
#define KEY2_PRES	2		//KEY2
#define KEY3_PRES	3		//KEY3
#define KEY4_PRES	4		//KEY4

u8 KEY_Scan(u8 mode);  	//按键扫描函数
void KEY_HANDLE(void);
#endif