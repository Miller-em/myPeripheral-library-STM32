/*
*********************************************************************************************************
*
*	模块名称 : AD7606驱动模块
*	文件名称 : bsp_spi_ad7606.c
*	版    本 : V1.3
*	说    明 : 驱动AD7606 ADC转换器 SPI接口
*
*
*********************************************************************************************************
*/

#include "ad7606.h"
#include "tim.h"

FIFO_T	g_tAD;	/* 定义一个交换缓冲区，用于存储AD采集数据，并用于写入SD卡 */

/*
*********************************************************************************************************
*	函 数 名: bsp_InitAD7606
*	功能说明: 初始化AD7606 SPI口线
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_InitAD7606(void)
{
    /* 设置过采样模式 */
//    ad7606_SetOS(0);

    /* 设置GPIO的初始状态 */
    ad7606_Reset();				/* 硬件复位复AD7606 */
    AD_CONVST_HIGH();			/* CONVST脚设置为高电平 */
    MX_TIM5_Init();                 /* 配置定时器*/
}

/*
*********************************************************************************************************
*	函 数 名: ad7606_Reset
*	功能说明: 硬件复位AD7606
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void ad7606_Reset(void)
{
    /* AD7606是高电平复位，要求最小脉宽50ns */
    AD_RESET_LOW();
    AD_RESET_HIGH();
    AD_RESET_HIGH();
    AD_RESET_HIGH();
    AD_RESET_HIGH();
    AD_RESET_LOW();
}

/*
*********************************************************************************************************
*	函 数 名: ad7606_StartConv
*	功能说明: 启动AD7606的ADC转换
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void ad7606_StartConv(void)
{
    /* 上升沿开始转换，低电平持续时间至少25ns  */
    AD_CONVST_LOW();
    AD_CONVST_LOW();
    AD_CONVST_LOW();	/* 连续执行2次，低电平约50ns */
    AD_CONVST_LOW();
    AD_CONVST_LOW();
    AD_CONVST_LOW();
    AD_CONVST_LOW();
    AD_CONVST_LOW();
    AD_CONVST_LOW();
    AD_CONVST_HIGH();
}

//SPI写数据
//向触摸屏IC写入1byte数据
//num:要写入的数据
void SPI_SendData(u16 data)
{
    u8 count=0;
    AD_SCK_LOW();	//下降沿有效
    for(count=0;count<16;count++)
    {
        if(data&0x8000)
            AD_MISO_LOW();
        else
            AD_MISO_HIGH();
        data<<=1;
        AD_SCK_LOW();
        AD_SCK_HIGH();		//上升沿有效
    }
}
//SPI读数据
//从触摸屏IC读取adc值
//CMD:指令
//返回值:读到的数据
//u16 SPI_ReceiveData(void)
//{
//	u8 count=0;
//	u16 Num=0;
//	AD_SCK_LOW();		//先拉低时钟
//	for(count=0;count<16;count++)//读出16位数据,只有高12位有效
//	{
//		Num<<=1;
//		AD_SCK_LOW();	//下降沿有效
//		AD_CSK_HIGH();
//
//		if(AD_MISO_IN)Num++;
//	}
//	return(Num);
//}
u16 SPI_ReceiveData(void)
{
    u8 count=0;
    u16 Num=0;
    AD_SCK_HIGH();
    for(count=0;count<16;count++)//读出16位数据
    {
        Num<<=1;
        AD_SCK_LOW();	//下降沿有效
        if(AD_MISO_IN)Num++;
        AD_SCK_HIGH();
    }
    return(Num);
}
/*
*********************************************************************************************************
*	函 数 名: ad7606_ReadBytes
*	功能说明: 读取AD7606的采样结果
*	形    参：
*	返 回 值: 无
*********************************************************************************************************
*/
uint16_t ad7606_ReadBytes(void)
{
    uint16_t usData = 0;

////  /* Wait until the transmit buffer is empty */
////  while (SPI_I2S_GetFlagStatus(AD_SPI, SPI_I2S_FLAG_TXE) == RESET)
////  {
////  }

//  /* Send the byte */
//  SPI_I2S_SendData(AD_SPI, 0xFFFF);
////	SPI_SendData(0xFFFF);

////  /* Wait until a data is received */
////  while (SPI_I2S_GetFlagStatus(AD_SPI, SPI_I2S_FLAG_RXNE) == RESET)
////  {
////  }

    /* Get the received data */
////  usData = SPI_I2S_ReceiveData(AD_SPI);
    usData = SPI_ReceiveData();

    /* Return the shifted data */
    return usData;
}

/*
*********************************************************************************************************
*	函 数 名: ad7606_IRQSrc
*	功能说明: 定时调用本函数，用于读取AD转换器数据
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void ad7606_IRQSrc(void)
{
    uint8_t i;
    uint16_t usReadValue;

//    TIM_ClearFlag(TIM4, TIM_FLAG_Update);

    /* 读取数据
    示波器监测，CS低电平持续时间 35us
    */
    AD_CS_LOW();
    for (i = 0; i < CH_NUM; i++)
    {
        usReadValue = ad7606_ReadBytes();
        if (g_tAD.usWrite < FIFO_SIZE)
        {
            g_tAD.usBuf[g_tAD.usWrite] = usReadValue;
            ++g_tAD.usWrite;
        }
    }

    AD_CS_HIGH();
//	g_tAD.usWrite = 0;
    ad7606_StartConv();
}

/*
*********************************************************************************************************
*	函 数 名: GetAdcFormFifo
*	功能说明: 从FIFO中读取一个ADC值
*	形    参：_usReadAdc : 存放ADC结果的变量指针
*	返 回 值: 1 表示OK，0表示暂无数据
*********************************************************************************************************
*/
uint8_t GetAdcFormFifo(uint16_t *_usReadAdc)
{
    uint16_t usWrite;

    DISABLE_INT();
    usWrite = g_tAD.usWrite;
    ENABLE_INT();

    if (usWrite != g_tAD.usRead)
    {
        *_usReadAdc = g_tAD.usBuf[g_tAD.usRead];

        DISABLE_INT();
        if (++g_tAD.usRead >= FIFO_SIZE)
        {
            g_tAD.usRead = 0;
        }
        ENABLE_INT();
        return 1;
    }
    return 0;
}

/*
*********************************************************************************************************
*	函 数 名: ad7606_StartRecord
*	功能说明: 开始采集
*	形    参：_ulFreq : 采样频率, 单位 HZ
*	返 回 值: 无
*********************************************************************************************************
*/
void ad7606_StartRecord(uint32_t _ulFreq)
{
    //ad7606_Reset();	/* 复位硬件 */

    ad7606_StartConv();				/* 启动采样，避免第1组数据全0的问题 */

    g_tAD.usRead = 0;				/* 必须在开启TIM2之前清0 */
    g_tAD.usWrite = 0;


    HAL_TIM_Base_Start_IT(&htim5);  /* 使能中断*/
}

/*
*********************************************************************************************************
*	函 数 名: ad7606_StopRecord
*	功能说明: 停止采集
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void ad7606_StopRecord(void)
{
    /* TIM2 enable counter [允许tim2计数]*/
    HAL_TIM_Base_Start_IT(&htim5);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim == (&htim5)) {
        ad7606_IRQSrc();
    }
}

