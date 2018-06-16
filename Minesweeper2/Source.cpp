﻿#include "Graphic.h"

void gameOver(bool isWin)
{
	//show board
	//???

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

//Mở ô được click và các ô liền kề
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