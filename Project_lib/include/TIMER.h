#ifndef TIMER
#define TIMER
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"

/*
 * TIMER 2 - Op�ninia
 * TIMER 3 - TriggerCzujnik�w
 * TIMER 4 - PWM_SILNIK�W
 * TIMER 5 - Czestotliwosc Pomiarow
 * TIMER 7 - WARTOSC POMIARU
 */
#define PERIOD  ((int) 999)
#define _TAKTOWANIEZEGARA ((int)84000000)
#define czstotliwoscLicznikaPomiarowego ((int)170)
unsigned int czestotliwoscTimeraPomiarowego;

unsigned long long timeDelay;
void uDelay(unsigned int delay);
void mDelay(unsigned int delay);
void timerConfiguration();
#endif
