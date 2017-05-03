#include "elsHead.h"

char bg_array[BG_Y][BG_X] = { 0 };//������������
char st_array[2][4] = { 0 };//��������
short g_sqareId = -1;//����id
short g_markL = -1; //�������� i
short g_markR = -1; //�������� j
int   g_score = 0;   //����

//���ڲ�����Ӧ
void onCreat() {
	srand((unsigned int)time(NULL));//���������������
	creatRandSqare();  //������һ���������
	moveStarToBg();    //����
}

//������ʱ�����Ӧ
void onPaint(HDC hDC) {

	char scoreStr[10] = { 0 };//�����ַ�

	itoa(g_score, scoreStr, 10);
	//����������DC
	HDC hMemDc = CreateCompatibleDC(hDC); 
	//����λͼ
	HBITMAP hBitMap = CreateCompatibleBitmap(hDC, WIND_W,WIND_H);
	//����DC��λͼ
	SelectObject(hMemDc,hBitMap);
	
    paintSqare(hMemDc);   //DC��ͼ
	printSqare2(hMemDc);  //�ײ���

	//����
	BitBlt(hDC, 0, 0, BG_W, BG_H, hMemDc, 0, 0, SRCCOPY);

	//�������

	TextOut(hDC, BG_W , 20, "���ķ����ǣ�", 12);
	TextOut(hDC, BG_W+10, 50, scoreStr, strlen(scoreStr));
	TextOut(hDC, BG_W, 320, "�س�����ʼ��", 10);
	TextOut(hDC, BG_W, 340, "�ϼ������Σ�", 10);
	TextOut(hDC, BG_W, 360, "�¼������٣�", 10);
	TextOut(hDC, BG_W, 380, "��������ƣ�", 10);
	TextOut(hDC, BG_W, 400, "�Ҽ������ƣ�", 10);
	TextOut(hDC, BG_W, 580, "����:Theohui", 12);
	//�ͷ�
	DeleteObject(hMemDc);
	DeleteDC(hDC);
}

//�س����µ���Ӧ
void onReturn(HWND hWnd) {
	SetTimer(hWnd, ID_TIMER1, 1000, NULL);//���ö�ʱ��������Ĳ�������ΪNULL�����һ��WM_TIMER��Ϣ��
}


//����
void onRight(HWND hWnd) {

	HDC hDc = GetDC(hWnd);

	short i = 0,
	      j = BG_X - 1;

	if (1==canSqareRight() ){
		for (i = 0; i < BG_Y; i++) {
			for (j = BG_X - 1; j >= 0; j--) {
				if (1 == bg_array[i][j]) {
					bg_array[i][j + 1] = 1;
					bg_array[i][j] = 0;//����
				}
			}
		}
		g_markR++;
	}
	onPaint(hDc);   //��ӡ

	ReleaseDC(hWnd, hDc);  //�ͷ�
}
//����
void onLeft(HWND hWnd) {
    HDC hDc = GetDC(hWnd);
	
	short i = 0,
		  j = 0;

	if (1==canSqareLeft()) {
		for (i = 0; i < BG_Y; i++) {
			for (j =0; j <BG_X; j++) {
				if (1 == bg_array[i][j]) {
					bg_array[i][j - 1] = 1;
					bg_array[i][j] = 0;//����
				}
			}
		}
		g_markR--;
	}
	onPaint(hDc);   //��ӡ

	ReleaseDC(hWnd, hDc);  //�ͷ�
}
//����
void onDown(HWND hWnd) {
	onTimer(hWnd);
}

//����
void onUp(HWND hWnd) {
	HDC hDc = GetDC(hWnd);
    
	switch (g_sqareId)
	{
	case 1:
		if (1 == canSqareChange1()) {
			changeSqare1();       //��ͨ����
		}
		break;
	case 2:
		if (1 == canSqareChange2()) {
			changeSqare2();    //��������
		} 
		break;
	case 3:
		return;
		break;
	default:
		return;
		break;
	}


	onPaint(hDc);   //��ӡ
	ReleaseDC(hWnd, hDc);  //�ͷ�
}

