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

extern button modeBtn[3];

extern rgb border_array[3];
extern rgb fill_array[3];
extern rgb hover_array[3];
extern rgb color_array[3];
extern int pad_left[3];

extern const char s0[18];
extern const char s1[18];
extern const char s2[18];

button drawButtonSmile(float cx, float cy, float r);

void buttonHover(button btn);

void buttonHover(button btn, rgb border, rgb fill, rgb text, const char *s, int pad_left);

void buttonPressing(button btn);

void drawModeBtn();

void drawString(const char *s, int x, int y, rgb color, int padding_left);