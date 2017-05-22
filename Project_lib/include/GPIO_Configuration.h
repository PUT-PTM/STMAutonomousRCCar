#ifndef GPIO
#define GPIO
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
void GPIOConfiguration();
//Potrzebne do sterowania pinem wyjsciowym
int ADC_Result;
#define DOPUSZCZALNY_PROGR_OZLADOWANIA ((int)2000)
#define PROGAKCPETOWALNY ((int)2050)

#endif
