/*
 * @Author: your name
 * @Date: 2021-07-31 14:50:57
 * @LastEditTime: 2021-07-31 14:50:57
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \LCD_DEMO_F411CEU\MyCode\LCD_SPI\lcd_demo.c
 */
#include "lcd.h"
#include "lcd_gui.h"
#include "lcd_demo.h"
//#include "lcd_touch.h"
#include "lcd_pic.h"

//========================variable==========================//
u16 ColorTab[5]={RED,GREEN,BLUE,YELLOW,BRED};//定义颜色数组
//=====================end of variable======================//

/*****************************************************************************
 * @name       :void DrawTestPage(u8 *str)
 * @date       :2018-08-09
 * @function   :Drawing test interface
 * @parameters :str:the start address of the Chinese and English strings
 * @retvalue   :None
******************************************************************************/
void DrawTestPage(u8 *str)
{
//绘制固定栏up
    LCD_Clear(WHITE);
    LCD_Fill(0,0,lcddev.width,20,BLUE);
//绘制固定栏down
    LCD_Fill(0,lcddev.height-20,lcddev.width,lcddev.height,BLUE);
    POINT_COLOR=WHITE;
    Gui_StrCenter(0,2,WHITE,BLUE,str,16,1);//居中显示
    Gui_StrCenter(0,lcddev.height-18,WHITE,BLUE,"http://www.lcdwiki.com",16,1);//居中显示
//绘制测试区域
//LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
}

