#include"PS2Controller.h"
#include"EnginePower.h"
int EZERO=0;//DEBUG POZBYC SIE W PRZYSZLOSCI
/*
 * Konfiguruje interfejs SPI do obs³ugi GAMEPADA
 */
void SPIConfiguration()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	//Zmniejszyc taktowanie czyli Pleskaler na Maxa
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_Init(SPI2, &SPI_InitStructure);

	SPI_Cmd(SPI2, ENABLE);
}

/*
 * Funkcja Debuguj¹ca
 */
void PrzepiszDoZmiennychGlobalnychZawartoscTablicy()
{
	podglad0PolaWTablicy=tabConfig[0];
	podglad1PolaWTablicy=tabConfig[1];
	podglad2PolaWTablicy=tabConfig[2];
	podglad3PolaWTablicy=tabConfig[3];
	podglad4PolaWTablicy=tabConfig[4];
	podglad5PolaWTablicy=tabConfig[5];
	podglad6PolaWTablicy=tabConfig[6];
	podglad7PolaWTablicy=tabConfig[7];
	podglad8PolaWTablicy=tabConfig[8];
}
/*
 * Wys³anie i odczyt jednego bajtu z kontrolera
 */
unsigned char pad_byte(unsigned char byte)
{
    char receive;
    SPI_I2S_SendData(SPI2, byte);
    while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
    uDelay(20);
    receive = SPI_I2S_ReceiveData(SPI2);
    return receive;
}

/*
 * Wysy³a/Odbiera sekwence bajtów które sk³adaj¹ siê na komêde
 * t = wskaŸnik do tablicy przechowuj¹cej komende
 * n = dlugosc komendy
 */
void pad_cmd(unsigned char t[],unsigned int n)
{
   unsigned int i;
   //ATT RESET
   GPIO_ResetBits(GPIOE,GPIO_Pin_11);
   for(i=0; i<n; i++)
   {
	   t[i]= pad_byte(t[i]);
	   PrzepiszDoZmiennychGlobalnychZawartoscTablicy();
   }
   //ATT SET
   PrzepiszDoZmiennychGlobalnychZawartoscTablicy();
   GPIO_SetBits(GPIOE,GPIO_Pin_11);
   uDelay(50);
}

/*
 * Pobiera informacje na temat stanu Gapmepada
 */
void padPoll()
{
	tabConfig[0] = 0x01;
	tabConfig[1] = 0x42; // komenda 0x42 - Controller poll
	tabConfig[2] = 0x00;
	tabConfig[3] = 0x00; // przyciski
	tabConfig[4] = 0x00; // przyciski
	tabConfig[5] = 0x00; // d¿ojstik prawy  lewo-prawo
	tabConfig[6] = 0x00; // d¿ojstik prawy  góra-dó³
	tabConfig[7] = 0x00; // d¿ojstik lewy   lewo-prawo
	tabConfig[8] = 0x00; // d¿ojstik lewy   gora-dó³
	// Wysy³amy pakiet danych z komend¹ 0x42(Controller poll),
	// w rezultacie otrzymujemy 9 bajtów z informacj¹ o stanie
	// przycisków i d¿ojstików analogowych
	pad_cmd(tabConfig, 9);
	// Wyœwietla na LEDach  wybrany bajt tablicy
	mDelay(50);

}
/*
 * Wymusza przejscie pada do trybu analogowego
 * Umozliwa korzystanie z analogow z funkconalnoscia przechwycenia stopnia wychlenia
 */
void padGoIntoAnalogMode()
{
	  // Prze³¹czamy gamepada w tryb analogowy, aby mieæ
	   // mo¿liwoœæ odczytywania d¿ojstików analogowych
	   // Komenda 0x44 "Turn on analog mode"
	   tabConfig[0]= 0x01;
	   tabConfig[1]= 0x44;
	   tabConfig[2]= 0x00;
	   tabConfig[3]= 0x01;
	   tabConfig[4]= 0x03; //
	   tabConfig[5]= 0x00;
	   tabConfig[6]= 0x00;
	   tabConfig[7]= 0x00;
	   tabConfig[8]= 0x00;
	   pad_cmd(tabConfig, 9);
}

/*
 * przejscie do konfiguracji gamePada
 */
void padGoIntoConfigurationMode()
{
	  // Komenda 0x43 "Go into configuration mode"
	   tabConfig[0]= 0x01;
	   tabConfig[1]= 0x43;
	   tabConfig[2]= 0x00;
	   tabConfig[3]= 0x01;
	   tabConfig[4]= 0x00;
	   pad_cmd(tabConfig, 5);
}

