#include<stdlib.h>
#include<GL/glew.h>
#include<GL/glut.h>
#include<stdio.h>
#include<time.h>
#include<string.h>

/*
	Thiết kế lại Flag và các vấn đề liên quan

*/
bool isDevMode = false;

const int col = 9;
const int row = 9;
int mines = 10;

int squareLength = 20;
int border = squareLength / 2;

int screenW = (col + 1) * squareLength;
int screenH = (row + 1) * squareLength + 100;

GLdouble left = 0;
GLdouble right = screenW;
GLdouble bottom = 0;
GLdouble top = screenH;

typedef struct POINT {
	int x;
	int y;
} point;

int maxX = screenW;
int maxY = screenH - 100;

int array[row][col];
int flag[row][col];

int randomNumber(int a, int b)
{	
	int x = rand() % (b - a + 1) + a;
	return x;
}

void initGL() {
	// Set "clearing" or background color
	glClearColor(0.95f, 0.95f, 0.95f, 1.0f); // Black and opaque
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

/*
	-1:mines;
	0:close;
	1:open;
*/
void initArray(int a[][col])
{	
	srand(time(NULL));
	int i, j;
	int c = 0;
	int l = 0;

	while (c < mines)
	{
		l++;

		i = randomNumber(0, row - 1);
		j = randomNumber(0, col - 1);

		if (isDevMode)
		printf("loop:%d, i:%d-j:%d-v:%d-c:%d\n", l, i, j, a[i][j], c);
		
		if (a[i][j] != -1)
		{
			a[i][j] = -1;
			c++;
		}

		if (isDevMode)
		printf("i:%d-j:%d-v:%d-c:%d\n", i, j, a[i][j], c);
	}

}

void showArray(int a[][col])
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			printf("%3d", a[i][j]);
		}
		printf("\n");
	}
}

int countMines(int a[][col], int x, int y)
{
	//calculate i, j from x, y
	x -= squareLength / 2;
	int ix = x / squareLength;

	y = screenH - y - squareLength / 2;
	int iy = y / squareLength;
	iy = row - 1 - iy;

	int i = iy;
	int j = ix;

	//count 
	int count = 0;
	int pos[8][2] = { {i - 1, j - 1}, {i - 1, j}, {i - 1, j + 1}
					, {i, j - 1}				, {i, j + 1}
					, {i + 1, j - 1}, {i + 1, j}, {i + 1, j + 1} };

	int r, c;
	for (r = 0; r < 8; r++)
	{
		//if pos out of board
		if (pos[r][0] < 0 || pos[r][1] < 0 || pos[r][0] > row - 1 || pos[r][1] > col - 1)
		{

		}
		else
		{
			if (a[pos[r][0]][pos[r][1]] == -1)
			{
				count++;
			}
		}
	}

	return count;
}

bool isMine(int a[][col], int wx, int wy)
{
	//calculate i, j from x, y
	point w = { wx, wy };
	point c = convertCoordWindowToClip(w);
	point index = clipToIndex(c);

	int i = index.x;
	int j = index.y;

	//check
	if (a[i][j] == -1)
	{
		return true;
	}
	return false;
}

bool isOpened(int a[][col], int wx, int wy)
{
	//calculate i, j from x, y
	point w = { wx, wy };
	point c = convertCoordWindowToClip(w);
	point index = clipToIndex(c);

	int i = index.x;
	int j = index.y;

	//check
	if (a[i][j] == 1)
	{
		return true;
	}
	return false;
}

bool isValidClick(int wx, int wy)
{
	wx -= squareLength / 2;
	int ix = wx / squareLength;

	wy = screenH - wy - squareLength / 2;
	int iy = wy / squareLength;

	if (wx >= 0 && wy >= 0 && wx % 20 != 0 && wy % 20 != 0 && 0 <= ix && ix < col && 0 <= iy && iy < row)
	{
		return true;
	}
	return false;
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

void gameOver(bool isWin)
{
	//show board
	//message
	char s[20];
	if (isWin)
	{
		sprintf_s(s, 20, "YOU WIN");
	}
	else
	{
		sprintf_s(s, 20, "GAME OVER");
	}
	
	drawString(s, 10, 50);
	//stop mouse event
	glutMouseFunc(NULL);
}

void checkGameOver()
{
	int empty = row * col - mines;
	int opened = 0;
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (array[i][j] == 1)
			{
				opened++;
			}
		}
	}

	if (opened == empty)
	{
		gameOver(true);
	}
}

