#include"czujniki.h"
float ZmiennaPomocniczaDoDebuguWartosciZwracanejPrzezFunkcjeMeasureDistance;
/*
 * Funkcja mierzaca odleglosc przeszkody od czujnika
 * Przyjmuje 4 parametry
 * 	1 - Port
 * 	2 - Numer pinu z ktorego nalezy odczytywac wartosc
 * 	3 - Wskaźnik na zmienna przechowująca początkową wartosc licznika
 * 	4 - Wskaźnik na zmienna przechowująca koncowa wartosc licznika
 *
 */
float measureDistance(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, int *start, int *stop,bool *isMeasureComplete)
{

	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin))
	{
		*start=TIM7->CNT;
	}
	else
	{
		*stop=TIM7->CNT;
		if((*stop-*start)>0&&!(*isMeasureComplete))
		{
			*isMeasureComplete=true;
			 ZmiennaPomocniczaDoDebuguWartosciZwracanejPrzezFunkcjeMeasureDistance= (((((float)(*stop-*start))/(TIM7->ARR+1))/czestotliwoscTimeraPomiarowego)*170);
			 if(ZmiennaPomocniczaDoDebuguWartosciZwracanejPrzezFunkcjeMeasureDistance<0.05)
			 {
				 return 0.05;
			 }
			 else
			 {
				 return ZmiennaPomocniczaDoDebuguWartosciZwracanejPrzezFunkcjeMeasureDistance;
			 }
		}
		else
		{
			return 1;
		}
	}
}
