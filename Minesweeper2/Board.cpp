#include "Board.h"

int array[40][40];
int flag[40][40];

void initArray(int a[][40])
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			a[i][j] = 0;
		}
	}

	srand(time(NULL));
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

void showArray(int a[][40])
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

int countMines(int a[][40], int x, int y)
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
	int pos[8][2] = { { i - 1, j - 1 },{ i - 1, j },{ i - 1, j + 1 }
		,{ i, j - 1 }				,{ i, j + 1 }
	,{ i + 1, j - 1 },{ i + 1, j },{ i + 1, j + 1 } };

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

bool isMine(int a[][40], int wx, int wy)
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

bool isOpened(int a[][40], int wx, int wy)
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

void resetFlag(int flag[][40])
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			flag[i][j] = 0;
		}
	}
}