#include "interupt.h"
#include"czujniki.h"
void TIM2_IRQHandler(void)
{

	 if(TIM_GetITStatus(TIM2, TIM_IT_Update)!=RESET)
	 {

		 timeDelay--;
		 if(timeDelay==0)
		 			 TIM_Cmd(TIM2, DISABLE);
		 TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

	 }
}

void TIM3_IRQHandler(void)
{
	 if(TIM_GetITStatus(TIM3, TIM_IT_Update)!=RESET)
	 {
		 GPIO_ResetBits(GPIOE,GPIO_Pin_10);
		TIM_Cmd(TIM3, DISABLE);
		TIM_SetCounter(TIM3, 0);

		TIM_SetCounter(TIM7, 0);
		TIM_Cmd(TIM7, ENABLE);


		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	 }

}

void uruchomPomiar()
{
	TIM_Cmd(TIM3, ENABLE);
	GPIO_SetBits(GPIOE,GPIO_Pin_10);
	leftForwardMeasureComplete=false;
	centerForwardMeasureComplete=false;
	rightForwardMeasureComplete=false;
}

void TIM5_IRQHandler(void)
	{
		 if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		 {
			 uruchomPomiar();
			TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
		 }
	}

/*
 * konczy pomiar w przypadku gdy czujnik nie zwrocil odleglsoci zwraca 1
 */
void TIM7_IRQHandler(void)
{

	 if(TIM_GetITStatus(TIM7, TIM_IT_Update)!=RESET)
	 {
		 TIM_Cmd(TIM7, DISABLE);

		 if(!leftForwardMeasureComplete)
		 {
			 leftForwardMeasureComplete=true;
			 odlegloscLeftForward=1;
		 }

		 if(!centerForwardMeasureComplete)
		 {
			 centerForwardMeasureComplete=true;
			 odlegloscCenterForward=1;
		 }

		 if(!rightForwardMeasureComplete)
		 {
			 rightForwardMeasureComplete=true;
			 odlegloscRightForward=1;
		 }


		 //POSZUKAC LEPSZEGO MIejscA DLA tEgo

		 TIM_ClearITPendingBit(TIM7, TIM_IT_Update);

	 }

}

//////////////////////////////////////////////////////////////////////////////////////////////
//
/*
 * PRAWY CZUJNIK
 * Przy narastajacym zboczu oznacza wartosc licznika timera 7 jako start
 * Przy opadajacym zboczu oznacza wartosc licznika timera 7 jako koniec pomiaru i oblicza odlegosc
 *
 * gdy róznica miedzy stop - start jest ujemna nie zwraca odlegosci
 */
void measureForwardSensorRightForwawrd()
{
	//TIM4->CCR4=TIM4->ARR;
			if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4))
			{
				CzujnikLine4Start=TIM7->CNT;
			}
			else
			{
				CzujnikLine4Stop=TIM7->CNT;
					if((CzujnikLine4Stop-CzujnikLine4Start)>0&&!(rightForwardMeasureComplete))
					{
					odlegloscRightForward=(((((float)(CzujnikLine4Stop-CzujnikLine4Start))/(TIM7->ARR+1))/czestotliwoscTimeraPomiarowego)*170);
					rightForwardMeasureComplete=true;
					}
				}
}

/*
 * SRODKOWY CZUJNIK
 * Przy narastajacym zboczu oznacza wartosc licznika timera 7 jako start
 * Przy opadajacym zboczu oznacza wartosc licznika timera 7 jako koniec pomiaru i oblicza odlegosc
 *
 * gdy róznica miedzy stop - start jest ujemna nie zwraca odlegosci
 */
void measureForwardSensorCenterForward()
{

	//		TIM4->CCR4=TIM4->ARR;
				if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)){

					CzujnikLine6Start=TIM7->CNT;
				}
				else
				{
					CzujnikLine5Stop=TIM7->CNT;
					if((CzujnikLine5Stop-CzujnikLine5Start)>0&&!(centerForwardMeasureComplete))
					{
						odlegloscCenterForward=(float)(CzujnikLine5Stop-CzujnikLine5Start)/TIM7->ARR/czstotliwoscLicznikaPomiarowego*170;
						centerForwardMeasureComplete=true;

					}

				}

}

/*
 * LEWY CZUJNIK
 * Przy narastajacym zboczu oznacza wartosc licznika timera 7 jako start
 * Przy opadajacym zboczu oznacza wartosc licznika timera 7 jako koniec pomiaru i oblicza odlegosc
 *
 * gdy róznica miedzy stop - start jest ujemna nie zwraca odlegosci
 */
void measureForwardSensorLeftForward()
{
//
				if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)){

					CzujnikLine6Start=TIM7->CNT;
				}
				else
				{
					CzujnikLine6Stop=TIM7->CNT;
					if((CzujnikLine6Stop-CzujnikLine6Start)>0)
					{
						odlegloscLeftForward=(float)(CzujnikLine6Stop-CzujnikLine6Start)/TIM7->ARR/czstotliwoscLicznikaPomiarowego*170;
						leftForwardMeasureComplete=true;
					}

				}

}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)
	{

		odlegloscCenterForward=measureDistance(GPIOE,GPIO_Pin_5,&CzujnikLine5Start,&CzujnikLine5Stop,&centerForwardMeasureComplete);
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)
	{

		odlegloscLeftForward=measureDistance(GPIOE,GPIO_Pin_6,&CzujnikLine6Start,&CzujnikLine6Stop,&leftForwardMeasureComplete);
		EXTI_ClearITPendingBit(EXTI_Line6);
	}


}

void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4) != RESET)
	{
		odlegloscRightForward=measureDistance(GPIOE,GPIO_Pin_4,&CzujnikLine4Start,&CzujnikLine4Stop,&rightForwardMeasureComplete);

	EXTI_ClearITPendingBit(EXTI_Line4);
	}

}
