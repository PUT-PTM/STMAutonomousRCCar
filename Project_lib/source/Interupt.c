#include "interupt.h"

/*
 *
 */
void EXTI_Line_4()
{
	//zasilanie
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//Konfiguracja
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;// wyb�r numeru aktualnie konfigurowanej linii przerwa�
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;// wyb�r trybu - przerwanie b�d� zdarzenie
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;// wyb�r zbocza, na kt�re zareaguje przerwanie
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	 SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);
}

/*
 *
 */
void EXTI_Line_5()
{
	//zasilanie
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//Konfiguracja
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line5;// wyb�r numeru aktualnie konfigurowanej linii przerwa�
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;// wyb�r trybu - przerwanie b�d� zdarzenie
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;// wyb�r zbocza, na kt�re zareaguje przerwanie
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;// uruchom dan� lini� przerwa�
	EXTI_Init(&EXTI_InitStructure);// zapisz struktur� konfiguracyjn� przerwa� zewn�trznych do rejestr�w

	 SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource5);
}

/*
 *
 */
void EXTI_Line_6()
{
	//zasilanie
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//Konfiguracja
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line6;// wyb�r numeru aktualnie konfigurowanej linii przerwa�
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;// wyb�r trybu - przerwanie b�d� zdarzenie
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;// wyb�r zbocza, na kt�re zareaguje przerwanie
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;// uruchom dan� lini� przerwa�
	EXTI_Init(&EXTI_InitStructure);// zapisz struktur� konfiguracyjn� przerwa� zewn�trznych do rejestr�w

	 SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource6);
}

/*
 *
 */
void extiConfiguration()
{
	EXTI_Line_4();
	EXTI_Line_5();
	EXTI_Line_6();
}

////////////////////////////////////////////////////////////////////
/*
 *
 */
void interiptEXTILine4()
{
	NVIC_InitTypeDef NVIC_InitStructure;

			NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;	// numer przerwania
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;// priorytet g��wny
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;// subpriorytet
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	// uruchom dany kana�
			NVIC_Init(&NVIC_InitStructure);// zapisz wype�nion� struktur� do rejestr�w
}

/*
 *
 */
void interiptEXTILine9_5()
{
	NVIC_InitTypeDef NVIC_InitStructure;

			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;	// numer przerwania
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;// priorytet g��wny
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;// subpriorytet
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	// uruchom dany kana�
			NVIC_Init(&NVIC_InitStructure);// zapisz wype�nion� struktur� do rejestr�w
}

/*
 *
 */
void interuptEXTI()
{
	interiptEXTILine4();
	interiptEXTILine9_5();
}

/*
 *
 */
void interuptTimer2()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;// numer przerwania
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;// priorytet g��wny
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	// uruchom dany kana�
	NVIC_Init(&NVIC_InitStructure);// zapisz wype�nion� struktur� do rejestr�w
}

/*
 *
 */
void interuptTimer3()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;// numer przerwania
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;// priorytet g��wny
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	// uruchom dany kana�
	NVIC_Init(&NVIC_InitStructure);// zapisz wype�nion� struktur� do rejestr�w
}

/*
 *
 */
void interuptTimer5()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;// numer przerwania
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;// priorytet g��wny
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	// uruchom dany kana�
	NVIC_Init(&NVIC_InitStructure);// zapisz wype�nion� struktur� do rejestr�w
}

/*
 *
 */
void interuptTimer7()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;// numer przerwania
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;// priorytet g��wny
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	// uruchom dany kana�
	NVIC_Init(&NVIC_InitStructure);// zapisz wype�nion� struktur� do rejestr�w
}

/*
 *
 */
void interuptConfigurations(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	interuptTimer2();
	interuptTimer3();
	interuptTimer5();
	interuptTimer7();
	interuptEXTI();

}

