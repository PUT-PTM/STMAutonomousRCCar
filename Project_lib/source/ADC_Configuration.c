#include "ADC_Configuration.h"

void adcConfiguration2()
{
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
		// niezale¿ny tryb pracy przetworników
		ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
		// zegar g³ówny podzielony przez 2
		ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
		// opcja istotna tylko dla trybu multi ADC
		ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
		// czas przerwy pomiêdzy kolejnymi konwersjami
		ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
		ADC_CommonInit(&ADC_CommonInitStructure);
}

void adcConfiguration1()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); // zegar dla modu³u ADC1
	ADC_InitTypeDef ADC_InitStructure;
		//ustawienie rozdzielczoœci przetwornika na maksymaln¹ (12 bitów)
		ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
		//wy³¹czenie trybu skanowania (odczytywaæ bêdziemy jedno wejœcie ADC
		//w trybie skanowania automatycznie wykonywana jest konwersja na wielu //wejœciach/kana³ach)
		ADC_InitStructure.ADC_ScanConvMode = DISABLE;
		//w³¹czenie ci¹g³ego trybu pracy
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		//wy³¹czenie zewnêtrznego wyzwalania
		//konwersja mo¿e byæ wyzwalana timerem, stanem wejœcia itd. (szczegó³y w //dokumentacji)
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
		ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
		//wartoœæ binarna wyniku bêdzie podawana z wyrównaniem do prawej
		//funkcja do odczytu stanu przetwornika ADC zwraca wartoœæ 16-bitow¹
		//dla przyk³adu, wartoœæ 0xFF wyrównana w prawo to 0x00FF, w lewo 0x0FF0
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		//liczba konwersji równa 1, bo 1 kana³
		ADC_InitStructure.ADC_NbrOfConversion = 1;
		// zapisz wype³nion¹ strukturê do rejestrów przetwornika numer 1
		ADC_Init(ADC1, &ADC_InitStructure);


		ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_84Cycles);

}

void adcConfiguration()
{

	adcConfiguration2();
	adcConfiguration1();
	ADC_Cmd(ADC1, ENABLE);
}









