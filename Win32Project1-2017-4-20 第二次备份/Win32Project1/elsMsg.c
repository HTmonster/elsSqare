#include "elsHead.h"

int bg_array[20][10] = { 0 };

void onPaint(HDC hDC) {
	//创建兼容性DC
	HDC hMemDc = CreateCompatibleDC(hDC); 
	//创建位图
	HBITMAP hBitMap = CreateCompatibleBitmap(hDC, 400, 600);
	//关联DC和位图
	SelectObject(hMemDc,hBitMap);
	
    paintSqare(hMemDc);

	

	//传递
	BitBlt(hDC, 0, 0, 300, 600, hMemDc, 0, 0, SRCCOPY);


	//释放
	DeleteObject(hMemDc);
	DeleteDC(hDC);
}

void paintSqare(HDC hMemDc) {
	int i, j;
	Rectangle(hMemDc, 0, 0, 300, 600);

	bg_array[2][1] = 1;
	bg_array[2][2] = 1;
	bg_array[2][3] = 1;
	bg_array[1][2] = 1;

	for (i = 0; i <20; i++) {
		for (j = 0; j < 10; j++) {
			if (1==bg_array[i][j]) {
               Rectangle(hMemDc, 30*j,30*i, 30 * j+30, 30 * i+30);
			}
		}
	}

}

void onCreat() {


}