/*
 * @Author: Zhou Xiaozong
 * @Date: 2021-07-31 14:09:19
 * @LastEditTime: 2021-07-31 14:10:16
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LCD_DEMO_F411CEU\MyCode\LCD_SPI\lcd.c
 */
#include "lcd.h"
#include "stdlib.h"

//管理LCD重要参数
//默认为竖屏
_lcd_dev lcddev;

//画笔颜色,背景颜色
u16 POINT_COLOR = RED,BACK_COLOR = WHITE;
u16 DeviceCode;

/****************************************************************************
* 名    称：void  SPIv_WriteData(u8 Data)
* 功    能：STM32_模拟SPI写一个字节数据底层函数
* 入口参数：Data
* 出口参数：无
* 说    明：STM32_模拟SPI读写一个字节数据底层函数
****************************************************************************/
void  SPIv_WriteData(u8 Data)
{
    unsigned char i=0;
    for(i=8;i>0;i--)
    {
        if(Data&0x80)
            LCD_SDA_SET(); //输出数据
        else LCD_SDA_CLR();

        LCD_SCL_CLR();
        LCD_SCL_SET();
        Data<<=1;
    }
}

/*****************************************************************************
 * @name       :void LCD_WR_REG(u8 data)
 * @date       :2018-08-09
 * @function   :Write an 8-bit command to the LCD screen
 * @parameters :data:Command value to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WR_REG(u8 data)
{
    LCD_CS_CLR();
    LCD_RS_CLR();
    SPIv_WriteData(data);
    LCD_CS_SET();
}

/*****************************************************************************
 * @name       :void LCD_WR_DATA(u8 data)
 * @date       :2018-08-09
 * @function   :Write an 8-bit data to the LCD screen
 * @parameters :data:data value to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WR_DATA(u8 data)
{
    LCD_CS_CLR();
    LCD_RS_SET();
    SPIv_WriteData(data);
    LCD_CS_SET();
}

/*****************************************************************************
 * @name       :void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
 * @date       :2018-08-09
 * @function   :Write data into registers
 * @parameters :LCD_Reg:Register address
                LCD_RegValue:Data to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{
    LCD_WR_REG(LCD_Reg);
    LCD_WR_DATA(LCD_RegValue);
}

/*****************************************************************************
 * @name       :void LCD_WriteRAM_Prepare(void)
 * @date       :2018-08-09
 * @function   :Write GRAM
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void LCD_WriteRAM_Prepare(void)
{
    LCD_WR_REG(lcddev.wramcmd);
}

/*****************************************************************************
 * @name       :void Lcd_WriteData_16Bit(u16 Data)
 * @date       :2018-08-09
 * @function   :Write an 16-bit command to the LCD screen
 * @parameters :Data:Data to be written
 * @retvalue   :None
******************************************************************************/
void Lcd_WriteData_16Bit(u16 Data)
{
    LCD_CS_CLR();
    LCD_RS_SET();
    SPIv_WriteData(Data>>8);
    SPIv_WriteData(Data);
    LCD_CS_SET();
}

/*****************************************************************************
 * @name       :void LCD_DrawPoint(u16 x,u16 y)
 * @date       :2018-08-09
 * @function   :Write a pixel data at a specified location
 * @parameters :x:the x coordinate of the pixel
                y:the y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/
void LCD_DrawPoint(u16 x,u16 y)
{
    LCD_SetCursor(x,y);//设置光标位置
    Lcd_WriteData_16Bit(POINT_COLOR);
}

/*****************************************************************************
 * @name       :void LCD_Clear(u16 Color)
 * @date       :2018-08-09
 * @function   :Full screen filled LCD screen
 * @parameters :color:Filled color
 * @retvalue   :None
******************************************************************************/
void LCD_Clear(u16 Color)
{
    unsigned int i,m;
    LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);
    LCD_CS_CLR();
    LCD_RS_SET();
    for(i=0;i<lcddev.height;i++)
    {
        for(m=0;m<lcddev.width;m++)
        {
            Lcd_WriteData_16Bit(Color);
        }
    }
    LCD_CS_SET();
}

