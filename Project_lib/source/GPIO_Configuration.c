#include "GPIO_Configuration.h"
void GPIO_CzujnikUltradzwiekowy()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	//////TRIGER
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

}
void GPIO_MostekHConfiguration()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void GPIO_PWM_SignalConfiguration()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD , ENABLE);
	GPIO_InitTypeDef  GPIO_InitStructure;
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void GPIO_SPI_ChipSelectConfiguration()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure3;
		GPIO_InitStructure3.GPIO_Pin = GPIO_Pin_11;
		GPIO_InitStructure3.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure3.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure3.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOE, &GPIO_InitStructure3);
}

void GPIO_SPI()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB , ENABLE);
		GPIO_InitTypeDef GPIO_InitStructure2;
		GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
		GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure2.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure2.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure2);
		// SCK
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
		// MISO
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
		// MOSI
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);
}

void GPIO_SPI_Configuration()
{
	GPIO_SPI();
	GPIO_SPI_ChipSelectConfiguration();
}
void GPIO_ADC_Configuration()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE); // zegar dla portu GPIO z którego wykorzystany zostanie pin jako wejœcie ADC (PA1)

	GPIO_InitTypeDef GPIO_InitStructure;
	//inicjalizacja wejœcia ADC
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void GPIO_OutMOSFETBasePin()
{

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void GPIO_Configuration()
{

	GPIO_PWM_SignalConfiguration();
	GPIO_MostekHConfiguration();
	GPIO_SPI_Configuration();
	GPIO_CzujnikUltradzwiekowy();
	GPIO_ADC_Configuration();
	GPIO_OutMOSFETBasePin();
}
