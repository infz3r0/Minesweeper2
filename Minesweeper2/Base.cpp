
#include "Base.h"

bool isDevMode = false;

int mines = 10;

int squareLength = 20;
int border = squareLength / 2;

int screenW = (col + 1) * squareLength;
int screenH = (row + 1) * squareLength + 100;

GLdouble left = 0;
GLdouble right = screenW;
GLdouble bottom = 0;
GLdouble top = screenH;

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