/*
 * Wyjscie z trybu konfiguracji
 */
void padExitConfigurationMode()
{
	// Komenda 0x43 "Exit config mode"
	   tabConfig[0] = 0x01;
	   tabConfig[1] = 0x43;
	   tabConfig[2] = 0x00;
	   tabConfig[3] = 0x00;
	   tabConfig[4] = 0x5A;
	   tabConfig[5] = 0x5A;
	   tabConfig[6] = 0x5A;
	   tabConfig[7] = 0x5A;
	   tabConfig[8] = 0x5A;
	   pad_cmd(tabConfig, 9);
}

/*
 * Podstawowa konfiguracja gamepada
 */
void pad_config(void)
{
	padGoIntoConfigurationMode();
	padGoIntoAnalogMode();
	padExitConfigurationMode();
	padPoll();
	skala=0.7;
   padConifgured=true;

}

//---------------------------------------------------------------------------
//Odczytywanie Przycisków Sprawdzanie pojedyñczych bitów
bool sprawdzBajt(uint8_t poleWtablicy,uint8_t bajt)
{
	int maska=1;//Zmienic na zmienna globalna tutaj tylko przywracac wartosc
	for(int i=0; i<bajt;i++)
		maska*=2;
	if((tabConfig[poleWtablicy]&maska) == 0)
		return true;
	else
		return false;
}
//---------------------------------------------------------------------------
//Dzia³a

/*
 * Sprawdza bit odpowiedzialny za zwiekszenie maksymanej mocy przekazywanych do silnikow
 */
void sprawdzNitro()
{
	if(sprawdzBajt(Shape,R2))
	{
		skala=1;
		TIM4->CCR4=TIM4->ARR;
	}
	else
	{
		skala=0.7	;
		TIM4->CCR4=0;
	}
}

//PROBLEMY Z STEROWANIEM PRZY UZYCIU MOSFETA POMYSL ODLOZONY
/*
 * Funkcja steruje pinem po³¹czonym z bramka tranzystora
 * Obsuguje przycisk w formie przerzutnika pistabilnego
 * Pierwszy if ma eliminowaæ przelaczanie sie stanu podczas wciskania przycisku( prawdopodobnie zbedne)
 */
void turnOffPower()
{
	if(sprawdzBajt(CrossFunction,START ))
	{
		if(counterButton<0)//CO TO MA BYC :P MIA£ ELIMINOWAC DRGANIA NA STYKACH
		{
			//DEBUG
			//PRAWDOPODBNIE TEN IF JEST ZBEDY
			counterButton++;
		}
		else
		{
			if(availableChangePowerSuplyStatus)
			{
				if(powerSuply)
				{
					powerSuply=false;
					TIM4->CCR2=0;
				}
				else
				{
					powerSuply=true;
					TIM4->CCR2=TIM4->ARR;
				}
				availableChangePowerSuplyStatus=false;
			}
		}
	}
	else
	{
		counterButton=0;
		availableChangePowerSuplyStatus=true;
	}
	//DEBUG
	czyDostepnaJestZmiana=availableChangePowerSuplyStatus;
	Zasilanie=powerSuply;
}

/*
 * Sprawdza jakie polecenia wyda³ u¿ytkownik i dostosowuje zachowanie robota do nich
 * Wywoluje funkcje sprawdzajace stan konkretych bitow
*/
void obslugaZdazen()//ROZBIC NA FUNKCJE SPRAWDZAJACE STAN PRZYCISKOW I DZIALAJACE NA SILNIKACH
{
	sprawdzNitro();
	turnOffPower();

		if(powerSuply&&AkumulatoryOK)
		{
			runMotorChannelRight();
			runMotorChannelLeft();
		}
		else
		{
			channelLeftStop();
			channelRightStop();
		}
	//ten IF jest zbedny symuluje tylko tranzystor mosfet
}

//---------------------------------------------------------------------------
/*
 * Funkcja Obs³uguj¹ca pada
 * 1 - Konfiguracja
 * 2 - StanPrzycisków
 * 3 - Zarz¹dzanie robotem
 *
 * Konfiguracja nastepuje tylko raz podczas startu, pozosta³e funkconalnosci realizowane sa co cykl
 */
int obsluga_kontrolera(void)
{
	if(!padConifgured)
		pad_config();
	padPoll();

	obslugaZdazen();
}
