#ifndef __PID_H
#define __PID_H
/*
 * 	这是一个pid调节库，里面声明了各种pid算法
 * */


typedef struct {

	double SetPoint; /*  设定目标 Desired Value */

	double Proportion; /*  比例常数 Proportional Const */
	double Integral; /*  积分常数 Integral Const */
	double Derivative; /*  微分常数 Derivative Const */

	double LastError; /*  前一项误差 */
	double PrevError; /*  前第二项误差 */
	double SumError; /*  总误差 */

} PID;

/*
 * 增量式PID结构体变量声明
 * */
static PID incPID;
static PID *incptr;
/*
 * 位置式PID结构体变量声明
 * */
extern PID sPID;
extern PID *sptr;

/****************************************************************************
   PID计算部分
****************************************************************************/
double PIDCalc_Pos( PID *pp, double NextPoint); //位置式PID
int IncPIDCalc(int NextPoint);					//增量式PID

#endif
