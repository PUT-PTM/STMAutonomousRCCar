#include"TIMER.h"

/*
 *
 */
void uDelay(unsigned int delay)
{
	timeDelay=delay;

	TIM_Cmd(TIM2, ENABLE);
	while(timeDelay>0);
}

/*
 *
 */
void mDelay(unsigned int delay)
{
	timeDelay=delay*1000;

		TIM_Cmd(TIM2, ENABLE);
		while(timeDelay>0);
}

/*
 *
 */
int calculatePresacler( int Period, int  freload)
{
	return (_TAKTOWANIEZEGARA/(freload*(Period+1)))-1;
}

/*
 *
 */
void timer2Configuration()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	float freload =1000000;
	int Period=1;


	//KOONFIGURACJA IMPULSÓW
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period =Period; //ARR EUREKA
	TIM_TimeBaseStructure.TIM_Prescaler = calculatePresacler(Period,freload);
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}

/*
 *
 */
void timer3Configuration()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	float freload =100000;
	int Period=839;


	//KOONFIGURACJA IMPULSÓW
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period =Period; //ARR EUREKA
	TIM_TimeBaseStructure.TIM_Prescaler = calculatePresacler(Period,freload);
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}

/*
 *
 */
void TIM4Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	int freload =50000; 							//czas po którym nastepuje przepelnienie licznika
	int Period=839; 							//pojemnosc liczika


	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	//KOONFIGURACJA IMPULSÓW
	TIM_TimeBaseStructure.TIM_Period =Period; //ARR EUREKA
	TIM_TimeBaseStructure.TIM_Prescaler = calculatePresacler(Period,freload);
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

}

/*
 *
 */
void Tim4_PWM_Configuration()
{
	//KONFIGURACJA PWM IMPORTANT!!!!!
		TIM_OCInitTypeDef TIM_OCInitStructure;
		/* PWM1 Mode configuration: */
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse =0;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		//1 kanal
		TIM_OC1Init(TIM4, &TIM_OCInitStructure);
		TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
		//2 kanal
		TIM_OC2Init(TIM4, &TIM_OCInitStructure);
		TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
		//3 Kanal
		TIM_OC3Init(TIM4, &TIM_OCInitStructure);
		TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
		//4 Kanal
		TIM_OC4Init(TIM4, &TIM_OCInitStructure);
		TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
}

/*
 *
 */
void timer4Configuration()
{
	TIM4Config();
	Tim4_PWM_Configuration();

}

/*
 *
 */
void timer5Configuration()
{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

			int freload =16; 							//czas po którym nastepuje przepelnienie licznika
			int Period=9999; 							//pojemnosc liczika

			//KOONFIGURACJA IMPULSÓW
			TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
			TIM_TimeBaseStructure.TIM_Period =Period; //ARR EUREKA
			TIM_TimeBaseStructure.TIM_Prescaler = calculatePresacler(Period,freload);;
			TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
			TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
			TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

			TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
				TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
}

/*
 *
 */
void timer7Configuration()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
		float freload =czstotliwoscLicznikaPomiarowego;
		int Period=24999;
		int Plescaler=19;


		//KOONFIGURACJA IMPULSÓW
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_TimeBaseStructure.TIM_Period =Period; //ARR EUREKA
		TIM_TimeBaseStructure.TIM_Prescaler = Plescaler;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);

		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
		TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);

		czestotliwoscTimeraPomiarowego=84000000/((Period+1)*(Plescaler+1));
}

/*
 *
 */
void timerConfiguration()
{
	timer2Configuration();
	timer3Configuration();
	timer4Configuration();
	timer5Configuration();
	timer7Configuration();
}
