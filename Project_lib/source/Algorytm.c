#include"Algorytm.h"

/*
 *
 */
float missColissionForLeftWheel()
{
	if(0.5-odlegloscRightForward>0)
	{
		return TIM4->ARR*1*(float)((0.5-odlegloscRightForward)/0.5);
	}
}

/*
 *
 */
float missColissionForRightWheel()
{
	if(0.5-odlegloscLeftForward>0)
	{
		return TIM4->ARR*1*(float)((0.5-odlegloscLeftForward)/0.5);
	}
}
