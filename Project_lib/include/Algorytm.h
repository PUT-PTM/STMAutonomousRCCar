#ifndef Algorytm
#define Algorytm
#include "timer.h"
#include "stdbool.h"
#include "czujniki.h"

bool colisionForwardDetect;
//int direction;//Zbedne

#define zmiennaDoAlgorytmu3 ((float)0.7)// czesc g³owna
#define zmiennaDoAlgorytmu2 ((float)0.12)// czesc g³owna
#define zmiennaDoAlgorytmu ((float)0.30)//Czesc zapasowa
float missColissionForLeftWheel();
float missColissionForRightWheel();

#endif
