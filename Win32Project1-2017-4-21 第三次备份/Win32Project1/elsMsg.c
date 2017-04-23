#include "elsHead.h"

char bg_array[BG_Y][BG_X] = { 0 };//������������
char st_array[2][4] = { 0 };//��������


void onPaint(HDC hDC) {
	//����������DC
	HDC hMemDc = CreateCompatibleDC(hDC); 
	//����λͼ
	HBITMAP hBitMap = CreateCompatibleBitmap(hDC, WIND_W,WIND_H);
	//����DC��λͼ
	SelectObject(hMemDc,hBitMap);
	
    paintSqare(hMemDc);   //DC��ͼ
	printSqare2(hMemDc);

	//����
	BitBlt(hDC, 0, 0, BG_W, BG_H, hMemDc, 0, 0, SRCCOPY);


	//�ͷ�
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

//���ڲ���
void onCreat() {
	srand((unsigned int)time(NULL));//���������������
	creatRandSqare();  //�����������
	moveStarToBg();    //����
}

//�س����µ���Ӧ
void onReturn(HWND hWnd) {
	SetTimer(hWnd, ID_TIMER1, 1000, NULL);//���ö�ʱ��������Ĳ�������ΪNULL�����һ��WM_TIMER��Ϣ��
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
}

//���鲻�����������
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

//��ʾ�ײ�
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

//Timer��Ϣ��Ӧ
void onTimer(HWND hWnd) {
	HDC hDc = GetDC(hWnd);

	if (0 == CanDownSqare()){
          sqareDown();   //��������
	}
	else {
		change1To2();
		creatRandSqare();
		moveStarToBg();
	}
	
	onPaint(hDc);   //��ӡ

	ReleaseDC(hWnd,hDc);  //�ͷ�
}