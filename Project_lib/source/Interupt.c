
#include "interupt.h"
////////////////////////////////////////////////////////////////////

void EXTI_Line_4()
{
	//zasilanie
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//Konfiguracja
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;// wybór numeru aktualnie konfigurowanej linii przerwañ
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;// wybór trybu - przerwanie b¹dŸ zdarzenie
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;// wybór zbocza, na które zareaguje przerwanie
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	 SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);
}
void EXTI_Line_5()
{
	//zasilanie
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//Konfiguracja
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line5;// wybór numeru aktualnie konfigurowanej linii przerwañ
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;// wybór trybu - przerwanie b¹dŸ zdarzenie
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;// wybór zbocza, na które zareaguje przerwanie
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;// uruchom dan¹ liniê przerwañ
	EXTI_Init(&EXTI_InitStructure);// zapisz strukturê konfiguracyjn¹ przerwañ zewnêtrznych do rejestrów

	 SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource5);
}
void EXTI_Line_6()
{
	//zasilanie
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//Konfiguracja
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line6;// wybór numeru aktualnie konfigurowanej linii przerwañ
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;// wybór trybu - przerwanie b¹dŸ zdarzenie
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;// wybór zbocza, na które zareaguje przerwanie
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;// uruchom dan¹ liniê przerwañ
	EXTI_Init(&EXTI_InitStructure);// zapisz strukturê konfiguracyjn¹ przerwañ zewnêtrznych do rejestrów

	 SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource6);
}
void extiConfiguration()
{
	EXTI_Line_4();
	EXTI_Line_5();
	EXTI_Line_6();
}
//
//void EXTI4_IRQHandler(void)
//	{
//		if(EXTI_GetITStatus(EXTI_Line4) != RESET)
//		{
//			if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)){
//
//					CzujnikLine4Start=TIM7->CNT;
//								TIM_Cmd(TIM7, ENABLE);
//				}
//				else
//				{
//					CzujnikLine4Stop=TIM7->CNT;
//					odleglosc=(float)(CzujnikLine4Stop-CzujnikLine4Start)/TIM7->ARR/czstotliwoscLicznikaPomiarowego*170;
//			//		TIM4->CCR2=(1-odleglosc)*TIM4->ARR;
//				}
//				EXTI_ClearITPendingBit(EXTI_Line4);
//
//
//		}
//	}

//void EXTI9_5_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line5) != RESET)
//	{
//		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)){
//
//			CzujnikLine5Start=TIM7->CNT;
//						TIM_Cmd(TIM7, ENABLE);
//		}
//		else
//		{
//			CzujnikLine5Stop=TIM7->CNT;
//			odleglosc2=(float)(CzujnikLine5Stop-CzujnikLine5Start)/TIM7->ARR/czstotliwoscLicznikaPomiarowego*170;
//			//TIM4->CCR3=(1-odleglosc2)*TIM4->ARR;
//		}
//		EXTI_ClearITPendingBit(EXTI_Line5);
//	}
//
//	if(EXTI_GetITStatus(EXTI_Line6) != RESET)
//		{
//
//			if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)){
//				TIM4->CCR2=TIM4->ARR;
//				CzujnikLine6Start=TIM7->CNT;
//							TIM_Cmd(TIM7, ENABLE);
//			}
//			else
//			{
//				CzujnikLine6Stop=TIM7->CNT;
//				odleglosc3=(float)(CzujnikLine6Stop-CzujnikLine6Start)/TIM7->ARR/czstotliwoscLicznikaPomiarowego*170;
////				TIM4->CCR3=(1-odleglosc)*TIM4->ARR;
//			}
//			EXTI_ClearITPendingBit(EXTI_Line6);
//		}
//}

////////////////////////////////////////////////////////////////////
void interiptEXTILine4()
{
	NVIC_InitTypeDef NVIC_InitStructure;

			NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;	// numer przerwania
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;// priorytet g³ówny
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;// subpriorytet
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	// uruchom dany kana³
			NVIC_Init(&NVIC_InitStructure);// zapisz wype³nion¹ strukturê do rejestrów
}
void interiptEXTILine9_5()
{
	NVIC_InitTypeDef NVIC_InitStructure;

			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;	// numer przerwania
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;// priorytet g³ówny
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;// subpriorytet
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	// uruchom dany kana³
			NVIC_Init(&NVIC_InitStructure);// zapisz wype³nion¹ strukturê do rejestrów
}
void interuptEXTI()
{
	interiptEXTILine4();
	interiptEXTILine9_5();
}
void interuptTimer2()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;// numer przerwania
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;// priorytet g³ówny
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	// uruchom dany kana³
	NVIC_Init(&NVIC_InitStructure);// zapisz wype³nion¹ strukturê do rejestrów
}
void interuptTimer3()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;// numer przerwania
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;// priorytet g³ówny
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	// uruchom dany kana³
	NVIC_Init(&NVIC_InitStructure);// zapisz wype³nion¹ strukturê do rejestrów
}
void interuptTimer5()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;// numer przerwania
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;// priorytet g³ówny
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	// uruchom dany kana³
	NVIC_Init(&NVIC_InitStructure);// zapisz wype³nion¹ strukturê do rejestrów
}
void interuptTimer7()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;// numer przerwania
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;// priorytet g³ówny
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	// uruchom dany kana³
	NVIC_Init(&NVIC_InitStructure);// zapisz wype³nion¹ strukturê do rejestrów
}
void interuptConfigurations(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	interuptTimer2();
	interuptTimer3();
	interuptTimer5();
	interuptTimer7();
	interuptEXTI();

}

