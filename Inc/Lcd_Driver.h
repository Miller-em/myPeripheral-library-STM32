#ifndef __LCD_DRIVER_H_
#define __LCD_DRIVER_H_

#include "main.h"
/////////////////////////////////////用户配置区///////////////////////////////////
//支持横竖屏快速定义切换
#define USE_HORIZONTAL  		0	//定义是否使用横屏 		0,不使用.1,使用.

//-----------------------------SPI 总线配置--------------------------------------//
//#define USE_HARDWARE_SPI     1  //1:Enable Hardware SPI;0:USE Soft SPI

//-------------------------屏幕物理像素设置--------------------------------------//
#define LCD_X_SIZE	        240
#define LCD_Y_SIZE	        320

#if USE_HORIZONTAL//如果定义了横屏
#define X_MAX_PIXEL	        LCD_Y_SIZE
#define Y_MAX_PIXEL	        LCD_X_SIZE
#else
#define X_MAX_PIXEL	        LCD_X_SIZE
#define Y_MAX_PIXEL	        LCD_Y_SIZE
#endif
//////////////////////////////////////////////////////////////////////////////////

//定义了颜色
#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//灰色0 3165 00110 001011 00101
#define GRAY1   0x8410      	//灰色1      00000 000000 00000
#define GRAY2   0x4208      	//灰色2  1111111111011111



//本测试程序使用的是模拟SPI接口驱动
//可自由更改接口IO配置，使用任意最少4 IO即可完成本款液晶驱动显示
#define LCD_SDA_SET()   HAL_GPIO_WritePin(SDA_GPIO_Port,SDA_Pin, GPIO_PIN_SET) //SDA
#define LCD_SDA_CLR()   HAL_GPIO_WritePin(SDA_GPIO_Port,SDA_Pin, GPIO_PIN_RESET) //SDA
#define LCD_SCL_SET()   HAL_GPIO_WritePin(SCL_GPIO_Port,SCL_Pin, GPIO_PIN_SET) //SCL
#define LCD_SCL_CLR()   HAL_GPIO_WritePin(SCL_GPIO_Port,SCL_Pin, GPIO_PIN_RESET) //SCL
#define LCD_RS_SET()   HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin, GPIO_PIN_SET) //RS
#define LCD_RS_CLR()   HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin, GPIO_PIN_RESET) //RS
#define LCD_CS_SET()   HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin, GPIO_PIN_SET) //CS
#define LCD_CS_CLR()   HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin, GPIO_PIN_RESET) //CS
#define LCD_LED_SET()   HAL_GPIO_WritePin(LCD_LED_GPIO_Port,LCD_LED_Pin, GPIO_PIN_SET) //led
#define LCD_LED_CLR()   HAL_GPIO_WritePin(LCD_LED_GPIO_Port,LCD_LED_Pin, GPIO_PIN_RESET) //led
//#define LCD_RET_SET()   HAL_GPIO_WritePin(RET_GPIO_Port,RET_Pin, GPIO_PIN_SET) //SCL
//#define LCD_RET_CLR()   HAL_GPIO_WritePin(RET_GPIO_Port,RET_Pin, GPIO_PIN_RESET) //SCL

//#define LCD_DATAOUT(x) LCD_DATA->ODR=x; //数据输出
//#define LCD_DATAIN     LCD_DATA->IDR;   //数据输入

//#define LCD_WR_DATA(data){\
//LCD_RS_SET;\
//LCD_CS_CLR;\
//LCD_DATAOUT(data);\
//LCD_WR_CLR;\
//LCD_WR_SET;\
//LCD_CS_SET;\
//}



void Lcd_WriteIndex(u8 Index);
void Lcd_WriteData(u8 Data);
void Lcd_WriteReg(u8 Index,u8 Data);
u16 Lcd_ReadReg(u8 LCD_Reg);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(u16 Color);
void Lcd_SetXY(u16 x,u16 y);
void Gui_DrawPoint(u16 x,u16 y,u16 Data);
unsigned int Lcd_ReadPoint(u16 x,u16 y);
void Lcd_SetRegion(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);
void Lcd_WriteData_16Bit(u16 Data);

#endif
