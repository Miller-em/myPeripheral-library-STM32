/*
 * @Author: your name
 * @Date: 2021-08-15 17:14:13
 * @LastEditTime: 2021-08-15 17:39:54
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \AD7606_F411CEU\MyCode\Inc\ad7606.h
 */
#ifndef __AD7606_H
#define __AD7606_H

#include "main.h"

/* 开关全局中断的宏 */
#define ENABLE_INT()	__set_PRIMASK(0)	/* 使能全局中断 */
#define DISABLE_INT()	__set_PRIMASK(1)	/* 禁止全局中断 */

/* 每个样本2字节，采集通道 */
#define CH_NUM			8				/* 采集2通道 */
#define FIFO_SIZE		1*1024*2		/* 大小不要超过48K (CPU内部RAM 只有64K) */

/* SPI模拟电平设置 */
#define AD_CS_LOW()     		HAL_GPIO_WritePin(AD7606CS_GPIO_Port, AD7606CS_Pin, GPIO_PIN_RESET)
#define AD_CS_HIGH()     	    HAL_GPIO_WritePin(AD7606CS_GPIO_Port, AD7606CS_Pin, GPIO_PIN_SET)

#define AD_RESET_LOW()		    HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_RESET)
#define AD_RESET_HIGH()	        HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_SET)

#define AD_CONVST_LOW()			HAL_GPIO_WritePin(CONVST_GPIO_Port, CONVST_Pin, GPIO_PIN_RESET)
#define AD_CONVST_HIGH()		HAL_GPIO_WritePin(CONVST_GPIO_Port, CONVST_Pin, GPIO_PIN_SET)

#define AD_RANGE_5V()		    HAL_GPIO_WritePin(RANGE_GPIO_Port, RANGE_Pin, GPIO_PIN_RESET)
#define AD_RANGE_10V()		    HAL_GPIO_WritePin(RANGE_GPIO_Port, RANGE_Pin, GPIO_PIN_SET)

#define AD_MISO_LOW()		    HAL_GPIO_WritePin(AD7606MISO_GPIO_Port, AD7606MISO_Pin, GPIO_PIN_RESET)
#define AD_MISO_HIGH()		    HAL_GPIO_WritePin(AD7606MISO_GPIO_Port, AD7606MISO_Pin, GPIO_PIN_SET)

#define AD_SCK_LOW()		    HAL_GPIO_WritePin(AD7606SCK_GPIO_Port, AD7606SCK_Pin, GPIO_PIN_RESET)
#define AD_SCK_HIGH()		    HAL_GPIO_WritePin(AD7606SCK_GPIO_Port, AD7606SCK_Pin, GPIO_PIN_SET)

#define AD_MISO_IN				HAL_GPIO_ReadPin(AD7606MISO_GPIO_Port, AD7606MISO_Pin)

/* AD数据采集缓冲区 */
typedef struct
{
    uint16_t usRead;
    uint16_t usWrite;
    uint16_t usCount;
    uint16_t usBuf[FIFO_SIZE];
}FIFO_T;

/* 供外部调用的函数声明 */
void ad7606_Reset(void);
void bsp_SET_TIM2_FREQ(uint32_t _ulFreq);
void bsp_InitAD7606(void);
void ad7606_StartRecord(void);
void ad7606_StopRecord(void);
uint8_t GetAdcFormFifo(uint16_t *_usReadAdc);
extern FIFO_T  g_tAD;

#endif
