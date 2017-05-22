#ifndef _CZUJNIKI
#define _CZUJNIKI
#include"Interupt.h"
void measureDistance(float *Distance,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, int *start, int *stop,bool *isMeasureComplete);
#endif
