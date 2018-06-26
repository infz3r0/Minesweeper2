#include "Timer.h"

clock_t startTime;
double timePassed;
double timeDelay;
char displayTime[30];
bool running;

void initTimer()
{
	startTime = 0;
	running = false;
}

void resetTimer()
{
	startTime = 0;
	running = false;
}

void startTimer()
{
	startTime = clock();
	running = true;
}

void stopTimer()
{
	running = false;
}

void updateTime()
{
	if (running)
	{
		timePassed = (clock() - startTime) / CLOCKS_PER_SEC;
		if (timePassed >= timeDelay)
		{
			updateText();
		}
	}
}

void drawTime(char *s, int x, int y)
{
	int len = (int)strlen(s);

	int cx = x;
	int cy = screenH - y;

	GLfloat red = 0.0f;
	GLfloat green = 0.0f;
	GLfloat blue = 0.0f;

	int padding = 0;

	glColor3f(red, green, blue);
	glRasterPos2i(cx + padding, cy + padding);
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[i]);

		if (isDevMode)
			printf("%c", s[i]);

	}

	glFlush();
}

void clearTime(int wx, int wy)
{
	int cx = wx;
	int cy = screenH - wy;

	int h = 12;
	int w = 120;

	glColor3f(0.95f, 0.95f, 0.95f);
	glBegin(GL_QUADS);

	glVertex2f(cx, cy);
	glVertex2f(cx, cy + h);
	glVertex2f(cx + w, cy + h);
	glVertex2f(cx + w, cy);

	glEnd();

	glFlush();
}

void updateText()
{
	sprintf_s(displayTime, 30, "Timer: %.0f", timePassed);
	clearTime(10, header - 20);
	drawTime(displayTime, 10, header - 20);
	//printf("\n[TIME]:%s", displayTime);
}