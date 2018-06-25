#include "Graphic.h"

int maxX = screenW;
int maxY = screenH - 100;

void initGL() {
	// Set "clearing" or background color
	glClearColor(0.95f, 0.95f, 0.95f, 1.0f); // Black and opaque
}

void drawBoard()
{
	//draw col
	int x1 = 0;
	int y1 = border;
	int x2 = x1;
	int y2 = maxY - border;

	for (x1 = border; x1 <= maxX; x1 += squareLength)
	{
		x2 = x1;

		glBegin(GL_LINES);

		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);

		glEnd();

		glFlush();


	}

	//draw row
	x1 = border;
	x2 = maxX - border;

	for (y1 = border; y1 <= maxY; y1 += squareLength)
	{
		y2 = y1;

		glBegin(GL_LINES);

		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);

		glEnd();

		glFlush();


	}
}

void drawSquare()
{
	int i = 0;
	int j = 0;

	int x = 0;
	int y = 0;

	for (int i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			x = border + i * squareLength;
			y = border + j * squareLength + 1;

			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_QUADS);

			glVertex2f(x, y);
			glVertex2f(x + squareLength - 1, y);
			glVertex2f(x + squareLength - 1, y + squareLength - 1);
			glVertex2f(x, y + squareLength - 1);

			glEnd();

			glFlush();
		}
	}
}

void colorSquare(int x, int y, GLfloat red, GLfloat green, GLfloat blue)
{
	x -= squareLength / 2;
	int ix = x / squareLength;

	y = screenH - y - squareLength / 2;
	int iy = y / squareLength;

	if (isDevMode)
		printf("\n%d-%d | %d-%d", x, y, ix, iy);

	// if x >= 0 && y >= 0
	// if x % 20 != 0 && y % 20 != 0
	// if 0 <= ix <= 14 && 0 <= iy <= 14
	if (x >= 0 && y >= 0 && x % squareLength != 0 && y % squareLength != 0 && 0 <= ix && ix < col && 0 <= iy && iy < row)
	{
		if (isDevMode)
			printf("\tTRUE");

		x = border + ix * squareLength;
		y = border + iy * squareLength + 1;

		glColor3f(red, green, blue);
		glBegin(GL_QUADS);

		glVertex2f(x, y);
		glVertex2f(x + squareLength - 1, y);
		glVertex2f(x + squareLength - 1, y + squareLength - 1);
		glVertex2f(x, y + squareLength - 1);

		glEnd();

		glFlush();
	}
}

void drawNumber(int num, int x, int y)
{
	x -= squareLength / 2;
	int ix = x / squareLength;

	y = screenH - y - squareLength / 2;
	int iy = y / squareLength;

	if (isDevMode)
		printf("\n%d-%d | %d-%d", x, y, ix, iy);

	GLfloat red = 0.0f;
	GLfloat green = 0.0f;
	GLfloat blue = 0.0f;

	int padding = 5;

	// if x >= 0 && y >= 0
	// if x % 20 != 0 && y % 20 != 0
	// if 0 <= ix <= 14 && 0 <= iy <= 14
	if (x >= 0 && y >= 0 && x % 20 != 0 && y % 20 != 0 && 0 <= ix && ix < col && 0 <= iy && iy < row)
	{
		if (isDevMode)
			printf("\tTRUE");

		x = 10 + ix * 20;
		y = 10 + iy * 20 + 1;

		glColor3f(red, green, blue);
		glRasterPos2i(x + padding, y + padding);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0' + num);

		glFlush();
	}
}

void drawString(char *s, int x, int y)
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

void clearString(int wx, int wy)
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

void updateMines()
{
	int count = 0;
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (flag[i][j] == 1)
			{
				count++;
			}
		}
	}

	int minesLeft = mines - count;

	int buf;
	char s[18];
	buf = sprintf_s(s, 18, "Mines left: %d", minesLeft);

	clearString(10, 102);
	drawString(s, 10, 100);
}

void drawFlag(int x, int y)
{
	x -= squareLength / 2;
	int ix = x / squareLength;

	y = screenH - y - squareLength / 2;
	int iy = y / squareLength;

	if (isDevMode)
		printf("\n%d-%d | %d-%d", x, y, ix, iy);

	GLfloat red = 0.0f;
	GLfloat green = 0.0f;
	GLfloat blue = 0.0f;

	int padding = 5;

	// if x >= 0 && y >= 0
	// if x % 20 != 0 && y % 20 != 0
	// if 0 <= ix <= 14 && 0 <= iy <= 14
	if (x >= 0 && y >= 0 && x % 20 != 0 && y % 20 != 0 && 0 <= ix && ix < col && 0 <= iy && iy < row)
	{

		if (isDevMode)
			printf("\tTRUE");

		x = border + ix * squareLength;
		y = border + iy * squareLength + 1;

		glColor3f(red, green, blue);

		glBegin(GL_LINES);

		glVertex2f(x + 14, y + 3);
		glVertex2f(x + 14, y + 17);

		glEnd();

		red = 1.0f;
		glColor3f(red, green, blue);

		glBegin(GL_TRIANGLES);

		glVertex2f(x + 13, y + 17);
		glVertex2f(x + 13, y + 9);
		glVertex2f(x + 5, y + 12);

		glEnd();

		glFlush();
	}
}

void toggleFlag(int wx, int wy)
{
	if (!isValidClick(wx, wy))
	{
		return;
	}

	point w = { wx, wy };	
	point c = convertCoordWindowToClip(w);
	point index = clipToIndex(c);

	if (!isOpened(array, wx, wy))
	{
		if (flag[index.x][index.y] == 1)
		{
			flag[index.x][index.y] = 0;
			colorSquare(wx, wy, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			flag[index.x][index.y] = 1;
			drawFlag(wx, wy);
		}

		updateMines();
	}
}
