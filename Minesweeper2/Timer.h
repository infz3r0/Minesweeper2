#pragma once
#include "Base.h"

extern clock_t startTime;
extern double timePassed;
extern double timeDelay;
extern char displayTime[30];
extern bool running;

void initTimer();

void resetTimer();

void startTimer();

void stopTimer();

void updateTime();

void updateText();