/*
 * @Author: ZhouXiaozong
 * @Date: 2021-07-23 19:56:39
 * @LastEditTime: 2021-07-24 12:33:43
 * @LastEditors: Please set LastEditors
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
#define KEY_COL1_OUT_LOW    HAL_GPIO_WritePin(COL1_GPIO_Port, COL1_Pin, GPIO_PIN_RESET)
#define KEY_COL2_OUT_LOW    HAL_GPIO_WritePin(COL2_GPIO_Port, COL2_Pin, GPIO_PIN_RESET)
#define KEY_COL3_OUT_LOW    HAL_GPIO_WritePin(COL3_GPIO_Port, COL3_Pin, GPIO_PIN_RESET)
#define KEY_COL4_OUT_LOW    HAL_GPIO_WritePin(COL4_GPIO_Port, COL4_Pin, GPIO_PIN_RESET)
/*行阵列致高*/
#define KEY_COL1_OUT_HIGH   HAL_GPIO_WritePin(COL1_GPIO_Port, COL1_Pin, GPIO_PIN_SET)
#define KEY_COL2_OUT_HIGH   HAL_GPIO_WritePin(COL2_GPIO_Port, COL2_Pin, GPIO_PIN_SET)
#define KEY_COL3_OUT_HIGH   HAL_GPIO_WritePin(COL3_GPIO_Port, COL3_Pin, GPIO_PIN_SET)
#define KEY_COL4_OUT_HIGH   HAL_GPIO_WritePin(COL4_GPIO_Port, COL4_Pin, GPIO_PIN_SET)


#endif