/*****************************************************************************
 * @name       :void main_test(void)
 * @date       :2018-08-09
 * @function   :Drawing the main Interface of the Comprehensive Test Program
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void main_test(void)
{
    DrawTestPage("I Love ...");
    Gui_StrCenter(0,30,RED,BLUE,"全动电子",16,1);//居中显示
    Gui_StrCenter(0,60,RED,BLUE,"综合测试程序",16,1);//居中显示
    Gui_StrCenter(0,90,GREEN,BLUE,"2.8\" ILI9341 240X320",16,1);//居中显示
    Gui_StrCenter(0,120,BLUE,BLUE,"xiaoFeng@QDtech 2018-08-20",16,1);//居中显示
    HAL_Delay(1500);
    HAL_Delay(1500);
}

/*****************************************************************************
 * @name       :void Test_Color(void)
 * @date       :2018-08-09
 * @function   :Color fill test(white,black,red,green,blue)
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Color(void)
{
    //DrawTestPage("测试1:纯色填充测试");
    LCD_Fill(0,0,lcddev.width,lcddev.height,WHITE);
    Show_Str(20,30,BLUE,YELLOW,"BL Test",16,1);HAL_Delay(800);
    LCD_Fill(0,0,lcddev.width,lcddev.height,RED);
    Show_Str(20,30,BLUE,YELLOW,"RED ",16,1);HAL_Delay(800);
    LCD_Fill(0,0,lcddev.width,lcddev.height,GREEN);
    Show_Str(20,30,BLUE,YELLOW,"GREEN ",16,1);HAL_Delay(800);
    LCD_Fill(0,0,lcddev.width,lcddev.height,BLUE);
    Show_Str(20,30,RED,YELLOW,"BLUE ",16,1);HAL_Delay(800);
}

/*****************************************************************************
 * @name       :void Test_FillRec(void)
 * @date       :2018-08-09
 * @function   :Rectangular display and fill test
								Display red,green,blue,yellow,pink rectangular boxes in turn,
								1500 milliseconds later,
								Fill the rectangle in red,green,blue,yellow and pink in turn
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_FillRec(void)
{
    u8 i=0;
    DrawTestPage("测试2:GUI矩形填充测试");
    LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
    for (i=0; i<5; i++)
    {
        POINT_COLOR=ColorTab[i];
        LCD_DrawRectangle(lcddev.width/2-80+(i*15),lcddev.height/2-80+(i*15),lcddev.width/2-80+(i*15)+60,lcddev.height/2-80+(i*15)+60);
    }
    HAL_Delay(1500);
    LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
    for (i=0; i<5; i++)
    {
        POINT_COLOR=ColorTab[i];
        LCD_DrawFillRectangle(lcddev.width/2-80+(i*15),lcddev.height/2-80+(i*15),lcddev.width/2-80+(i*15)+60,lcddev.height/2-80+(i*15)+60);
    }
    HAL_Delay(1500);
}

/*****************************************************************************
 * @name       :void Test_Circle(void)
 * @date       :2018-08-09
 * @function   :circular display and fill test
								Display red,green,blue,yellow,pink circular boxes in turn,
								1500 milliseconds later,
								Fill the circular in red,green,blue,yellow and pink in turn
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Circle(void)
{
    u8 i=0;
    DrawTestPage("测试3:GUI画圆填充测试");
    LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
    for (i=0; i<5; i++)
        gui_circle(lcddev.width/2-80+(i*25),lcddev.height/2-50+(i*25),ColorTab[i],30,0);
    HAL_Delay(1500);
    LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
    for (i=0; i<5; i++)
        gui_circle(lcddev.width/2-80+(i*25),lcddev.height/2-50+(i*25),ColorTab[i],30,1);
    HAL_Delay(1500);
}

/*****************************************************************************
 * @name       :void English_Font_test(void)
 * @date       :2018-08-09
 * @function   :English display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void English_Font_test(void)
{
    DrawTestPage("测试5:英文显示测试");
    Show_Str(10,30,BLUE,YELLOW,"6X12:abcdefghijklmnopqrstuvwxyz0123456789",12,0);
    Show_Str(10,45,BLUE,YELLOW,"6X12:ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",12,1);
    Show_Str(10,60,BLUE,YELLOW,"6X12:~!@#$%^&*()_+{}:<>?/|-+.",12,0);
    Show_Str(10,80,BLUE,YELLOW,"8X16:abcdefghijklmnopqrstuvwxyz0123456789",16,0);
    Show_Str(10,100,BLUE,YELLOW,"8X16:ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",16,1);
    Show_Str(10,120,BLUE,YELLOW,"8X16:~!@#$%^&*()_+{}:<>?/|-+.",16,0);
    HAL_Delay(1200);
}

/*****************************************************************************
 * @name       :void Test_Triangle(void)
 * @date       :2018-08-09
 * @function   :triangle display and fill test
								Display red,green,blue,yellow,pink triangle boxes in turn,
								1500 milliseconds later,
								Fill the triangle in red,green,blue,yellow and pink in turn
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Triangle(void)
{
    u8 i=0;
    DrawTestPage("测试4:GUI Triangle填充测试");
    LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
    for(i=0;i<5;i++)
    {
        POINT_COLOR=ColorTab[i];
        Draw_Triangel(lcddev.width/2-80+(i*20),lcddev.height/2-20+(i*15),lcddev.width/2-50-1+(i*20),lcddev.height/2-20-52-1+(i*15),lcddev.width/2-20-1+(i*20),lcddev.height/2-20+(i*15));
    }
    HAL_Delay(1500);
    LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
    for(i=0;i<5;i++)
    {
        POINT_COLOR=ColorTab[i];
        Fill_Triangel(lcddev.width/2-80+(i*20),lcddev.height/2-20+(i*15),lcddev.width/2-50-1+(i*20),lcddev.height/2-20-52-1+(i*15),lcddev.width/2-20-1+(i*20),lcddev.height/2-20+(i*15));
    }
    HAL_Delay(1500);
}

/*****************************************************************************
 * @name       :void Chinese_Font_test(void)
 * @date       :2018-08-09
 * @function   :chinese display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Chinese_Font_test(void)
{
    DrawTestPage("测试6:中文显示测试");
    Show_Str(10,30,BLUE,YELLOW,"16X16:全动电子技术有限公司欢迎您",16,0);
    Show_Str(10,50,BLUE,YELLOW,"16X16:Welcome全动电子",16,0);
    Show_Str(10,70,BLUE,YELLOW,"24X24:深圳市中文测试",24,1);
    Show_Str(10,100,BLUE,YELLOW,"32X32:字体测试",32,1);
    HAL_Delay(1200);
}

/*****************************************************************************
 * @name       :void Pic_test(void)
 * @date       :2018-08-09
 * @function   :picture display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Pic_test(void)
{
    DrawTestPage("测试7:图片显示测试");
    //LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
    Gui_Drawbmp16(30,30,gImage_qq);
    Show_Str(30+12,75,BLUE,YELLOW,"QQ",16,1);
    Gui_Drawbmp16(90,30,gImage_qq);
    Show_Str(90+12,75,BLUE,YELLOW,"QQ",16,1);
    Gui_Drawbmp16(150,30,gImage_qq);
    Show_Str(150+12,75,BLUE,YELLOW,"QQ",16,1);
    HAL_Delay(1200);
}

/*****************************************************************************
 * @name       :void Rotate_Test(void)
 * @date       :2018-08-09
 * @function   :rotate test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Rotate_Test(void)
{
    u8 i=0;
    u8 *Direction[4]={"Rotation:0","Rotation:90","Rotation:180","Rotation:270"};

    for(i=0;i<4;i++)
    {
        LCD_direction(i);
        DrawTestPage("测试8:屏幕旋转测试");
        Show_Str(20,30,BLUE,YELLOW,Direction[i],16,1);
        Gui_Drawbmp16(30,50,gImage_qq);
        HAL_Delay(1000);HAL_Delay(1000);
    }
    LCD_direction(USE_HORIZONTAL);
}

/*****************************************************************************
 * @name       :void Touch_Test(void)
 * @date       :2018-08-09
 * @function   :touch test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
//void Touch_Test(void)
//{
//    u8 key;
//    u16 i=0;
//    u16 j=0;
//    u16 colorTemp=0;
//    TP_Init();
//    KEY_Init();
//    LED_Init();
//    DrawTestPage("测试9:Touch(按KEY0校准)      ");
//    LCD_ShowString(lcddev.width-24,0,16,"RST",1);//显示清屏区域
//    POINT_COLOR=RED;
//    LCD_Fill(lcddev.width-52,2,lcddev.width-50+20,18,RED);
//    while(1)
//    {
//        key=KEY_Scan();
//        tp_dev.scan(0);
//        if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
//        {
//            if(tp_dev.x<lcddev.width&&tp_dev.y<lcddev.height)
//            {
//                if(tp_dev.x>(lcddev.width-24)&&tp_dev.y<16)
//                {
//                    DrawTestPage("测试9:Touch(按KEY0校准)      ");//清除
//                    LCD_ShowString(lcddev.width-24,0,16,"RST",1);//显示清屏区域
//                    POINT_COLOR=colorTemp;
//                    LCD_Fill(lcddev.width-52,2,lcddev.width-50+20,18,POINT_COLOR);
//                }
//                else if((tp_dev.x>(lcddev.width-60)&&tp_dev.x<(lcddev.width-50+20))&&tp_dev.y<20)
//                {
//                    LCD_Fill(lcddev.width-52,2,lcddev.width-50+20,18,ColorTab[j%5]);
//                    POINT_COLOR=ColorTab[(j++)%5];
//                    colorTemp=POINT_COLOR;
//                    HAL_Delay(10);
//                }
//
//                else TP_Draw_Big_Point(tp_dev.x,tp_dev.y,POINT_COLOR);		//画图
//            }
//        }else HAL_Delay(10);	//没有按键按下的时候
//        if(key==1)	//KEY_RIGHT按下,则执行校准程序
//        {
//
//            LCD_Clear(WHITE);//清屏
//            TP_Adjust();  //屏幕校准
//            TP_Save_Adjdata();
//            DrawTestPage("测试9:Touch(按KEY0校准)      ");
//            LCD_ShowString(lcddev.width-24,0,16,"RST",1);//显示清屏区域
//            POINT_COLOR=colorTemp;
//            LCD_Fill(lcddev.width-52,2,lcddev.width-50+20,18,POINT_COLOR);
//        }
//        i++;
//        if(i==30)
//        {
//            i=0;
//            LED0=!LED0;
//            //break;
//        }
//    }
//}