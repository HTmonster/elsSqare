

#ifndef  DEF_ELS_HEAD
    
#define DEF_ELS_HEAD
    #include<Windows.h>
    #include<time.h>   

    #define  ID_TIMER1  1   //定时器id
    #define  WIND_H    600  //窗口高
     #define WIND_W    400  //窗口宽
    #define  BG_H  600      //游戏区域的高
    #define  BG_W  300      //游戏区域的宽
    #define  BG_Y  20       //大框的高（单位：方块的边长）
    #define  BG_X 10        //大框的宽
    #define  INTERVAL_L 3   //开始时与左边的距离（单位：方块的边长）
    #define  SQARE_SIZE 30  //方块的边长 
    
	
	void onCreat();//产生窗口时的响应
	void onPaint(HDC hDC);//画窗口的响应
	void onReturn(HWND hWnd);//    键盘消息回车键的响应
	void onTimer(HWND hWnd);//    定时器消息响应
	void onLeft(HWND hWnd);//    左键响应（左移)
	void onRight(HWND hWnd);//    右键响应（右移)
	void onDown(HWND hWnd);//     下键响应（加速）
	void onUp(HWND hWnd);//      上键响应（变形）

	
	void paintSqare(HDC hMemDc);//     产生DC图(画中上部）
	void creatRandSqare();//     产生随机方块
	void moveStarToBg();//        随机方块和背景关联
    void  printSqare2(HDC hMemDc);	//显示底部

	void sqareDown();	//        方块下落
	void disappearSqare();//       消除行

	char  ifStopGame();//    游戏结束判断
	short canSqareLeft();   //      方块左移条件
	short canSqareRight();  //      方块右移条件
	short canSqareChange1(); //      普通方块变形条件
	short canSqareChange2(); //      长条方块变形条件
	short CanDownSqare();	//        方块下落条件（开始）
	short CanDownSqare2();	//        方块下落条件2（底部）

	void  change1To2();	//        改变底部数字
	void  changeSqare1();//      普通方块变形
	void  changeSqare2();//      长条方块变形
#endif // ! DEF_ELS_HEAD