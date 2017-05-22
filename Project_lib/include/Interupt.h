#ifndef InterupConfiguration
#define InterupConfiguration
#include "misc.h"
#include "timer.h"
#include "stdbool.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "GPIO_Configuration.h"

void interuptConfigurations(void);
void extiConfiguration();
void uruchomPomiar();

/////////////////////////////////Zmienne Pomiarowe///////////////
int CzujnikLine4Start;
int CzujnikLine4Stop;

int CzujnikLine5Start;
int CzujnikLine5Stop;

int CzujnikLine6Start;
int CzujnikLine6Stop;
////////////////////////////////////////////////////////////////
bool leftForwardMeasureComplete;
bool centerForwardMeasureComplete;
bool rightForwardMeasureComplete;

///////////////////////////////////////////////
float odlegloscRightForward;
float odlegloscCenterForward;
float odlegloscLeftForward;
short TIMER5CNT;

#endif
