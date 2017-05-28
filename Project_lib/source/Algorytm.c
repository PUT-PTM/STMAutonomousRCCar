#include"Algorytm.h"
/*
 * niezabezpieczone nie baw sie
 */
float pow(float a, int b)
{
	int result=a;
	for(int i=1;i<b;i++)
	{
		result=result*a;
	}
	return result;
}
bool colisionForwardDetect;
int direction;
float decide(float input1,float input2)
{

	//direction=(input1-input2);

	if(input1<input2)
	{
		return 0;
	}
	else
	{
		return 2;
	}
}

float missColisionPartOne()
{
	if(zmiennaDoAlgorytmu-odlegloscCenterForward>0)
		{
			colisionForwardDetect=true;
			if(zmiennaDoAlgorytmu2<odlegloscCenterForward)
			{
				colisionForwardDetect=false;

			}
			else
			{
				colisionForwardDetect=true;
			}
			return (1*(TIM4->ARR*1*(float)((zmiennaDoAlgorytmu-odlegloscCenterForward)/zmiennaDoAlgorytmu)));
		}
		else
		{
			colisionForwardDetect=false;
		}
}

int debugChoseLeft;
int debugChoseLeftDirect;


float missColisionLeftPartTwo()
{
	if(colisionForwardDetect)
		{
		debugChoseLeft = (decide(odlegloscLeftForward,odlegloscRightForward));
			return debugChoseLeft*TIM4->ARR;
			//return 2*(TIM4->ARR*1*(float)((zmiennaDoAlgorytmu-odlegloscRightForward)/zmiennaDoAlgorytmu));
		}
	else if((zmiennaDoAlgorytmu-odlegloscRightForward>0))
		{
			return (1.5*(TIM4->ARR*1*(float)((zmiennaDoAlgorytmu-odlegloscRightForward)/zmiennaDoAlgorytmu)));
		}
}

/*
 *
 */
float missColissionForLeftWheel()
{
	return (missColisionPartOne()+missColisionLeftPartTwo());
}

//float missColisionPartOne()
//{
//	if(zmiennaDoAlgorytmu2-odlegloscCenterForward>0)
//		{
//			colisionForwardDetect=true;
//			return (TIM4->ARR*1*(float)((zmiennaDoAlgorytmu-odlegloscCenterForward)/zmiennaDoAlgorytmu));
//		}
//		else
//		{
//			colisionForwardDetec=false;
//		}
//}


int debugChoseRight;
int debugChoseRightDirect;
float missColisionRightPartTwo()
{
	//if((zmiennaDoAlgorytmu-odlegloscLeftForward>0)&&colisionForwardDetect)

	if(colisionForwardDetect)
		{
		debugChoseRight=decide(odlegloscRightForward,odlegloscLeftForward);
			return debugChoseRight*TIM4->ARR;
			//return 2*(TIM4->ARR*1*(float)((zmiennaDoAlgorytmu-odlegloscLeftForward)/zmiennaDoAlgorytmu));
		}
	else if((zmiennaDoAlgorytmu-odlegloscLeftForward>0))
	{
		return (1.5*(TIM4->ARR*1*(float)((zmiennaDoAlgorytmu-odlegloscLeftForward)/zmiennaDoAlgorytmu)));
	}
}
/*
 *
 */
float missColissionForRightWheel()
{
	return (missColisionPartOne()+missColisionRightPartTwo());
}
