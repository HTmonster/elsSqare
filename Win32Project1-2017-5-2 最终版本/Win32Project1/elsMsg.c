#include "elsHead.h"

char bg_array[BG_Y][BG_X] = { 0 };//背景数据数组
char st_array[2][4] = { 0 };//方块数组
short g_sqareId = -1;//方块id
short g_markL = -1; //方块标记行 i
short g_markR = -1; //方块标记列 j
int   g_score = 0;   //分数

//窗口产生响应
void onCreat() {
	srand((unsigned int)time(NULL));//设置随机数的种子
	creatRandSqare();  //产生第一个随机方块
	moveStarToBg();    //关联
}

//画窗口时候的响应
void onPaint(HDC hDC) {

	char scoreStr[10] = { 0 };//分数字符

	itoa(g_score, scoreStr, 10);
	//创建兼容性DC
	HDC hMemDc = CreateCompatibleDC(hDC); 
	//创建位图
	HBITMAP hBitMap = CreateCompatibleBitmap(hDC, WIND_W,WIND_H);
	//关联DC和位图
	SelectObject(hMemDc,hBitMap);
	
    paintSqare(hMemDc);   //DC画图
	printSqare2(hMemDc);  //底部的

	//传递
	BitBlt(hDC, 0, 0, BG_W, BG_H, hMemDc, 0, 0, SRCCOPY);

	//侧边文字

	TextOut(hDC, BG_W , 20, "您的分数是：", 12);
	TextOut(hDC, BG_W+10, 50, scoreStr, strlen(scoreStr));
	TextOut(hDC, BG_W, 320, "回车：开始：", 10);
	TextOut(hDC, BG_W, 340, "上键：变形：", 10);
	TextOut(hDC, BG_W, 360, "下键：加速：", 10);
	TextOut(hDC, BG_W, 380, "左键：左移：", 10);
	TextOut(hDC, BG_W, 400, "右键：右移：", 10);
	TextOut(hDC, BG_W, 580, "作者:Theohui", 12);
	//释放
	DeleteObject(hMemDc);
	DeleteDC(hDC);
}

//回车按下的响应
void onReturn(HWND hWnd) {
	SetTimer(hWnd, ID_TIMER1, 1000, NULL);//设置定时器（后面的参数设置为NULL会产生一个WM_TIMER消息）
}


//右移
void onRight(HWND hWnd) {

	HDC hDc = GetDC(hWnd);

	short i = 0,
	      j = BG_X - 1;

	if (1==canSqareRight() ){
		for (i = 0; i < BG_Y; i++) {
			for (j = BG_X - 1; j >= 0; j--) {
				if (1 == bg_array[i][j]) {
					bg_array[i][j + 1] = 1;
					bg_array[i][j] = 0;//右移
				}
			}
		}
		g_markR++;
	}
	onPaint(hDc);   //打印

	ReleaseDC(hWnd, hDc);  //释放
}
//左移
void onLeft(HWND hWnd) {
    HDC hDc = GetDC(hWnd);
	
	short i = 0,
		  j = 0;

	if (1==canSqareLeft()) {
		for (i = 0; i < BG_Y; i++) {
			for (j =0; j <BG_X; j++) {
				if (1 == bg_array[i][j]) {
					bg_array[i][j - 1] = 1;
					bg_array[i][j] = 0;//左移
				}
			}
		}
		g_markR--;
	}
	onPaint(hDc);   //打印

	ReleaseDC(hWnd, hDc);  //释放
}
//加速
void onDown(HWND hWnd) {
	onTimer(hWnd);
}

//变形
void onUp(HWND hWnd) {
	HDC hDc = GetDC(hWnd);
    
	switch (g_sqareId)
	{
	case 1:
		if (1 == canSqareChange1()) {
			changeSqare1();       //普通方块
		}
		break;
	case 2:
		if (1 == canSqareChange2()) {
			changeSqare2();    //长条方块
		} 
		break;
	case 3:
		return;
		break;
	default:
		return;
		break;
	}


	onPaint(hDc);   //打印
	ReleaseDC(hWnd, hDc);  //释放
}

