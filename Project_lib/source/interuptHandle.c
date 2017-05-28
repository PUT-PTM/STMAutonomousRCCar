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


/*
 * USTAWIA NEUTRALNA WARTOSC
 */
void setNeutralValue()
{
	 leftForwardMeasureComplete=true;
	 odlegloscLeftForward=neutralDistance;

	 centerForwardMeasureComplete=true;
	 odlegloscCenterForward=neutralDistance;

	 rightForwardMeasureComplete=true;
	 odlegloscRightForward=neutralDistance;
}

/*
 * URUCHAMIA POMIAR W PRZYPADKU GDY CZUJNIK ZOSTA£ WY£¥CZONY USTAWIA ODLEGLOSCI NA NEUTRALNA WARTOSC
 */
void TIM5_IRQHandler(void)
	{
		 if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		 {
			 if(!SensorON)
			 {
				 TIM_Cmd(TIM5,DISABLE);
				 setNeutralValue();
			 }
			 else
			 {
				 uruchomPomiar();
			 }

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

		 {
			 TIM_Cmd(TIM7, DISABLE);
			 if(!leftForwardMeasureComplete)
			 {
				 leftForwardMeasureComplete=true;
				 obstacleNoDetected(&odlegloscLeftForward,&probaPomiaruLeftForward);
			 }
			 if(!centerForwardMeasureComplete)
			 {
				 centerForwardMeasureComplete=true;
				 obstacleNoDetected(&odlegloscCenterForward,&probaPomiaruCenterForward);
			 }
			 if(!rightForwardMeasureComplete)
			 {
				 rightForwardMeasureComplete=true;
				 obstacleNoDetected(&odlegloscRightForward,&probaPomiaruRightForward);
			 }
			 TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
		 }

	 }

}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)
	{
		measureDistance(&odlegloscCenterForward,GPIOE,GPIO_Pin_5,&CzujnikLine5Start,&CzujnikLine5Stop,&centerForwardMeasureComplete,&probaPomiaruCenterForward);
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)
	{
		measureDistance(&odlegloscRightForward,GPIOE,GPIO_Pin_6,&CzujnikLine6Start,&CzujnikLine6Stop,&rightForwardMeasureComplete,&probaPomiaruRightForward);
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
}

void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4) != RESET)
	{
		measureDistance(&odlegloscLeftForward,GPIOE,GPIO_Pin_4,&CzujnikLine4Start,&CzujnikLine4Stop,&leftForwardMeasureComplete,&probaPomiaruLeftForward);
	EXTI_ClearITPendingBit(EXTI_Line4);
	}
}
