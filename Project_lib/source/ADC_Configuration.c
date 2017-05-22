#include "ADC_Configuration.h"

void adcConfiguration2()
{
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
		// niezale�ny tryb pracy przetwornik�w
		ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
		// zegar g��wny podzielony przez 2
		ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
		// opcja istotna tylko dla trybu multi ADC
		ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
		// czas przerwy pomi�dzy kolejnymi konwersjami
		ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
		ADC_CommonInit(&ADC_CommonInitStructure);
}

void adcConfiguration1()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); // zegar dla modu�u ADC1
	ADC_InitTypeDef ADC_InitStructure;
		//ustawienie rozdzielczo�ci przetwornika na maksymaln� (12 bit�w)
		ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
		//wy��czenie trybu skanowania (odczytywa� b�dziemy jedno wej�cie ADC
		//w trybie skanowania automatycznie wykonywana jest konwersja na wielu //wej�ciach/kana�ach)
		ADC_InitStructure.ADC_ScanConvMode = DISABLE;
		//w��czenie ci�g�ego trybu pracy
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		//wy��czenie zewn�trznego wyzwalania
		//konwersja mo�e by� wyzwalana timerem, stanem wej�cia itd. (szczeg�y w //dokumentacji)
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
		ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
		//warto�� binarna wyniku b�dzie podawana z wyr�wnaniem do prawej
		//funkcja do odczytu stanu przetwornika ADC zwraca warto�� 16-bitow�
		//dla przyk�adu, warto�� 0xFF wyr�wnana w prawo to 0x00FF, w lewo 0x0FF0
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		//liczba konwersji r�wna 1, bo 1 kana�
		ADC_InitStructure.ADC_NbrOfConversion = 1;
		// zapisz wype�nion� struktur� do rejestr�w przetwornika numer 1
		ADC_Init(ADC1, &ADC_InitStructure);


		ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_84Cycles);

}

void adcConfiguration()
{

	adcConfiguration2();
	adcConfiguration1();
	ADC_Cmd(ADC1, ENABLE);
}









