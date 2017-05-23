#include"EnginePower.h"
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
	WypelnienieRightAxis=0;
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
	int Odpychanie=0;

		if(0.5-odlegloscCenterForward>0)
		{
			Odpychanie=TIM4->CCR3=TIM4->ARR*skala*(float)((0.5-odlegloscCenterForward)/0.5);
		}
		directionChannelLeft(Odpychanie,WypelnienieLeftAxis);

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
	WypelnienieRightAxis=0;
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
	int Odpychanie=0;

		if(0.5-odlegloscCenterForward>0)
		{
			Odpychanie=TIM4->CCR1=TIM4->ARR*skala*(float)((0.5-odlegloscCenterForward)/0.5);
		}
	directionChannelRight(Odpychanie,WypelnienieRightAxis);


}