//Timer��Ϣ��Ӧ
void onTimer(HWND hWnd) {
	HDC hDc = GetDC(hWnd);

	if (0 == CanDownSqare() && 0 == CanDownSqare2()) {
		sqareDown();   //��������
	}
	else {
		change1To2();     //�����ͣ�ȵĸı䵽2
		if (1 == ifStopGame())//���������Ϸ
		{
			MessageBox(NULL, "��Ϸ����", "��ʾ", MB_OK);//��ʾ��
			KillTimer(hWnd, ID_TIMER1);//�رն�ʱ��
			return 0;//����
		}    
		disappearSqare(); //��������
		creatRandSqare(); //�����µķ���
		moveStarToBg();   //���·����Ƶ�������
	}

	onPaint(hDc);   //��ӡ

	ReleaseDC(hWnd, hDc);  //�ͷ�
}

//�����飨1��
void paintSqare(HDC hMemDc) {
	int i, j;
	HBRUSH hNewBrush, hOldBrush;//��ˢ

	Rectangle(hMemDc, 0, 0, BG_W, BG_H);//�����

	hNewBrush = CreateSolidBrush(RGB(150, 255, 150));//����ɫ
	hOldBrush = SelectObject(hMemDc, hNewBrush);

	for (i = 0; i <BG_Y; i++) {     //��1
		for (j = 0; j <BG_X; j++) {
			if (1==bg_array[i][j]) {
               Rectangle(hMemDc, SQARE_SIZE*j, SQARE_SIZE*i, SQARE_SIZE * (j+1), SQARE_SIZE * (i+1));
			}
		}
	}

	hOldBrush = SelectObject(hMemDc, hOldBrush);
	DeleteObject(hOldBrush);

}

//��ʾ�ײ�����2��
void  printSqare2(HDC hMemDc) {
	int i, j;
	HBRUSH hNewBrush, hOldBrush;//��ˢ

	hNewBrush = CreateSolidBrush(RGB(255, 0, 0));//����ɫ
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

//������ʼ�ķ��� 
void creatRandSqare() {
	short n;
	n = rand()%7;

	//��ʼ�����
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
		g_sqareId = 1;//��ͨ����
		g_markL = 0;
		g_markR = INTERVAL_L;
		break;
	case 5:
		g_sqareId = 2;//��������
		g_markL = -1;
		g_markR = INTERVAL_L;
		break;
	case 6:
		g_sqareId = 3;//�����η���
		break;
	}
}

//�ѷ������������ķ����Ƶ�����
void moveStarToBg() {
	short i = 0,
		  j = 0;

	for (i = 0; i < 2; i++) {
		for (j = 0; j < 4; j++) {
			bg_array[i][j + INTERVAL_L] = st_array[i][j];
		}
	}
}


//��������
void sqareDown() {
	short i = 0,
		j = 0;

	for (i =BG_Y-1; i >=0; i--) {
		for (j = BG_X-1; j>=0; j--) {
			if (1 == bg_array[i][j]) {
				bg_array[i][j]=0;
			    bg_array[i + 1][j]=1;//��������
			}
		}
	}
	g_markL++;
}

//       ������
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
//    ��Ϸ�����ж�
char  ifStopGame() {
	char ifStop = 0;//Ĭ�ϲ�����
	short i;

	for (i = 0; i < BG_X; i++) {
		if (2 == bg_array[0][i]) {
			return ifStop=1;
		}
	}
	return ifStop;
}

//      ������������
short canSqareRight() {
	short canR = 1;//Ĭ�Ͽ���
	
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

//      ������������
short canSqareLeft() {
	short canL = 1;//Ĭ�Ͽ���

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
//      ��ͨ�����������
short canSqareChange1() {
	short canC = 1;//Ĭ�Ͽ���

	short i, j;

	if (g_markR < 0 || g_markR > BG_X - 3) {
		return canC = 0;
	}                 //�߽�Ĳ����Ա���

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (2 == bg_array[g_markL + i][g_markR + j]) {
				return canC = 0;//������
			}
		}
	}

	return canC;
}
//      ���������������
short canSqareChange2(){
	short canC = 1;//Ĭ�Ͽ���

	short i, j;

	if (g_markR < 0 || g_markR > BG_X - 4||g_markL<0){
		return canC = 0;
	}                 //�߽�Ĳ����Ա���

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (2 == bg_array[g_markL + i][g_markR + j]) {
				return canC = 0;//������
			}
		}
	}

	return canC;
}

//���鲻�����������
short CanDownSqare() {
	int m;

	for (m = 0; m < BG_X; m++) {
		if (1 == bg_array[BG_Y - 1][m]) {
            return 1;
		}
	}
    
	return 0;
}
//���鲻�����������2
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

//�ı䲻������ķ����1��2
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
//��ͨ�������
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
//      �����������
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