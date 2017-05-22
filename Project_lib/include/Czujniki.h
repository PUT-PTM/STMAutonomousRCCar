#ifndef _CZUJNIKI
#define _CZUJNIKI
#include"Interupt.h"
float measureDistance(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, int *start, int *stop,bool *isMeasureComplete);
#endif
