#include "elsHead.h"

char bg_array[BG_Y][BG_X] = { 0 };//背景数据数组
char st_array[2][4] = { 0 };//方块数组


void onPaint(HDC hDC) {
	//创建兼容性DC
	HDC hMemDc = CreateCompatibleDC(hDC); 
	//创建位图
	HBITMAP hBitMap = CreateCompatibleBitmap(hDC, WIND_W,WIND_H);
	//关联DC和位图
	SelectObject(hMemDc,hBitMap);
	
    paintSqare(hMemDc);   //DC画图
	printSqare2(hMemDc);

	//传递
	BitBlt(hDC, 0, 0, BG_W, BG_H, hMemDc, 0, 0, SRCCOPY);


	//释放
	DeleteObject(hMemDc);
	DeleteDC(hDC);
}

void paintSqare(HDC hMemDc) {
	int i, j;
	Rectangle(hMemDc, 0, 0, BG_W, BG_H);

	for (i = 0; i <BG_Y; i++) {
		for (j = 0; j <BG_X; j++) {
			if (1==bg_array[i][j]) {
               Rectangle(hMemDc, SQARE_SIZE*j, SQARE_SIZE*i, SQARE_SIZE * (j+1), SQARE_SIZE * (i+1));
			}
		}
	}

}
//长生初始的方块 
void creatRandSqare() {
	short n;
	n = rand()%7;

	//初始方块库
	switch (n) {
	case(0):
		st_array[0][0] = 1, st_array[0][1] = 1, st_array[0][2] = 0, st_array[0][3] = 0;//1 1 0 0
		st_array[1][0] = 0, st_array[1][1] = 1, st_array[1][2] = 1, st_array[1][3] = 0;//0 1 1 0
		break;
	case(1):
		st_array[0][0] = 0, st_array[0][1] = 0, st_array[0][2] = 1, st_array[0][3] = 1;//0 0 1 1
		st_array[1][0] = 0, st_array[1][1] = 1, st_array[1][2] = 1, st_array[1][3] = 0;//0 1 1 0
		break;
	case(2):
		st_array[0][0] = 0, st_array[0][1] = 1, st_array[0][2] = 1, st_array[0][3] = 0;//0 1 1 0
		st_array[1][0] = 0, st_array[1][1] = 1, st_array[1][2] = 1, st_array[1][3] = 0;//0 1 1 0
		break;
	case(3):
		st_array[0][0] = 0, st_array[0][1] = 1, st_array[0][2] = 0, st_array[0][3] = 0;//0 1 0 0
		st_array[1][0] = 1, st_array[1][1] = 1, st_array[1][2] = 1, st_array[1][3] = 0;//1 1 1 0
		break;
	case(4):
		st_array[0][0] = 1, st_array[0][1] = 1, st_array[0][2] = 1, st_array[0][3] = 1;//1 1 1 1
		st_array[1][0] = 0, st_array[1][1] = 0, st_array[1][2] = 0, st_array[1][3] = 0;//0 0 0 0
		break;
	case(5):
		st_array[0][0] = 1, st_array[0][1] = 0, st_array[0][2] = 0, st_array[0][3] = 0;//1 0 0 0
		st_array[1][0] = 1, st_array[1][1] = 1, st_array[1][2] = 1, st_array[1][3] = 1;//1 1 1 1
		break;
	case(6):
		st_array[0][0] = 0, st_array[0][1] = 0, st_array[0][2] = 0, st_array[0][3] = 1;//0 0 0 1
		st_array[1][0] = 1, st_array[1][1] = 1, st_array[1][2] = 1, st_array[1][3] = 1;//1 1 1 1
		break;
	}
}

//把方块库随机产生的方块移到背景
void moveStarToBg() {
	short i = 0,
		  j = 0;

	for (i = 0; i < 2; i++) {
		for (j = 0; j < 4; j++) {
			bg_array[i][j + INTERVAL_L] = st_array[i][j];
		}
	}
}

//窗口产生
void onCreat() {
	srand((unsigned int)time(NULL));//设置随机数的种子
	creatRandSqare();  //产生随机方块
	moveStarToBg();    //关联
}

//回车按下的响应
void onReturn(HWND hWnd) {
	SetTimer(hWnd, ID_TIMER1, 1000, NULL);//设置定时器（后面的参数设置为NULL会产生一个WM_TIMER消息）
}

//方块下落
void sqareDown() {
	short i = 0,
		j = 0;

	for (i =BG_Y-1; i >=0; i--) {
		for (j = BG_X-1; j>=0; j--) {
			if (1 == bg_array[i][j]) {
				bg_array[i][j]=0;
			    bg_array[i + 1][j]=1;//方块下落
			}
		}
	}
}

//方块不在下落的条件
short CanDownSqare() {
	int m;
	char flag = 0;

	for (m = 0; m < BG_X; m++) {
		if (1 == bg_array[BG_Y - 1][m]) {
            return 1;
		}
	}
    
	return 0;
}

void  change1To2(){
	int i, j;

	for (i = 0; i < BG_Y; i++) {
		for (j = 0; j< BG_X; j++) {
			if (1 == bg_array[i][j]) {
				bg_array[i][j] = 2;
			}
		}
	}
}

//显示底部
void  printSqare2(HDC hMemDc) {
	int i, j;

	for (i = 0; i <BG_Y; i++) {
		for (j = 0; j <BG_X; j++) {
			if (2 == bg_array[i][j]) {
				Rectangle(hMemDc, SQARE_SIZE*j, SQARE_SIZE*i, SQARE_SIZE * (j + 1), SQARE_SIZE * (i + 1));
			}
		}
	}


}

//Timer消息响应
void onTimer(HWND hWnd) {
	HDC hDc = GetDC(hWnd);

	if (0 == CanDownSqare()){
          sqareDown();   //方块下落
	}
	else {
		change1To2();
		creatRandSqare();
		moveStarToBg();
	}
	
	onPaint(hDc);   //打印

	ReleaseDC(hWnd,hDc);  //释放
}