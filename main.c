#include "Interupt.h"
#include"EnginePower.h"
#include "GPIO_Configuration.h"
#include "PS2Controller.h"
#include "ADC_Configuration.h"
int stanLiniE10;
int stanLiniE4;
int TIMER7CNT;



/*
 *
 */
void defineGlobalVarablies()
{
	//PS2Controller.h
	powerSuply=false;
	availableChangePowerSuplyStatus=true;
	counterButton=0;
	int czyDostepnaJestZmiana = 0;
	int Zasilanie = 0;

	////////////////
	probaPomiaruLeftForward=0;
	probaPomiaruCenterForward=0;
	probaPomiaruRightForward=0;


	bool SensorON=false;
	bool availableChangeSensroStatus=true;
}

/*
 *
 */
void configuration()
{
	SystemInit();
	GPIO_Configuration();
	SPIConfiguration();
	timerConfiguration();
	interuptConfigurations();
	extiConfiguration();
	adcConfiguration();
}

/*
 *
 */
void pomiarADC()
{
	ADC_SoftwareStartConv(ADC1);
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
		ADC_Result = ADC_GetConversionValue(ADC1);
		//DROBNA HISTEREEZA
		if(ADC_Result>PROGAKCPETOWALNY)
		{
			GPIO_SetBits(GPIOE,GPIO_Pin_12);
			AkumulatoryOK=GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12);
		}

		if(ADC_Result<DOPUSZCZALNY_PROGR_OZLADOWANIA)
		{
			GPIO_ResetBits(GPIOE,GPIO_Pin_12);
			AkumulatoryOK=GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12);
		}
}

/*
 * MAIN LOOP
 */
int main(void)
{

	configuration();
	TIM_Cmd(TIM4, ENABLE);
	TIM_Cmd(TIM5, ENABLE);
	padConifgured=false;

    while(1)
    {
    	obsluga_kontrolera();
    	TIMER7CNT=TIM5->CNT;
    	pomiarADC();
    }
}
