/*
 * @Author: your name
 * @Date: 2021-07-23 19:56:39
 * @LastEditTime: 2021-07-24 12:11:57
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \MyCode\Inc\keypad.h
 */
#ifndef __KEYPAD_H__
#define __KEYPAD_H__

#include "main.h"
#include "string.h"

/*按键扫描函数*/
int KEY_SCAN(void);
/*按键行扫描函数*/
int KEY_ROW_SCAN(void);
int KEY_FUNCTION(void);

/*行阵列致低*/
#define KEY_CLO1_OUT_LOW    HAL_GPIO_WritePin(CLO1_GPIO_Port, CLO1_Pin, GPIO_PIN_RESET)
#define KEY_CLO2_OUT_LOW    HAL_GPIO_WritePin(CLO2_GPIO_Port, CLO2_Pin, GPIO_PIN_RESET)
#define KEY_CLO3_OUT_LOW    HAL_GPIO_WritePin(CLO3_GPIO_Port, CLO3_Pin, GPIO_PIN_RESET)
#define KEY_CLO4_OUT_LOW    HAL_GPIO_WritePin(CLO4_GPIO_Port, CLO4_Pin, GPIO_PIN_RESET)
/*行阵列致高*/
#define KEY_CLO1_OUT_HIGH   HAL_GPIO_WritePin(CLO1_GPIO_Port, CLO1_Pin, GPIO_PIN_SET)
#define KEY_CLO2_OUT_HIGH   HAL_GPIO_WritePin(CLO2_GPIO_Port, CLO2_Pin, GPIO_PIN_SET)
#define KEY_CLO3_OUT_HIGH   HAL_GPIO_WritePin(CLO3_GPIO_Port, CLO3_Pin, GPIO_PIN_SET)
#define KEY_CLO4_OUT_HIGH   HAL_GPIO_WritePin(CLO4_GPIO_Port, CLO4_Pin, GPIO_PIN_SET)


#endif
