/*
 * @Author: Zhou Xiaozong
 * @Date: 2021-07-25 18:53:09
 * @LastEditTime: 2021-07-25 18:54:22
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MyCode\OLED_U8g2\u8g2_delay_gpio.c
 */
#include "u8g2.h"


void delay_us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = SysTick->VAL;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = SysTick->VAL;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = SysTick->VAL;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;
    }
}



uint8_t STM32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,
		void *arg_ptr) {
	switch (msg) {
	case U8X8_MSG_DELAY_100NANO:		// delay arg_int * 100 nano seconds
		__NOP();
		break;
	case U8X8_MSG_DELAY_10MICRO:		// delay arg_int * 10 micro seconds
		for (uint16_t n = 0; n < 320; n++) {
			__NOP();
		}
		break;
	case U8X8_MSG_DELAY_MILLI:			       // delay arg_int * 1 milli second
		HAL_Delay(1);
		break;
	case U8X8_MSG_DELAY_I2C:// arg_int is the I2C speed in 100KHz, e.g. 4 = 400 KHz
		delay_us(5);
		break;			// arg_int=1: delay by 5us, arg_int = 4: delay by 1.25us
	case U8X8_MSG_GPIO_I2C_CLOCK:	// arg_int=0: Output low at I2C clock pin
		if (arg_int == 1) // arg_int=1: Input dir with pullup high for I2C clock pin
			HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, GPIO_PIN_SET);
		else if (arg_int == 0)
			HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, GPIO_PIN_RESET);
		break;
	case U8X8_MSG_GPIO_I2C_DATA:		// arg_int=0: Output low at I2C data pin
		if (arg_int == 1) // arg_int=1: Input dir with pullup high for I2C data pin
			HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, GPIO_PIN_SET);
		else if (arg_int == 0)
			HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, GPIO_PIN_RESET);
		break;
	case U8X8_MSG_GPIO_MENU_SELECT:
		u8x8_SetGPIOResult(u8x8, /* get menu select pin state */0);
		break;
	case U8X8_MSG_GPIO_MENU_NEXT:
		u8x8_SetGPIOResult(u8x8, /* get menu next pin state */0);
		break;
	case U8X8_MSG_GPIO_MENU_PREV:
		u8x8_SetGPIOResult(u8x8, /* get menu prev pin state */0);
		break;
	case U8X8_MSG_GPIO_MENU_HOME:
		u8x8_SetGPIOResult(u8x8, /* get menu home pin state */0);
		break;
	default:
		u8x8_SetGPIOResult(u8x8, 1);			         // default return value
		break;
	}
	return 1;
}