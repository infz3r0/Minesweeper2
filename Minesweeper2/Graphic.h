#pragma once


#include "Board.h"

extern int maxX;
extern int maxY;

// Khởi tạo màu nền
void initGL();

// Vẽ đường ngang, dọc
void drawBoard();

// Vẽ các ô
void drawSquare();

// Tô màu ô
void colorSquare(int x, int y, GLfloat red, GLfloat green, GLfloat blue);

// Vẽ số
void drawNumber(int num, int x, int y);

// Vẽ chuỗi
void drawString(char *s, int x, int y);

// Xóa chuỗi
void clearString(int wx, int wy);

// Hiện số bom còn lại
void updateMines();

// Vẽ cờ
void drawFlag(int x, int y);

// Ẩn/Hiện cờ
void toggleFlag(int wx, int wy);