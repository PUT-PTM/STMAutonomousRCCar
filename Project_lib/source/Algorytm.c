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

/*
 * Decyduje w ktora strone ma sie obrocic pojazd
 * input 1/2 w zaleznosci od tego w ktorej czesci 2 algorytmu jest wywolane
 *  odpowiada odczytowi lewgo lub prawego czujnika
 */
float decide(float input1,float input2)
{
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

/*
 * G³ówna czesc algotyrmu wykrywajaca przeszkody z przodu.
 * Decyduje rowniez czy nalezy zmienic tryb na gwaltowne omijanie przeszkod
 */
float missColisionPartOne()
{
	debugColisionForward=colisionForwardDetect;
	{
		if(zmiennaDoAlgorytmu>odlegloscCenterForward)

			{
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

/*
 * Debug
 */
int debugChoseLeft;
int debugChoseLeftDirect;

/*
 * Obliczanie si³y odpychajacej dla lewego kola
 */
float missColisionLeftPartTwo()
{
	if(colisionForwardDetect)
		{
		debugChoseLeftDirect = (decide(odlegloscLeftForward,odlegloscRightForward));
		debugChoseLeft=(debugChoseLeftDirect*TIM4->ARR);
			return debugChoseLeft;
		}
	else if((zmiennaDoAlgorytmu-odlegloscRightForward>0))
		{
			return (0.5*(TIM4->ARR*1*(float)((zmiennaDoAlgorytmu-odlegloscRightForward)/zmiennaDoAlgorytmu)));
		}
}

/*
 * Sumuje si³e odpychajaca tak aby wysterowac lewe ko³o
 */
float missColissionForLeftWheel()
{
	return (missColisionPartOne()+ missColisionLeftPartTwo());
}

int debugChoseRight;
int debugChoseRightDirect;
/*
 * Obliczanie sily odpychajacej prawe kolo
 */
float missColisionRightPartTwo()
{
		if(colisionForwardDetect)
		{
		debugChoseRightDirect=(decide(odlegloscRightForward,odlegloscLeftForward));
		debugChoseRight= (debugChoseRightDirect*TIM4->ARR);
			return debugChoseRight;
		}
	else if((zmiennaDoAlgorytmu-odlegloscLeftForward>0))
	{
			return (0.5*(TIM4->ARR*1*(float)((zmiennaDoAlgorytmu-odlegloscLeftForward)/zmiennaDoAlgorytmu)));
	}
}
/*
 * Sumuje si³e odpychajaca tak aby wysterowac prawe ko³o
 */
float missColissionForRightWheel()
{
	return (missColisionPartOne()+ missColisionRightPartTwo());
}
