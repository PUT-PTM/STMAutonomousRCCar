#ifndef _CZUJNIKI
#define _CZUJNIKI
#include"Interupt.h"
void obstacleNoDetected(float *Distance,unsigned short *tryNumber);
void measureDistance(float *Distance,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, int *start, int *stop,bool *isMeasureComplete,unsigned short *tryNumber);
#endif
