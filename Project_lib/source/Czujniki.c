#include"czujniki.h"
/*
 * Zmienna pomocnicza pozwalajaca przechowac wynik obliczenia odleglosci
 * Oraz wykluczajaca koniecznosc rezerowania pamieci przy kazdym przerwaniu
 */
float temporaryDistance;
/*
 * Funkcja mierzaca odleglosc przeszkody od czujnika
 * Przyjmuje 4 parametry
 * 	1 - Port
 * 	2 - Numer pinu z ktorego nalezy odczytywac wartosc
 * 	3 - WskaŸnik na zmienna przechowuj¹ca pocz¹tkow¹ wartosc licznika
 * 	4 - WskaŸnik na zmienna przechowuj¹ca koncowa wartosc licznika
 *
 */
void measureDistance(float *Distance,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, int *start, int *stop,bool *isMeasureComplete,unsigned short *tryNumber)
{
	if(!(*isMeasureComplete)){
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin))
		{
				*start=TIM7->CNT;
		}
		else
		{
			*stop=TIM7->CNT;
			if((*stop-*start)>0)
			{
				 temporaryDistance= (((((float)(*stop-*start))/(TIM7->ARR+1))/czestotliwoscTimeraPomiarowego)*170);
				 if(temporaryDistance<0.05)
				 {
					 *Distance= 0.05;
				 }
				 else
				 {
					 *Distance= temporaryDistance;
				 }
				 *tryNumber=0;
			}
			*isMeasureComplete=true;
		}
	}
}

/*
 *
 */
void obstacleNoDetected(float *Distance,unsigned short *tryNumber)
{
	if(*tryNumber>5)
	{
		*Distance=neutralDistance;
	}
	else
	{
		*tryNumber=*tryNumber+1;
	}

}
