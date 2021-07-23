#include "pid.h"
#include "main.h"

//增量式PID结构体变量声明
static PID incPID;
static PID *incptr = &incPID;
//位置式PID结构体变量声明
PID sPID;
PID *sptr = &sPID;

/*====================================================================================================
位置式PID计算部分
=====================================================================================================*/
double PIDCalc_Pos(PID *pp, double NextPoint) {

	double dError, Error;

	Error = pp->SetPoint - NextPoint; /* 计算当前偏差 */
	pp->SumError += Error; /* 积分《总偏差》*/
	dError = pp->LastError - pp->PrevError; /* 当前微分 */
	pp->PrevError = pp->LastError;
	pp->LastError = Error; /*  三个误差值移位  */
	return (NextPoint + pp->Proportion * Error + pp->Integral * pp->SumError
			+ pp->Derivative * dError); /*返回总的误差值*/
}

/*====================================================================================================
增量式PID计算部分
=====================================================================================================*/
int IncPIDCalc(int NextPoint) {
	register int iError, iIncpid;                   //当前误差
	iError = sptr->SetPoint - NextPoint;            //增量计算
	iIncpid = sptr->Proportion * iError             //E[k]项
	- sptr->Integral * sptr->LastError          //E[k－1]项
	+ sptr->Derivative * sptr->PrevError;   //E[k－2]项
	//存储误差，用于下次计算
	sptr->PrevError = sptr->LastError;
	sptr->LastError = iError;
	//返回增量值
	return (iIncpid);
}

/*====================================================================================================
Initialize PID Structure 增量PID参数初始化
=====================================================================================================*/
void IncPIDInit(void)
{
    sptr->SumError = 0;
    sptr->LastError = 0;                            // Error[-1]
    sptr->PrevError = 0;                            // Error[-2]
    sptr->Proportion = 1.1;                           // 比例常数 Proportional Const
    sptr->Integral = 0.5;                             // 积分常数Integral Const
    sptr->Derivative = 0;                           // 微分常数 Derivative Const
    sptr->SetPoint = 1.8*4096/2.5;                    // 根据电压直接设置成ADC的值，减少中间运算
}
