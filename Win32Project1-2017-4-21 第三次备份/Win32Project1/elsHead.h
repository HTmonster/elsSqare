

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

    //画窗口的响应
	void onPaint(HDC hDC);
	//     产生DC图
	void paintSqare(HDC hMemDc);
	//     产生随机方块
	void creatRandSqare();
	//        随机方块和背景关联
	void moveStarToBg();
	//产生窗口时的响应
	void onCreat();
	//    键盘消息回车键的响应
	void onReturn(HWND hWnd);
	//        方块下落
	void sqareDown();
	//    定时器消息响应
	void onTimer(HWND hWnd);
	//        方块下落条件
	short CanDownSqare();
	//        改变底部数字
	void  change1To2();
	//显示底部
	void  printSqare2(HDC hMemDc);
#endif // ! DEF_ELS_HEAD



