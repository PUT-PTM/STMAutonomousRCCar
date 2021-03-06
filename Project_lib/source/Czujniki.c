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
					 obstacleVeryClose(Distance,tryNumber);
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
 * Redukuje skoki pomiarowe gdy przeszkoda jest bardzo blisko
 * (niweluje fale kt�re odbi�y si� w niew�asciwy spos�b i zak��caj� pomiar)
 */
void obstacleVeryClose(float *Distance,unsigned short *tryNumber)
{
	//Czyjniki sa mniej responsywne na szybkie pojawienie si� przeszkody w odleg�osci mniejszej ni� 5 cm
	if(*tryNumber>4)
		{
			*Distance=veryCloseDistance;
		}
		else
		{
			*tryNumber=*tryNumber+1;
		}
}

/*
 *W przypadku braku wykrycia przeszkody (sygnale sie nie odbije itp) zapobiega szybim skokomm odleglosci.
 */
void obstacleNoDetected(float *Distance,unsigned short *tryNumber)
{
	if(*tryNumber>8)
	{
		*Distance=neutralDistance;
	}
	else
	{
		*tryNumber=*tryNumber+1;
	}
}
