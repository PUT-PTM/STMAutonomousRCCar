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
 * 	3 - Wska�nik na zmienna przechowuj�ca pocz�tkow� wartosc licznika
 * 	4 - Wska�nik na zmienna przechowuj�ca koncowa wartosc licznika
 *
 */
void measureDistance(float *Distance,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, int *start, int *stop,bool *isMeasureComplete)
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
					*isMeasureComplete=true;
					 temporaryDistance= (((((float)(*stop-*start))/(TIM7->ARR+1))/czestotliwoscTimeraPomiarowego)*170);
					 if(temporaryDistance<0.05)
					 {
						 *Distance= 0.05;
					 }
					 else
					 {
						 *Distance= temporaryDistance;
					 }
				}
				else
				{
					*Distance=1;
				}
			}
	}
	else
	{
		*Distance=1;
	}

}
