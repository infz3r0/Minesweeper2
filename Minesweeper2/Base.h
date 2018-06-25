#pragma once

#include<stdlib.h>
#include<GL/glew.h>
#include<GL/glut.h>
#include<stdio.h>
#include<time.h>

extern bool isDevMode;

/*
GAME MODE:
BEGINER 9x9 10
INTERMEDIATE 16x16 40
ADVANCED 16rx30c 99
*/
/*
Số dòng, cột
Số lượng bom
*/
const int col = 30;
const int row = 16;
const int header = 150;
extern int mines;

// Kích thước ô
extern int squareLength;
extern int border;

// Kích thước màn hình
extern int screenW;
extern int screenH;

// Hệ tọa độ OpenGL
extern GLdouble left;
extern GLdouble right;
extern GLdouble bottom;
extern GLdouble top;

typedef struct POINT {
	int x;
	int y;
} point;

// Tọa độ window -> openGL
point convertCoordWindowToClip(point window);

// // Tọa độ openGL -> window
point convertCoordClipToWindow(point clip);

// Tọa độ openGL -> chỉ số mảng
point clipToIndex(point clip);

// Chỉ số mảng -> Tọa độ openGL 
point indexToClip(point index);

// Tạo số ngẫu nhiên trong đoạn [a, b]
int randomNumber(int a, int b);