#ifndef EnginePower
#define EnginePower
#include"GPIO_Configuration.h"
#include"PS2Controller.h"
#include <stdbool.h>
#include <Interupt.h>
//TYLKO DEBUG
int AO1;
int AO2;
int BO1;
int BO2;

float skala;
int WypelnienieRightAxis;
int WypelnienieLeftAxis;
void setChannelRight(bool A1,bool A2);
void setChanelB(bool B1, bool B2);
void runMotorChannelRight();//POWINNO ZNIKNAC
#endif