/*****************************************************************************
 * @name       :void LCD_RESET(void)
 * @date       :2018-08-09
 * @function   :Reset LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
//void LCD_RESET(void)
//{
//    LCD_RST_CLR;
//    HAL_Delay(100);
//    LCD_RST_SET;
//    HAL_Delay(50);
//}

/*****************************************************************************
 * @name       :void LCD_Init(void)
 * @date       :2018-08-09
 * @function   :Initialization LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void LCD_Init(void)
{
//    LCD_GPIOInit();//LCD GPIO初始化
//    LCD_RESET(); //LCD 复位
//*************2.8inch ILI9341初始化**********//
    LCD_WR_REG(0xCF);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0xC9); //C1
    LCD_WR_DATA(0X30);
    LCD_WR_REG(0xED);
    LCD_WR_DATA(0x64);
    LCD_WR_DATA(0x03);
    LCD_WR_DATA(0X12);
    LCD_WR_DATA(0X81);
    LCD_WR_REG(0xE8);
    LCD_WR_DATA(0x85);
    LCD_WR_DATA(0x10);
    LCD_WR_DATA(0x7A);
    LCD_WR_REG(0xCB);
    LCD_WR_DATA(0x39);
    LCD_WR_DATA(0x2C);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x34);
    LCD_WR_DATA(0x02);
    LCD_WR_REG(0xF7);
    LCD_WR_DATA(0x20);
    LCD_WR_REG(0xEA);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_REG(0xC0);    //Power control
    LCD_WR_DATA(0x1B);   //VRH[5:0]
    LCD_WR_REG(0xC1);    //Power control
    LCD_WR_DATA(0x00);   //SAP[2:0];BT[3:0] 01
    LCD_WR_REG(0xC5);    //VCM control
    LCD_WR_DATA(0x30); 	 //3F
    LCD_WR_DATA(0x30); 	 //3C
    LCD_WR_REG(0xC7);    //VCM control2
    LCD_WR_DATA(0XB7);
    LCD_WR_REG(0x36);    // Memory Access Control
    LCD_WR_DATA(0x08);
    LCD_WR_REG(0x3A);
    LCD_WR_DATA(0x55);
    LCD_WR_REG(0xB1);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x1A);
    LCD_WR_REG(0xB6);    // Display Function Control
    LCD_WR_DATA(0x0A);
    LCD_WR_DATA(0xA2);
    LCD_WR_REG(0xF2);    // 3Gamma Function Disable
    LCD_WR_DATA(0x00);
    LCD_WR_REG(0x26);    //Gamma curve selected
    LCD_WR_DATA(0x01);
    LCD_WR_REG(0xE0);    //Set Gamma
    LCD_WR_DATA(0x0F);
    LCD_WR_DATA(0x2A);
    LCD_WR_DATA(0x28);
    LCD_WR_DATA(0x08);
    LCD_WR_DATA(0x0E);
    LCD_WR_DATA(0x08);
    LCD_WR_DATA(0x54);
    LCD_WR_DATA(0XA9);
    LCD_WR_DATA(0x43);
    LCD_WR_DATA(0x0A);
    LCD_WR_DATA(0x0F);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_REG(0XE1);    //Set Gamma
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x15);
    LCD_WR_DATA(0x17);
    LCD_WR_DATA(0x07);
    LCD_WR_DATA(0x11);
    LCD_WR_DATA(0x06);
    LCD_WR_DATA(0x2B);
    LCD_WR_DATA(0x56);
    LCD_WR_DATA(0x3C);
    LCD_WR_DATA(0x05);
    LCD_WR_DATA(0x10);
    LCD_WR_DATA(0x0F);
    LCD_WR_DATA(0x3F);
    LCD_WR_DATA(0x3F);
    LCD_WR_DATA(0x0F);
    LCD_WR_REG(0x2B);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x01);
    LCD_WR_DATA(0x3f);
    LCD_WR_REG(0x2A);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0xef);
    LCD_WR_REG(0x11); //Exit Sleep
    HAL_Delay(120);
    LCD_WR_REG(0x29); //display on

    LCD_direction(USE_HORIZONTAL);//设置LCD显示方向
//    LCD_LED=1;//点亮背光
    LCD_Clear(WHITE);//清全屏白色
}

/*****************************************************************************
 * @name       :void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
 * @date       :2018-08-09
 * @function   :Setting LCD display window
 * @parameters :xStar:the bebinning x coordinate of the LCD display window
								yStar:the bebinning y coordinate of the LCD display window
								xEnd:the endning x coordinate of the LCD display window
								yEnd:the endning y coordinate of the LCD display window
 * @retvalue   :None
******************************************************************************/
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{
    LCD_WR_REG(lcddev.setxcmd);
    LCD_WR_DATA(xStar>>8);
    LCD_WR_DATA(0x00FF&xStar);
    LCD_WR_DATA(xEnd>>8);
    LCD_WR_DATA(0x00FF&xEnd);

    LCD_WR_REG(lcddev.setycmd);
    LCD_WR_DATA(yStar>>8);
    LCD_WR_DATA(0x00FF&yStar);
    LCD_WR_DATA(yEnd>>8);
    LCD_WR_DATA(0x00FF&yEnd);

    LCD_WriteRAM_Prepare();	//开始写入GRAM
}

/*****************************************************************************
 * @name       :void LCD_SetCursor(u16 Xpos, u16 Ypos)
 * @date       :2018-08-09
 * @function   :Set coordinate value
 * @parameters :Xpos:the  x coordinate of the pixel
								Ypos:the  y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
    LCD_SetWindows(Xpos,Ypos,Xpos,Ypos);
}

/*****************************************************************************
 * @name       :void LCD_direction(u8 direction)
 * @date       :2018-08-09
 * @function   :Setting the display direction of LCD screen
 * @parameters :direction:0-0 degree
                          1-90 degree
													2-180 degree
													3-270 degree
 * @retvalue   :None
******************************************************************************/
void LCD_direction(u8 direction)
{
    lcddev.setxcmd=0x2A;
    lcddev.setycmd=0x2B;
    lcddev.wramcmd=0x2C;
    switch(direction){
        case 0:
            lcddev.width=LCD_W;
            lcddev.height=LCD_H;
            LCD_WriteReg(0x36,(1<<3)|(0<<6)|(0<<7));//BGR==1,MY==0,MX==0,MV==0
            break;
        case 1:
            lcddev.width=LCD_H;
            lcddev.height=LCD_W;
            LCD_WriteReg(0x36,(1<<3)|(0<<7)|(1<<6)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
            break;
        case 2:
            lcddev.width=LCD_W;
            lcddev.height=LCD_H;
            LCD_WriteReg(0x36,(1<<3)|(1<<6)|(1<<7));//BGR==1,MY==0,MX==0,MV==0
            break;
        case 3:
            lcddev.width=LCD_H;
            lcddev.height=LCD_W;
            LCD_WriteReg(0x36,(1<<3)|(1<<7)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
            break;
        default:break;
    }
}
