
/*
 * @Author: Zhou Xiaozong
 * @Date: 2021-07-23 19:56:57
 * @LastEditTime: 2021-07-24 02:11:00
 * @LastEditors: Please set LastEditors
 * @Description: This a lib for keypad with stm32 hal_library
 * @FilePath: \MyCode\Keypad\keypad.c
 */
#include "keypad.h"

u8 Key_row[1]={0xff};		//保存按键扫描情况的状态数组

/**
 * @description: 扫描按键行
 * @param {void}
 * @return {1~4, 对应1~4行按键位置}
 */
char KEY_ROW_SCAN(void)
{
    //* 行扫描
    Key_row[0] = HAL_GPIO_ReadPin(ROW1_GPIO_Port, ROW1_Pin)<<3;
    Key_row[0] = Key_row[0] | HAL_GPIO_ReadPin(ROW2_GPIO_Port, ROW2_Pin)<<2;
    Key_row[0] = Key_row[0] | HAL_GPIO_ReadPin(ROW3_GPIO_Port, ROW3_Pin)<<1;
    Key_row[0] = Key_row[0] | HAL_GPIO_ReadPin(ROW4_GPIO_Port, ROW4_Pin);

    if (Key_row[0] != 0x0f){     //* 如果按键按下
        HAL_Delay(10);          //消抖
        if (Key_row[0] != 0x0f){
            switch (Key_row[0])
            {
            case 0x07:          //! 0111 
                return 1;
            case 0x0b:
                return 2;
            case 0x0d:
                return 3;
            case 0x0e:
                return 4;
            default:
                return 0;
            }
        }
        else return 0;
    }
    else return 0;
}

/**
 * @description: 4*4按键扫描
 * @param {void}
 * @return {0~16, 对应16个按键}
 */
char KEY_SCAN(){
    char Key_Num=0;         //*1-16对应的按键数
    char Key_row_Num=0;     //*行数

    KEY_CLO1_OUT_LOW;
    if ((Key_row_Num=KEY_ROW_SCAN()) != 0){
        while (KEY_ROW_SCAN()!=0);      //! 抬手检测
        Key_Num = 0 + Key_row_Num;
    }
    KEY_CLO1_OUT_HIGH;

    KEY_CLO2_OUT_LOW;
    if ((Key_row_Num=KEY_ROW_SCAN()) != 0){
        while (KEY_ROW_SCAN()!=0)
        Key_Num = 4 + Key_row_Num;
    }
    KEY_CLO2_OUT_HIGH;

    KEY_CLO3_OUT_LOW;
    if ((Key_row_Num=KEY_ROW_SCAN()) != 0){
        while (KEY_ROW_SCAN()!=0)
        Key_Num = 8 + Key_row_Num;
    }
    KEY_CLO3_OUT_HIGH;

    KEY_CLO4_OUT_LOW;
    if ((Key_row_Num=KEY_ROW_SCAN()) != 0){
        while (KEY_ROW_SCAN()!=0)
        Key_Num = 12 + Key_row_Num;
    }
    KEY_CLO4_OUT_HIGH;
    return Key_Num;
}

/**
 * @description: 执行按下按键后的操作
 * @param {void}
 * @return {void}
 */
char KEY_FUNCTION(void)
{
    char num = KEY_SCAN();
    if (0<num && num>17){
    	return num;
    }
    return num;
}