//Timer消息响应
void onTimer(HWND hWnd) {
	HDC hDc = GetDC(hWnd);

	if (0 == CanDownSqare() && 0 == CanDownSqare2()) {
		sqareDown();   //方块下落
	}
	else {
		change1To2();     //下落后停稳的改变到2
		if (1 == ifStopGame())//如果结束游戏
		{
			MessageBox(NULL, "游戏结束", "提示", MB_OK);//提示框
			KillTimer(hWnd, ID_TIMER1);//关闭定时器
			return 0;//结束
		}    
		disappearSqare(); //消除方块
		creatRandSqare(); //产生新的方块
		moveStarToBg();   //把新方块移到背景中
	}

	onPaint(hDc);   //打印

	ReleaseDC(hWnd, hDc);  //释放
}

//画方块（1）
void paintSqare(HDC hMemDc) {
	int i, j;
	HBRUSH hNewBrush, hOldBrush;//画刷

	Rectangle(hMemDc, 0, 0, BG_W, BG_H);//大矩形

	hNewBrush = CreateSolidBrush(RGB(150, 255, 150));//上颜色
	hOldBrush = SelectObject(hMemDc, hNewBrush);

	for (i = 0; i <BG_Y; i++) {     //画1
		for (j = 0; j <BG_X; j++) {
			if (1==bg_array[i][j]) {
               Rectangle(hMemDc, SQARE_SIZE*j, SQARE_SIZE*i, SQARE_SIZE * (j+1), SQARE_SIZE * (i+1));
			}
		}
	}

	hOldBrush = SelectObject(hMemDc, hOldBrush);
	DeleteObject(hOldBrush);

}

//显示底部（画2）
void  printSqare2(HDC hMemDc) {
	int i, j;
	HBRUSH hNewBrush, hOldBrush;//画刷

	hNewBrush = CreateSolidBrush(RGB(255, 0, 0));//上颜色
	hOldBrush = SelectObject(hMemDc, hNewBrush);

	for (i = 0; i <BG_Y; i++) {
		for (j = 0; j <BG_X; j++) {
			if (2 == bg_array[i][j]) {
				Rectangle(hMemDc, SQARE_SIZE*j, SQARE_SIZE*i, SQARE_SIZE * (j + 1), SQARE_SIZE * (i + 1));
			}
		}
	}
	hOldBrush = SelectObject(hMemDc, hOldBrush);
	DeleteObject(hOldBrush);
}

//产生初始的方块 
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
		st_array[0][0] = 0, st_array[0][1] = 1, st_array[0][2] = 1, st_array[0][3] = 0;// 0 1 1 0
		st_array[1][0] = 1, st_array[1][1] = 1, st_array[1][2] = 0, st_array[1][3] = 0;// 1 1 0 0
		break;
	case(2):
		st_array[0][0] = 0, st_array[0][1] = 1, st_array[0][2] = 0, st_array[0][3] = 0;//0 1 0 0
		st_array[1][0] = 1, st_array[1][1] = 1, st_array[1][2] = 1, st_array[1][3] = 0;//1 1 1 0
		break;
	case(3):
		st_array[0][0] = 0, st_array[0][1] = 0, st_array[0][2] = 1, st_array[0][3] = 0;//0 0 1 0
		st_array[1][0] = 1, st_array[1][1] = 1, st_array[1][2] = 1, st_array[1][3] = 0;//1 1 1 0
		break;
	case(4):
		st_array[0][0] = 1, st_array[0][1] = 0, st_array[0][2] = 0, st_array[0][3] = 0;//1 0 0 0
		st_array[1][0] = 1, st_array[1][1] = 1, st_array[1][2] = 1, st_array[1][3] = 0;//1 1 1 0
		break;
	case(5):
		st_array[0][0] = 1, st_array[0][1] = 1, st_array[0][2] = 1, st_array[0][3] = 1;//1 1 1 1
		st_array[1][0] = 0, st_array[1][1] = 0, st_array[1][2] = 0, st_array[1][3] = 0;//0 0 0 0
		break;
	case(6):
		st_array[0][0] = 0, st_array[0][1] = 1, st_array[0][2] = 1, st_array[0][3] = 0;//0 1 1 0
		st_array[1][0] = 0, st_array[1][1] = 1, st_array[1][2] = 1, st_array[1][3] = 0;//0 1 1 0
		break;
	}

	switch (n){
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		g_sqareId = 1;//普通方块
		g_markL = 0;
		g_markR = INTERVAL_L;
		break;
	case 5:
		g_sqareId = 2;//长条方块
		g_markL = -1;
		g_markR = INTERVAL_L;
		break;
	case 6:
		g_sqareId = 3;//正方形方块
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
	g_markL++;
}

