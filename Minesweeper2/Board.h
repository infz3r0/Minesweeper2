#pragma once

#include "Base.h"

extern int array[row][col];
extern int flag[row][col];

/*
Giá trị mảng array
-1:mines;
0:close;
1:open;
*/

// Khởi tạo mảng, bom ngẫu nhiên
void initArray(int a[][col]);

// Hiện mảng trên console
void showArray(int a[][col]);

// Đếm số bom xung quanh ô
int countMines(int a[][col], int x, int y);

// Kiểm tra ô có bom không
bool isMine(int a[][col], int wx, int wy);

// Kiểm tra ô đã được mở chưa
bool isOpened(int a[][col], int wx, int wy);

// Kiểm tra tọa độ click trong phạm vi board không
bool isValidClick(int wx, int wy);