void openSquare(int wx, int wy)
{
	if (!isValidClick(wx, wy))
	{
		return;
	}
	/*point wtest = { wx, wy };
	point ctest = convertCoordWindowToClip(wtest);
	point indextest = clipToIndex(ctest);

	if (isDevMode)
	printf("\n>>>r[open]i:%d-j%d", indextest.x, indextest.y);*/
	//calculate i, j from x, y
	point w = { wx, wy };
	point c = convertCoordWindowToClip(w);
	point index = clipToIndex(c);

	int i = index.x;
	int j = index.y;

	if (isOpened(array, wx, wy))
	{
		return;
	}

	if (isMine(array, wx, wy))
	{
		colorSquare(wx, wy, 1.0f, 0.0f, 0.0f);
		gameOver(false);
		return;
	}
	else
	{
		int countMine = countMines(array, wx, wy);
		if (flag[i][j] == 1)
		{
			colorSquare(wx, wy, 1.0f, 1.0f, 1.0f);
		}
		drawNumber(countMine, wx, wy);

		array[i][j] = 1;

		if (countMine == 0)
		{		
			int pos[8][2] = { { i - 1, j - 1 },{ i - 1, j },{ i - 1, j + 1 }
				,{ i, j - 1 }				,{ i, j + 1 }
			,{ i + 1, j - 1 },{ i + 1, j },{ i + 1, j + 1 } };

			int r;
			for (r = 0; r < 8; r++)
			{
				//if pos out of board
				if (pos[r][0] < 0 || pos[r][1] < 0 || pos[r][0] > row - 1 || pos[r][1] > col - 1)
				{

				}
				else
				{
					point indexOpen = { pos[r][0], pos[r][1] };
					point cOpen = indexToClip(indexOpen);
					point wOpen = convertCoordClipToWindow(cOpen);

					int xOpen = wOpen.x;
					int yOpen = wOpen.y;
					openSquare(xOpen, yOpen);
				}
			}
		}
		else
		{
			return;
		}
	}
}

/* Handler for window-repaint event. Call back when the window first appears and
whenever the window needs to be re-painted. */
void display() {
	glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
	
	drawBoard();
	drawSquare();
	updateMines();

	printf("\n[DISPLAY]");
}

void mouse(int button, int state, int wx, int wy)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {		
		openSquare(wx, wy);
		checkGameOver();
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		toggleFlag(wx, wy);
	}
}

void motion(int x, int y)
{
	
}

/* Handler for window re-size event. Called back when the window first appears and
whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
											   // Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping area to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset the projection matrix

	gluOrtho2D(left, right, bottom, top);

	//if (width >= height) {
	//	// aspect >= 1, set the height from -1 to 1, with larger width
	//	gluOrtho2D(left * aspect, right * aspect, bottom, top);
	//}
	//else {
	//	// aspect < 1, set the width to -1 to 1, with larger height
	//	gluOrtho2D(left, right, bottom / aspect, top / aspect);
	//}

	//prevent change window size
	glutReshapeWindow(screenW, screenH);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	initArray(array);
	//showArray(array);

	glutInit(&argc, argv);          // Initialize GLUT
	//glutInitDisplayMode(GLUT_DOUBLE);  // Enable double buffered mode
	glutInitWindowSize(screenW, screenH);   // Set the window's initial width & height - non-square
	glutInitWindowPosition(800, 50); // Position the window's initial top-left corner
	glutCreateWindow("Testing");  // Create window with the given title

	glutDisplayFunc(display);       // Register callback handler for window re-paint event
	glutReshapeFunc(reshape);       // Register callback handler for window re-size event
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	initGL();
	glutMainLoop();           // Enter the event-processing loop

	return 0;
}