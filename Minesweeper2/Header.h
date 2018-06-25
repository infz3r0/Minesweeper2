#pragma once
#include "Base.h"
#include<math.h>

#define PI 3.14159265f

typedef struct BUTTON
{
	float cx_bot_left;
	float cy_bot_left;
	float cx_top_right;
	float cy_top_right;
	bool isHover;
} button;

typedef struct RGB
{
	float r;
	float g;
	float b;
} rgb;

extern button smile;

button drawButtonSmile(float cx, float cy, float r);

void buttonHover(button btn);

void buttonPressing(button btn);