//       消除行
void disappearSqare() {
	short  i, j, m, n;

	char flag = 1;

	for (i = BG_Y - 1; i >= 0; i--) {
		flag = 1;
		for (j = 0; j < BG_X ; j++) {
			if (2 != bg_array[i][j]) {
				flag = 0;
			}
		}
		if (1 == flag) {
			for (m= i; m > 0; m--) {
				for (n = 0; n < BG_X ; n++) {
					bg_array[m][n]= bg_array[m - 1][n];
					bg_array[m - 1][n] = 0;
				}
			}
			i++;
			g_score++;
		}
	}

}
//    游戏结束判断
char  ifStopGame() {
	char ifStop = 0;//默认不结束
	short i;

	for (i = 0; i < BG_X; i++) {
		if (2 == bg_array[0][i]) {
			return ifStop=1;
		}
	}
	return ifStop;
}

//      方块右移条件
short canSqareRight() {
	short canR = 1;//默认可以
	
   short	i = 0,
		    j = BG_X - 1;

	for (i = 0; i < BG_Y; i++) {
		for (j = BG_X - 1; j >= 0; j--) {
			if (1 == bg_array[i][j]) {
				if (j == BG_X - 1 || 2 == bg_array[i][j + 1]) {
					return canR = 0;
				}
			}
		}
	}
	return canR;
}

//      方块左移条件
short canSqareLeft() {
	short canL = 1;//默认可以

	short i = 0,j = 0;

	for (i = 0; i < BG_Y; i++) {
		for (j = 0; j < BG_X; j++) {
			if (1 == bg_array[i][j]) {
				if (0 == j || 2 == bg_array[i][j - 1]) {
					return canL = 0;
				}
			}
		}
	}
	return canL;
}
//      普通方块变形条件
short canSqareChange1() {
	short canC = 1;//默认可以

	short i, j;

	if (g_markR < 0 || g_markR > BG_X - 3) {
		return canC = 0;
	}                 //边界的不可以变形

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (2 == bg_array[g_markL + i][g_markR + j]) {
				return canC = 0;//不可以
			}
		}
	}

	return canC;
}
//      长条方块变形条件
short canSqareChange2(){
	short canC = 1;//默认可以

	short i, j;

	if (g_markR < 0 || g_markR > BG_X - 4||g_markL<0){
		return canC = 0;
	}                 //边界的不可以变形

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (2 == bg_array[g_markL + i][g_markR + j]) {
				return canC = 0;//不可以
			}
		}
	}

	return canC;
}

//方块不在下落的条件
short CanDownSqare() {
	int m;

	for (m = 0; m < BG_X; m++) {
		if (1 == bg_array[BG_Y - 1][m]) {
            return 1;
		}
	}
    
	return 0;
}
//方块不在下落的条件2
short CanDownSqare2() {
	int i, j;

	for (i = BG_Y - 1; i >= 0; i--) {
		for (j = 0; j < BG_X; j++) {
			if (1 == bg_array[i][j]) {
				if (2 == bg_array[i + 1][j]) {
					return 1;
				}
			}
		}
	}

	return 0;
}

//改变不能下落的方块从1到2
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
//普通方块变形
void  changeSqare1() {
	char sqareArray[3][3] = { 0 };
	short i, j;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			sqareArray[i][j] = bg_array[g_markL + i][g_markR + j];
		}
	}

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			bg_array[g_markL + i][g_markR + j] = sqareArray[j][2-i];
		}
	}
}
//      长条方块变形
void  changeSqare2() {
	char sqareArray[4][4] = {0};

	short i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			sqareArray[i][j] = bg_array[g_markL + i][g_markR + j];
		}
	}

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			 bg_array[g_markL + i][g_markR + j]= sqareArray[j][i];
		}
	}
}