﻿#include "Graphic.h"
#include "Header.h"
#include "Timer.h"

bool gameover = false;

void gameOver(bool isWin)
{
	//show board
	//???

	//message
	char s[20];
	rgb border;
	rgb fill;
	int text;
	if (isWin)
	{
		sprintf_s(s, 20, "YOU WIN");
		border = { 0, 0.85f, 0 };
		fill = { 0.85f, 1, 0.85f };
		text = 50;
	}
	else
	{
		sprintf_s(s, 20, "GAME OVER");
		border = { 1.0f, 0, 0 };
		fill = { 1, 0.55f, 0.55f };		
		text = 70;
	}
	int cy = screenH - (header + screenH / 4);
	drawBox(1, cy - 10, screenW - 1, cy + 25, border, fill);
	drawString(s, screenW / 2 - text, header + screenH / 4, GLUT_BITMAP_TIMES_ROMAN_24);
	//stop mouse event
	gameover = true;
	stopTimer();
}

void restart()
{
	initArray(array);
	resetFlag(flag);
	resetTimer();
	gameover = false;
	
	glutPostRedisplay();
}

void changeMode(MODE m)
{
	switch (m)
	{
	case BEGINNER:
		initBase(BEGINNER);		
		break;
	case INTERMEDIATE:
		initBase(INTERMEDIATE);
		break;
	case ADVANCED:
		initBase(ADVANCED);
		break;
	default:
		break;
	}
	glutReshapeWindow(screenW, screenH);
	initBtn();
	initGL();
	restart();
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
	if (!running)
	{
		startTimer();
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
		colorSquare(wx, wy, 0.96f, 0.96f, 0.96f);
		drawNumber(countMine, wx, wy);

		if (countMine == 0)
		{
			colorSquare(wx, wy, 0.85f, 0.85f, 0.85f);
		}
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

bool isHoverBtn(int wx, int wy)
{
	point w = { wx, wy };
	point c = convertCoordWindowToClip(w);

	if (isDevMode)
	{
		printf("\nmouse:%d-%d", c.x, c.y);
		printf("\nbutton:bot-%f-%f, top-%f-%f", smile.cx_bot_left, smile.cy_bot_left, smile.cx_top_right, smile.cy_top_right);;
	}
	if (c.x >= smile.cx_bot_left && c.x <= smile.cx_top_right && c.y >= smile.cy_bot_left && c.y <= smile.cy_top_right)
	{
		return true;
	}
	return false;
}

int isHoverModeBtn(int wx, int wy)
{
	point w = { wx, wy };
	point c = convertCoordWindowToClip(w);

	if (c.x >= modeBtn[0].cx_bot_left && c.x <= modeBtn[0].cx_top_right && c.y >= modeBtn[0].cy_bot_left && c.y <= modeBtn[0].cy_top_right)
	{
		return 0;
	}
	else if (c.x >= modeBtn[1].cx_bot_left && c.x <= modeBtn[1].cx_top_right && c.y >= modeBtn[1].cy_bot_left && c.y <= modeBtn[1].cy_top_right)
	{
		return 1;
	}
	else if (c.x >= modeBtn[2].cx_bot_left && c.x <= modeBtn[2].cx_top_right && c.y >= modeBtn[2].cy_bot_left && c.y <= modeBtn[2].cy_top_right)
	{
		return 2;
	}
	return -1;
}

/* Handler for window-repaint event. Call back when the window first appears and
whenever the window needs to be re-painted. */
void display() {
	glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
	
	drawBoard();
	drawSquare();
	updateMines();
	smile = drawButtonSmile(screenW / 2, screenH - 70, 25);

	drawModeBtn();

	printf("\n[DISPLAY]");
}

void mouse(int button, int state, int wx, int wy)
{
	/*
	*	has the button been pressed or released?
	*/
	if (state == GLUT_DOWN)
	{
		/*
		*	Which button was pressed?
		*/
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			if (isHoverBtn(wx, wy))
			{
				buttonPressing(smile);
				restart();
			}

			if (isHoverModeBtn(wx, wy) != -1)
			{
				switch (isHoverModeBtn(wx, wy))
				{
				case 0:
					changeMode(BEGINNER);
					break;
				case 1:
					changeMode(INTERMEDIATE);
					break;
				case 2:
					changeMode(ADVANCED);
					break;
				default:
					break;
				}
			}
			
			if (!gameover)
			{
				openSquare(wx, wy);
				checkGameOver();
			}
			
			break;
		case GLUT_MIDDLE_BUTTON:
			printf("middle ");
			break;
		case GLUT_RIGHT_BUTTON:
			if (!gameover)
			{
				toggleFlag(wx, wy);
			}
			
			break;
		}
	}
	else
	{
		/*
		*	Which button was released?
		*/
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			if (isHoverBtn(wx, wy))
			{
				buttonHover(smile);
			}
			break;
		case GLUT_MIDDLE_BUTTON:
			printf("middle ");
			break;
		case GLUT_RIGHT_BUTTON:
			printf("right ");
			break;
		}
	}
}

