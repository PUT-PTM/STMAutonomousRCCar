#ifndef Algorytm
#define Algorytm
#include "timer.h"
#include "stdbool.h"
#include "czujniki.h"
//#include "math.h"//pow nie dzia³alo
#define zmiennaDoAlgorytmu2 ((float)0.12)// czesc g³owna
#define zmiennaDoAlgorytmu ((float)0.30)//Czesc zapasowa
float missColissionForLeftWheel();
float missColissionForRightWheel();
int leftSensor();
int centerSensor();
int leftSensor();
#endif
