

#ifndef  DEF_ELS_HEAD
    
#define DEF_ELS_HEAD
    #include<Windows.h>
    #include<time.h>   

    #define  ID_TIMER1  1   //��ʱ��id
    #define  WIND_H    600  //���ڸ�
     #define WIND_W    400  //���ڿ�
    #define  BG_H  600      //��Ϸ����ĸ�
    #define  BG_W  300      //��Ϸ����Ŀ�
    #define  BG_Y  20       //���ĸߣ���λ������ı߳���
    #define  BG_X 10        //���Ŀ�
    #define  INTERVAL_L 3   //��ʼʱ����ߵľ��루��λ������ı߳���
    #define  SQARE_SIZE 30  //����ı߳� 

    //�����ڵ���Ӧ
	void onPaint(HDC hDC);
	//     ����DCͼ
	void paintSqare(HDC hMemDc);
	//     �����������
	void creatRandSqare();
	//        �������ͱ�������
	void moveStarToBg();
	//��������ʱ����Ӧ
	void onCreat();
	//    ������Ϣ�س�������Ӧ
	void onReturn(HWND hWnd);
	//        ��������
	void sqareDown();
	//    ��ʱ����Ϣ��Ӧ
	void onTimer(HWND hWnd);
	//        ������������
	short CanDownSqare();
	//        �ı�ײ�����
	void  change1To2();
	//��ʾ�ײ�
	void  printSqare2(HDC hMemDc);
#endif // ! DEF_ELS_HEAD



