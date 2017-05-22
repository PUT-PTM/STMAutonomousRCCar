#include "Interupt.h"
#include "GPIO_Configuration.h"
#include "PS2Controller.h"
int stanLiniE10;
int stanLiniE4;
int TIMER7CNT;


void configuration()
{
	SystemInit();
	GPIO_Configuration();
	SPIConfiguration();
	timerConfiguration();
	interuptConfigurations();
	EXTIconfiguration();
}

int main(void)
{

	configuration();
	TIM_Cmd(TIM4, ENABLE);
	TIM_Cmd(TIM5, ENABLE);
	padConifgured=false;
    while(1)
    {
    	stanLiniE10=GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10);
    	stanLiniE4=GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4);
    	obsluga_kontrolera();
    	TIMER7CNT=TIM7->CNT;
    }
}

//////////////////////////////////////////////////////////////
//void TimerConfiguration()
//{
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
//	int taktowanieZegara=84000000;
//		float freload =1000000; 							//czas po którym nastepuje przepelnienie licznika
//		int Period=1; 							//pojemnosc liczika
//		int Prescaler;							//Co ile impulsów nastepuje inkrementacja licznika
//
//		Prescaler=(taktowanieZegara/(freload*(Period+1)))-1;
//
//		//KOONFIGURACJA IMPULSÓW
//		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//		TIM_TimeBaseStructure.TIM_Period =Period; //ARR EUREKA
//		TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;
//		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//		TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
//		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
//
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//				TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
//
//		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
//
//				 freload =100000; 							//czas po którym nastepuje przepelnienie licznika
//				 Period=839; 							//pojemnosc liczika
//
//				Prescaler=(taktowanieZegara/(freload*(Period+1)))-1;
//
//				//KOONFIGURACJA IMPULSÓW
//				TIM_TimeBaseStructure.TIM_Period =Period; //ARR EUREKA
//				TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;
//				TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//				TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
//				TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
//
//				//KONFIGURACJA PWM IMPORTANT!!!!!
//				TIM_OCInitTypeDef TIM_OCInitStructure;
//				/* PWM1 Mode configuration: */
//				TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//				TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//				TIM_OCInitStructure.TIM_Pulse =0;
//				TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//				//1 kanal
//				TIM_OC1Init(TIM4, &TIM_OCInitStructure);
//				TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
//				//2 Kanal
//				TIM_OC4Init(TIM4, &TIM_OCInitStructure);
//				TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
//				//3 Kanal
//				TIM_OC3Init(TIM4, &TIM_OCInitStructure);
//				TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
//
//}
