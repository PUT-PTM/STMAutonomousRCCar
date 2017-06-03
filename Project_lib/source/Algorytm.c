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

	if(input1>input2)
	{
		return 1;
	}
	else
	{
		return -2;
	}
}
 int debugColisionForward;
float missColisionPartOne()
{
	debugColisionForward=colisionForwardDetect;
//	if((odlegloscRightForward<zmiennaDoAlgorytmu3)||(odlegloscLeftForward<zmiennaDoAlgorytmu3))
//	{
//			colisionForwardDetect=true;
//	}
//	else
	{
		if(zmiennaDoAlgorytmu>odlegloscCenterForward)

			{
		//			colisionForwardDetect=true;
				if(zmiennaDoAlgorytmu2>odlegloscCenterForward)
				{
					colisionForwardDetect=true;
					return (1*(TIM4->ARR*1*(float)((zmiennaDoAlgorytmu-odlegloscCenterForward)/zmiennaDoAlgorytmu)));
				}
				else
				{
					colisionForwardDetect=false;
					return (0.5*(TIM4->ARR*1*(float)((zmiennaDoAlgorytmu-odlegloscCenterForward)/zmiennaDoAlgorytmu)));
				}
			}
			else
			{
				colisionForwardDetect=false;
			}
	}
}

int debugChoseLeft;
int debugChoseLeftDirect;


float missColisionLeftPartTwo()
{
	if(colisionForwardDetect)
		{
		debugChoseLeftDirect = (decide(odlegloscLeftForward,odlegloscRightForward));
		debugChoseLeft=(debugChoseLeftDirect*TIM4->ARR);
			return debugChoseLeft;
			//return 2*(TIM4->ARR*1*(float)((zmiennaDoAlgorytmu-odlegloscRightForward)/zmiennaDoAlgorytmu));
		}
	else if((zmiennaDoAlgorytmu-odlegloscRightForward>0))
		{
//			if(zmiennaDoAlgorytmu3>odlegloscRightForward)
//			{
//				//Troche redundancji pozbyc sie tego
//				debugChoseLeftDirect = (decide(odlegloscLeftForward,odlegloscRightForward));
//				debugChoseLeft=(debugChoseLeftDirect*TIM4->ARR);
//				return debugChoseLeft;
//
//			}
//			else
//			{
				return (0.5*(TIM4->ARR*1*(float)((zmiennaDoAlgorytmu-odlegloscRightForward)/zmiennaDoAlgorytmu)));
//			}
		}
}

/*
 *
 */
float missColissionForLeftWheel()
{
	return (missColisionPartOne()+ missColisionLeftPartTwo());
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
		debugChoseRightDirect=(decide(odlegloscRightForward,odlegloscLeftForward));
		debugChoseRight= (debugChoseRightDirect*TIM4->ARR);
			return debugChoseRight;
			//return 2*(TIM4->ARR*1*(float)((zmiennaDoAlgorytmu-odlegloscLeftForward)/zmiennaDoAlgorytmu));
		}
	else if((zmiennaDoAlgorytmu-odlegloscLeftForward>0))
	{
//		if(zmiennaDoAlgorytmu3>odlegloscLeftForward)
//		{
//			//Troche redundancji pozbyc sie tego
//			debugChoseRightDirect=(decide(odlegloscRightForward,odlegloscLeftForward));
//					debugChoseRight= (debugChoseRightDirect*TIM4->ARR);
//						return debugChoseRight;
//		}
//		else
//		{
			return (0.5*(TIM4->ARR*1*(float)((zmiennaDoAlgorytmu-odlegloscLeftForward)/zmiennaDoAlgorytmu)));
//		}
	}
}
/*
 *
 */
float missColissionForRightWheel()
{
	return (missColisionPartOne()+ missColisionRightPartTwo());
}
