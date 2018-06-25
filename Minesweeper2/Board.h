#pragma once

#include "Base.h"

extern int array[40][40];
extern int flag[40][40];

/*
Giá trị mảng array
-1:mines;
0:close;
1:open;
*/

// Khởi tạo mảng, bom ngẫu nhiên
void initArray(int a[][40]);

void resetFlag(int flag[][40]);

// Hiện mảng trên console
void showArray(int a[][40]);

// Đếm số bom xung quanh ô
int countMines(int a[][40], int x, int y);

// Kiểm tra ô có bom không
bool isMine(int a[][40], int wx, int wy);

// Kiểm tra ô đã được mở chưa
bool isOpened(int a[][40], int wx, int wy);

// Kiểm tra tọa độ click trong phạm vi board không
bool isValidClick(int wx, int wy);