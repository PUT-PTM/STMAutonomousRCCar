#include "Interupt.h"
#include"EnginePower.h"
#include "GPIO_Configuration.h"
#include "PS2Controller.h"
#include "ADC_Configuration.h"
int stanLiniE10;
int stanLiniE4;
int TIMER7CNT;

int zmiennaDebugujacaAdres;

void defineGlobalVarablies()
{
	//PS2Controller.h
	bool powerSuply=false;
	bool availableChangePowerSuplyStatus=true;
	uint8_t counterButton=0;
	int czyDostepnaJestZmiana = 0;
	int Zasilanie = 0;

	////////////////
	probaPomiaruLeftForward=0;
	probaPomiaruCenterForward=0;
	probaPomiaruRightForward=0;

//	////////////////POPRAWIC TEN SYF
//	motorLeft.PWMChannel=&(TIM4->CCR3);
//	motorLeft.inputPort=GPIOE;
//	motorLeft.inputSignalOne=GPIO_Pin_2;
//	motorLeft.inputSignalTwo=GPIO_Pin_3;
//	motorLeft.axis =LY;
//
//	/////////////////////////////////////
//	motorRight.PWMChannel=&(TIM4->CCR1);
//	motorRight.inputPort=GPIOE;
//	motorRight.inputSignalOne=GPIO_Pin_0;
//	motorRight.inputSignalTwo=GPIO_Pin_1;
//	motorRight.axis =RY;
}
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

int main(void)
{

	configuration();
	TIM_Cmd(TIM4, ENABLE);
	TIM_Cmd(TIM5, ENABLE);
	padConifgured=false;
	zmiennaDebugujacaAdres=&(TIM4->CCR3);
    while(1)
    {
    	//stanLiniE10=GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10);
    	//stanLiniE4=GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4);
    	obsluga_kontrolera();
    	//TIMER7CNT=TIM7->CNT;
    	pomiarADC();
    }
}
