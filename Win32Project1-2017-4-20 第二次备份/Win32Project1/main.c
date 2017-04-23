#include<Windows.h>
#include"elsHead.h"
#include"resource.h"

LRESULT CALLBACK Prussia(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lparam);

//WINAPI 调用约定 主要是参数的入栈顺序 栈空间的清理 与_stdcall APIENTPY一致
//Hinstance 句柄  窗口的唯一标识
//LPTSTR  应用的命令行
//nCmdShow 决定窗口的默认显示方式
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR IpCmdLin, int nCmdShow) {

	HWND hWnd;  //句柄
	MSG mSg;//消息结构体变量

	//初始化窗口类
	WNDCLASSEX wc;//系统支持的结构，用来储存某一类窗口的信息
	

	wc.cbClsExtra = 0;//窗口扩展
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;//窗口实例拓展
	wc.hbrBackground = (HBRUSH)COLOR_MENU;//窗口背景颜色
	wc.hCursor = LoadCursor(NULL, IDC_HAND); //窗口光标
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));//窗口状态栏图标
	wc.hIconSm = NULL;//窗口图标
	wc.hInstance = hInstance;//当前窗口实例
	wc.lpfnWndProc = Prussia;//回调函数地址
	wc.lpszClassName = "els";//窗口类名 （对于操作系统唯一的标志）
	wc.lpszMenuName = NULL;//窗口菜单名
	wc.style = CS_DROPSHADOW;//窗口风格

	//总12个，少了或者多了都无法创建窗口
	
    //注册窗口

	//参数：const WNDCLASSEX *lpwcx  （指向窗口类的指针）
	//返回值：ATOM (unsigned short)
	if (0 == RegisterClassEx(&wc)){

		return 0;//出错了直接结束
	}

	//创建窗口

	//返回值：HWND 句柄
	//参数1： DWORD    dwExStyle（附加属性）
	//参数2;  LPCTSTR   lpClassName(窗口的名字，给系统看）
	//参数3： LPCTSTR   lpWindowName(窗口的名字，给人看）
	//参数4： DWORD     dwStyle（指定窗口的风格）
	//参数5.6：int x   int y(初始窗口的位置）
	//参数7.8: int nWidth  int  nHeight(窗口的高度和宽度）
	//参数9： HWND    hWndParent（父句柄）
	//参数10：HMENU   hMenu(菜单句柄）
	//参数11：HINSTANCE hInstance(当前实例句柄）
	//参数12：LPVOID  lpParam(指向一个值的指针）

	hWnd = CreateWindowEx(WS_EX_TOPMOST,"els","俄罗斯方块", WS_SYSMENU,10,10,400,645,NULL,NULL,hInstance,NULL);
	
	if (NULL == hWnd) {
		return 0;//创建失败直接结束
	}

	//显示窗口

	//返回值：BOOL(正常显示返回非零，隐藏显示返回零)
	//参数1：HWND hWnd(句柄）
	//参数2：int  nCmdShow(窗口显示的风格）

	ShowWindow (hWnd, SW_SHOWNORMAL);

	//消息循环

	/*
	****************************************************
	//取消息函数
	
	//返回值：BOOL(正常执行返回非零）
	//参数1:  LPMSG lpMsg(指向消息结构体的指针）
	//参数2： HWND  hWnd(窗口句柄代表的消息 NULL代表全部）
	//参数3.4：UINT  wMsgFilterMin  UINT  wMsgFilterMax（处理消息的范围 0，0 代表全部）
	******************************************************

   //翻译消息函数
   //返回值：BOOL
   //参数1： MSG *lpMs（指向消息结构体的指针）
   *******************************************************

   //分发消息（标准，命令，通知，自定义消息）

   //返回值： LRESULT
   //参数1：MSG *lpmsg（指向消息结构体的指针）
 
	*/
	while(GetMessage(&mSg,NULL,0,0))
	{
		TranslateMessage(&mSg);
		DispatchMessage(&mSg);
	}

	return 0;
}

//回调函数
//返回值：LRESULT(long)
//函数约定：CALLBACK(和WINAPI相同）
//参数1：HWND hWnd (窗口句柄)
//参数2：UINT nMsg (消息ID)
//参数3.4：WPARAM wParam   LPARAM lParam（消息附带的数据）

LRESULT CALLBACK Prussia(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{   PAINTSTRUCT pt;
    HDC hDC;
	switch (nMsg) 
	{
		  case WM_CREATE:
			  onCreat();//初次创建时的处理函数
			  break;             //窗口创建时的消息，只产生一次
		  case WM_PAINT:
			  hDC=BeginPaint(hWnd, &pt);//hDC 可绘制的区域的标志  可以用getDC()
			  //画窗口上图形
			  onPaint(hDC);//画窗口函数
			  EndPaint(hWnd, &pt);
			  break;            //窗口大小改变，窗口重叠时产生
		  
		  case WM_DESTROY:
			  PostQuitMessage(0);//点差后产生的消息 WM_CLOSE WM_DESTROY WM_QUIT
			  break;
	}

	return DefWindowProc(hWnd, nMsg, wParam, lParam);//系统自己处理一些消息 参数类型和回调函数相同
}
//窗口句柄：当前窗口的唯一标识（值是一个数）