void motion(int x, int y)
{
	
}

void passiveMotion(int wx, int wy)
{
	if (isHoverBtn(wx, wy) && !smile.isHover)
	{
		smile.isHover = true;
		buttonHover(smile);
	}
	else if (!isHoverBtn(wx, wy) && smile.isHover)
	{
		smile.isHover = false;
		buttonHover(smile);
	}
	else
	{
		
			if (!modeBtn[0].isHover && isHoverModeBtn(wx, wy) == 0)
			{
				modeBtn[0].isHover = true;
				buttonHover(modeBtn[0], border_array[0], hover_array[0], color_array[0], s0, pad_left[0]);
			}
			else if (modeBtn[0].isHover && isHoverModeBtn(wx, wy) != 0)
			{
				modeBtn[0].isHover = false;
				buttonHover(modeBtn[0], border_array[0], fill_array[0], color_array[0], s0, pad_left[0]);
			}
			if (!modeBtn[1].isHover && isHoverModeBtn(wx, wy) == 1)
			{
				modeBtn[1].isHover = true;
				buttonHover(modeBtn[1], border_array[1], hover_array[1], color_array[1], s1, pad_left[1]);
			}
			else if (modeBtn[1].isHover && isHoverModeBtn(wx, wy) != 1)
			{
				modeBtn[1].isHover = false;
				buttonHover(modeBtn[1], border_array[1], fill_array[1], color_array[1], s1, pad_left[1]);
			}
			if (!modeBtn[2].isHover && isHoverModeBtn(wx, wy) == 2)
			{
				modeBtn[2].isHover = true;
				buttonHover(modeBtn[2], border_array[2], hover_array[2], color_array[2], s2, pad_left[2]);
			}
			else if (modeBtn[2].isHover && isHoverModeBtn(wx, wy) != 2)
			{
				modeBtn[2].isHover = false;
				buttonHover(modeBtn[2], border_array[2], fill_array[2], color_array[2], s2, pad_left[2]);
			}


	}
	
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

void Timer(int value) {
	updateTime();      // Post re-paint request to activate display()
	glutTimerFunc(1000, Timer, 0); // next Timer call milliseconds later
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	initArray(array);
	//showArray(array);

	initTimer();

	glutInit(&argc, argv);          // Initialize GLUT
	//glutInitDisplayMode(GLUT_DOUBLE);  // Enable double buffered mode
	glutInitWindowSize(screenW, screenH);   // Set the window's initial width & height - non-square
	glutInitWindowPosition(500, 50); // Position the window's initial top-left corner
	glutCreateWindow("Minesweeper 2018");  // Create window with the given title

	glutDisplayFunc(display);       // Register callback handler for window re-paint event
	glutReshapeFunc(reshape);       // Register callback handler for window re-size event
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passiveMotion);
	glutTimerFunc(0, Timer, 0);

	initGL();
	glutMainLoop();           // Enter the event-processing loop

	return 0;
}