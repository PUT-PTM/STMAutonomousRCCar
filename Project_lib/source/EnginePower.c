#include"EnginePower.h"

#include"Algorytm.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////s
/*
 * 									DO POPRAWY
 *
 * ZREDUKOWAC REDUNDANCJE W KODZIE POPRZEZ SKORZYSTANIE Z FUNKCJI PRZEKAZUJACYCH ZMIENNE JAKO
 * PARAMETTY PRZEZ WSKAZNIK. W RAZIE MOZLIWOSCI SKORZYSTAC Z ENUM ZAMIAST WARTOSCI WPISYWANYCH NA
 * STYWNO.	ZNALESC WSZYSTKIE MOZLIWE OPCJE GDZIE ZASTOSOWAC STALE ZAMIAST ZMIENNYCH(TO SAMO CO DO ENUM)
 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void setChannelLeft(bool B1, bool B2)
{

	if(B1)
	{
		GPIO_SetBits(GPIOE,GPIO_Pin_2);
	}
	else
	{
		GPIO_ResetBits(GPIOE,GPIO_Pin_2);
	}
	if(B2)
	{
		GPIO_SetBits(GPIOE,GPIO_Pin_3);
	}
	else
	{
		GPIO_ResetBits(GPIOE,GPIO_Pin_3);
	}
	BO1=B1;
	BO2=B2;

}

void channelLeftStop()
{
	directionChannelLeft(0,0);
}
void channelLeftForward()
{
	WypelnienieLeftAxis=TIM4->ARR*skala*(float)(127-tabConfig[LY])/127;
}
void channelLeftBack()
{
	WypelnienieLeftAxis=(-1)*(TIM4->ARR*skala*(float)(tabConfig[LY]-127)/128);
}
//void channelLeftBack()
//{
//	WypelnienieLeftAxis=TIM4->CCR3=TIM4->ARR*skala*(float)(tabConfig[LY]-127)/128;
//}


void directionChannelLeft(int odpychanie, int leftAxis)
{
	int Rezultat=leftAxis-odpychanie;

		if(Rezultat>0)
		{
			setChannelLeft(1,0);
		}
		else if(Rezultat<0)
		{
			Rezultat*=(-1);
			setChannelLeft(0,1);
		}
		else
		{
			setChannelLeft(0,0);
		}
		TIM4->CCR3=Rezultat;
}
//0 , 1 do ty³u
void leftAxisUserCommand()
{
	if(tabConfig[LY]<127)
		{
			channelLeftForward();
		}
		else if(tabConfig[LY]>127)
		{
			channelLeftBack();
		}
		else
		{
			WypelnienieLeftAxis=0;
		}
}

void runMotorChannelLeft()
{
	leftAxisUserCommand();
	odpychanieLeft=missColissionForLeftWheel();
	directionChannelLeft(odpychanieLeft,WypelnienieLeftAxis);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void setChannelRight(bool A1,bool A2)
{

		if(A1)
		{
			GPIO_SetBits(GPIOE,GPIO_Pin_0);
		}
		else
		{
			GPIO_ResetBits(GPIOE,GPIO_Pin_0);
		}
		if(A2)
		{
			GPIO_SetBits(GPIOE,GPIO_Pin_1);
		}
		else
		{
			GPIO_ResetBits(GPIOE,GPIO_Pin_1);
		}

	AO1=A1;
	AO2=A2;
}

void channelRightStop()
{
	directionChannelRight(0,0);
}
void channelRightForward()
{
	WypelnienieRightAxis=TIM4->ARR*skala*(float)(127-tabConfig[RY])/127;
}
void channelRightBack()
{
	WypelnienieRightAxis=(-1)*(TIM4->ARR*skala*(float)(tabConfig[RY]-127)/128);
}
//void channelRightBack()
//{
//	WypelnienieRightAxis=TIM4->CCR1=TIM4->ARR*skala*(float)(tabConfig[RY]-127)/128;
//}
int debugRIGHT;

void directionChannelRight(int odpychanie, int rightAxis)
{
	debugRIGHT=odpychanie;
	int Rezultat=rightAxis-odpychanie;

		if(Rezultat>0)
		{
			setChannelRight(1,0);
		}
		else if(Rezultat<0)
		{
			Rezultat*=(-1);
			setChannelRight(0,1);
		}
		else
		{
			setChannelRight(0,0);
		}
		TIM4->CCR1=Rezultat;
}

void rightAxisUserCommand()
{
	if(tabConfig[RY]<127)
		{
			channelRightForward();
		}
		else if(tabConfig[RY]>127)
		{
			channelRightBack();
		}
		else
		{
			WypelnienieRightAxis=0;
		}
}

void runMotorChannelRight()
{
	rightAxisUserCommand();
	odpychanieRight=missColissionForRightWheel();

	directionChannelRight(odpychanieRight,WypelnienieRightAxis);


}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FUNKCJE DO PRZEROBIENIA
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void setChannelRight(bool A1,bool A2)
//void channelRightStop()
//void channelRightForward()
//void channelRightBack()
//void directionChannelRight(int odpychanie, int rightAxis)
//void runMotorChannelRight()
//void rightAxisUserCommand()

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FUNKCJE ULEPSZONE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///*
// *
// */
//float calculateCommandForward(uint16_t axis)
//{
//	return TIM4->ARR*skala*(float)(127-tabConfig[axis])/127;
//}
//
///*
// *
// */
//float calculateCommandBack(uint16_t axis)
//{
//	return(-1)*(TIM4->ARR*skala*(float)(tabConfig[LY]-127)/128);
//}
//
///*
// *
// */
//float CommandStop()
//{
//	return 0.0;
//}
//
///*
// * Pobiera wychylenie analoga
// * Przymuje jeden parametr okreslajacy ktory analog i ktora os
// */
//float readUserAxisCommand(uint16_t axis)
//{
//	if(tabConfig[axis]<127)
//	{
//		return	calculateCommandForward(axis);
//	}
//	else if(tabConfig[axis]>127)
//	{
//		return calculateCommandBack(axis);
//	}
//	else
//	{
//		return CommandStop();
//	}
//}
//
///*
// *
// */
//void setMotorDirection(Motor motor, bool input1,bool input2)
//{
//	if(input1)
//	{
//		GPIO_SetBits(motor.inputPort,motor.inputSignalOne);
//	}
//	else
//	{
//		GPIO_ResetBits(motor.inputPort,motor.inputSignalOne);
//	}
//	if(input2)
//	{
//		GPIO_SetBits(motor.inputPort,motor.inputSignalTwo);
//	}
//	else
//	{
//		GPIO_ResetBits(motor.inputPort,motor.inputSignalTwo);
//	}
//	//ONLY DEBUG
//	if(motor.inputSignalOne=GPIO_Pin_2)
//	{
//		BO1=input1;
//		BO2=input2;
//	}
//	else
//	{
//		AO1=input1;
//		AO2=input2;
//	}
//
//}
//
///*
// *
// */
//void choseMotorDirection(Motor motor,uint16_t userVector, uint16_t obstacleVector)
//{
//
//	int Result=userVector-obstacleVector;
//
//		if(Result>0)
//		{
//			setChannelRight(1,0);
//		}
//		else if(Result<0)
//		{
//			Result*=(-1);
//			setChannelRight(0,1);
//		}
//		else
//		{
//			setChannelRight(0,0);
//		}
//		motor.PWMChannel=Result;
//}
//
///*
// *
// */
////Zbyt du¿o funkcjonalnosci
//void runMotor(Motor motor)//,uint16_t userVector)//, uint16_t obstacleVector)
//{
//
//	int odpychanie=0;
//
//	if(0.5-odlegloscCenterForward>0)
//	{
//		TIM4->CCR1;
//		odpychanie=motor.PWMChannel=(unsigned int)(TIM4->ARR*skala*(float)((0.5-odlegloscCenterForward)/0.5));
//	}
//	choseMotorDirection(motor,readUserAxisCommand(motor.axis),odpychanie);
//
//}
