#ifndef EnginePower
#define EnginePower
#include"GPIO_Configuration.h"
#include"PS2Controller.h"
#include <stdbool.h>
#include <Interupt.h>
//ZROBIC TO LEPIEJ ABORT
//typedef struct
//{
//	uint16_t inputPort;
//	uint16_t inputSignalOne;
//	uint16_t inputSignalTwo;
//	uint32_t* PWMChannel;
//	uint16_t axis;
//}Motor;
//
//Motor motorLeft;
//Motor motorRight;

//TYLKO DEBUG
int AO1;
int AO2;
int BO1;
int BO2;


int Odpychanie;
float skala;
int WypelnienieRightAxis;
int WypelnienieLeftAxis;
void setChannelRight(bool A1,bool A2);
void setChanelB(bool B1, bool B2);
void runMotorChannelRight();//POWINNO ZNIKNAC
#endif
