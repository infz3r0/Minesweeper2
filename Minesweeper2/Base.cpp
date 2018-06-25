
#include "Base.h"

bool isDevMode = false;

//default mode
int col = mode[BEGINNER].col;
int row = mode[BEGINNER].row;
int mines = mode[BEGINNER].mines;

int squareLength = 20;
int border = squareLength / 2;

int screenW = (col + 1) * squareLength;
int screenH = (row + 1) * squareLength + header;

GLdouble left = 0;
GLdouble right = screenW;
GLdouble bottom = 0;
GLdouble top = screenH;

void initBase(MODE m)
{
	col = mode[m].col;
	row = mode[m].row;
	mines = mode[m].mines;

	screenW = (col + 1) * squareLength;
	screenH = (row + 1) * squareLength + header;

	left = 0;
	right = screenW;
	bottom = 0;
	top = screenH;
}

int randomNumber(int a, int b)
{
	int x = rand() % (b - a + 1) + a;
	return x;
}

point convertCoordWindowToClip(point window)
{
	if (isDevMode)
	{
		printf("\nwindow: x:%d; y:%d", window.x, window.y);
	}

	point clip = { window.x, screenH - window.y };

	if (isDevMode)
	{
		printf("\nclip: x:%d; y:%d", clip.x, clip.y);
	}

	return clip;
}

point convertCoordClipToWindow(point clip)
{
	if (isDevMode)
		printf("\nclip: x:%d; y:%d", clip.x, clip.y);

	point window = { clip.x, screenH - clip.y };

	if (isDevMode)
		printf("\nwindow: x:%d; y:%d", window.x, window.y);

	return window;
}

point clipToIndex(point clip) {
	int j = (clip.x - squareLength / 2) / squareLength;
	int i = row - 1 - (clip.y - squareLength / 2) / squareLength;

	if (isDevMode)
		printf("\ni:%d-j:%d", i, j);

	point index = { i, j };
	return index;
}

point indexToClip(point index)
{
	int x = squareLength / 2 + (index.y) * squareLength + 2;
	int y = squareLength / 2 + (row - 1 - index.x) * squareLength + 2;

	point clip = { x + 2, y + 2 };

	if (isDevMode)
		printf("\nclip: x:%d; y:%d", clip.x, clip.y);

	return clip;
}