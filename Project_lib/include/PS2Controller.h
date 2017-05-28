#ifndef PS2Controller
#define PS2Controller
#include"GPIO_Configuration.h"
#include"czujniki.h"
#include<stdbool.h>
#include "stm32f4xx_spi.h"
int CMD;

unsigned short podglad0PolaWTablicy;
unsigned short podglad1PolaWTablicy;
unsigned short podglad2PolaWTablicy;
unsigned short podglad3PolaWTablicy;
unsigned short podglad4PolaWTablicy;
unsigned short podglad5PolaWTablicy;
unsigned short podglad6PolaWTablicy;
unsigned short podglad7PolaWTablicy;
unsigned short podglad8PolaWTablicy;

bool padConifgured;

bool powerSuply;
bool availableChangePowerSuplyStatus;
uint8_t counterButton;
int czyDostepnaJestZmiana;
int Zasilanie;


//Bity odpowiedzialne za konktetne przyciski
enum KsztaltyITyl
{
	L2=0,
	R2=1,
	R1=2,
	L1=3,
	Triangle=4,
	Circle=5,
	Cross=6,
	Square=7
};
enum KrzyzakFunction{
	SELECT=0,
	JOYR=1,
	JOYL=2,
	START=3,
	CrossUP=4,
	CrossRIGHT=5,
	CrossDOWN=6,
	CrossLEFT=7
};
//Pola w tablicy odpowiedzialne za osie
enum PolaWTablicy
{
	CrossFunction=3,//Krzy¿ak i Przyciski funkcyjne
	Shape=4,		//Przyciski z kszta³tami("Prawy Krzy¿ak"), Przyciski z ty³u;
	LX=7,			//Lewa os Lewo Prawo
	LY=8,			//Lewa os Góra Dó³
	RX=5,			//Prawa os Lewo Prawo
	RY=6			//Prawa os Góra Dó³
};
char tabConfig[9];


void SPIConfiguration();

void PrzepiszDoZmiennychGlobalnychZawartoscTablicy();
unsigned char pad_byte(unsigned char byte);
void pad_cmd(unsigned char t[],unsigned int n);
void pad_config(void);
int obsluga_kontrolera(void);
int AkumulatoryOK;

#endif
