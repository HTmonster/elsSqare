

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
    
	
	void onCreat();//��������ʱ����Ӧ
	void onPaint(HDC hDC);//�����ڵ���Ӧ
	void onReturn(HWND hWnd);//    ������Ϣ�س�������Ӧ
	void onTimer(HWND hWnd);//    ��ʱ����Ϣ��Ӧ
	void onLeft(HWND hWnd);//    �����Ӧ������)
	void onRight(HWND hWnd);//    �Ҽ���Ӧ������)
	void onDown(HWND hWnd);//     �¼���Ӧ�����٣�
	void onUp(HWND hWnd);//      �ϼ���Ӧ�����Σ�

	
	void paintSqare(HDC hMemDc);//     ����DCͼ(�����ϲ���
	void creatRandSqare();//     �����������
	void moveStarToBg();//        �������ͱ�������
    void  printSqare2(HDC hMemDc);	//��ʾ�ײ�

	void sqareDown();	//        ��������
	void disappearSqare();//       ������

	char  ifStopGame();//    ��Ϸ�����ж�
	short canSqareLeft();   //      ������������
	short canSqareRight();  //      ������������
	short canSqareChange1(); //      ��ͨ�����������
	short canSqareChange2(); //      ���������������
	short CanDownSqare();	//        ����������������ʼ��
	short CanDownSqare2();	//        ������������2���ײ���

	void  change1To2();	//        �ı�ײ�����
	void  changeSqare1();//      ��ͨ�������
	void  changeSqare2();//      �����������
#endif // ! DEF_ELS_HEAD