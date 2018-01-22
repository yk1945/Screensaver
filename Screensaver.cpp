#include <windows.h>
#include <time.h>
#include <stdlib.h>

/*
原理：屏幕保护系统：其实就是一个窗口、全屏、花花绿绿的数字在闪动
步骤：
1、开发一个窗口程序【WinMain】（QQ、360，VS）,不是去开发控制台程序【main】
2、边框、最大化框、最小化框、关闭框、菜单都不要（变成了白色区域）
3、程序将它最大化、将它变成和桌面大小一样，（相当于一块布、铺在你的桌面上面）只能够看到你的程序、看不到其他的
4、绘画、动起来
5、鼠标移动、鼠标点击、键盘按下、键盘抬起都要将你的程序退出，关闭程序。
*/

//窗口处理函数
LRESULT CALLBACK WindowProc(
	HWND hWnd,					//窗口句柄
	UINT uMsg,					//消息编号 
	WPARAM wParam,				//附加消息  按键
	LPARAM lParam				//附加消息  100，200
	);

int __stdcall WinMain(
				HINSTANCE hInstance,	//应用程序实例句柄
				HINSTANCE hPreInstance,	//应用程序前一个实例句柄
				LPSTR lpCmdLine,		//命令行参数
				int nCmdShow			//窗口显示方式 0,1,2,3
			)
{
	//Hello World
	//L告诉编译器：字符串要是用Unicode编码进行编码，支持全世界各国语言
	//MessageBox(NULL,L"Hello World",L"打造屏幕保护系统",MB_OK);

	//窗口创建步骤：
	//1、设计窗口类
	//char 
	wchar_t szAppClassName[]=L"TZScreensaver";

	WNDCLASS wndClass;
	wndClass.cbClsExtra=0;				//窗口类扩展空间大小，0字节
	wndClass.cbWndExtra=0;				//窗口额外扩展内存空间大小 0字节
	wndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);//加载一个黑色背景
	wndClass.hCursor=LoadCursor(NULL,MAKEINTRESOURCE(IDC_ARROW));				//鼠标的光标
	wndClass.hIcon=NULL;					//加载一个图标
	wndClass.hInstance=hInstance;			//应用程序实例句柄
	wndClass.lpfnWndProc=WindowProc;		//窗口处理函数
	wndClass.lpszClassName=szAppClassName;//窗口类型名
	wndClass.lpszMenuName=NULL;			//菜单名
	wndClass.style=CS_HREDRAW|CS_VREDRAW;//窗口类的风格

	//2、注册窗口类
	RegisterClass(&wndClass);


	//3、获取屏幕的宽和高
	int nScreenWidth=GetSystemMetrics(SM_CXSCREEN);
	int nScreenHeight=GetSystemMetrics(SM_CYSCREEN);


	//4、创建窗口
	HWND hMainWnd=CreateWindow(
		szAppClassName,						//窗口类型名
		L"黑客屏幕保护系统",					//窗口的标题
		NULL,							//窗口的风格
		0,									//窗口左上角横坐标
		0,									//窗口左上角纵坐标
		nScreenWidth,						//窗口的宽度
		nScreenHeight,						//窗口的高度
		NULL,								//父窗口句柄
		NULL,								//菜单句柄
		hInstance,							//实例句柄
		NULL								//参数
		);

	//5、显示窗口
	ShowWindow(hMainWnd,SW_SHOW);

	//6、消息循环
	MSG msg;
	//消息队列 消息驱动机制
	while(GetMessage(&msg,NULL,0,0))
	{
		//将虚拟键消息转换为字符消息
		TranslateMessage(&msg);

		//将消息分发给回调函数处理
		DispatchMessage(&msg);
	}


	return 0;//
}
//窗口处理函数
LRESULT CALLBACK WindowProc(
	HWND hWnd,					//窗口句柄
	UINT uMsg,					//消息编号 
	WPARAM wParam,				//附加消息  按键
	LPARAM lParam				//附加消息  100，200
	)
{
	PAINTSTRUCT ps;
	HDC hDC=NULL;
	RECT rect;

	switch (uMsg)
	{
	case WM_LBUTTONDOWN://鼠标左键点击
		DestroyWindow(hWnd);//销毁窗口
		break;
	case WM_RBUTTONDOWN://鼠标右键点击
		DestroyWindow(hWnd);//销毁窗口
		break;
	case WM_MBUTTONDOWN://鼠标中间键点击
		DestroyWindow(hWnd);//销毁窗口
		break;
	case WM_KEYDOWN://键盘按下
		DestroyWindow(hWnd);//销毁窗口
		break;
	case WM_MOUSEMOVE://鼠标移动
		break;
	case WM_CREATE://窗口创建消息,窗口创建之后，在窗口还没有出现，
	{					
		//获取程序的风格
		DWORD dwStyle=GetWindowLong(hWnd,GWL_STYLE);
		dwStyle=dwStyle&~WS_BORDER;
		dwStyle=dwStyle&~WS_CAPTION;
		dwStyle=dwStyle&~WS_SYSMENU;
		dwStyle=dwStyle&~WS_THICKFRAME;
		dwStyle=dwStyle&~WS_MAXIMIZEBOX;
		dwStyle=dwStyle&~WS_MINIMIZEBOX;
		//设置应用这个风格
		SetWindowLong(hWnd,GWL_STYLE,dwStyle);

		//开启定时器
		SetTimer(hWnd,1,2000,NULL);

		break;
	}
	case WM_PAINT:
	{	
		hDC=BeginPaint(hWnd,&ps);
		/************************************************************************/
		//*
		/***********************************************************************/

		//获取这鞥个客户区大小
		GetClientRect(hWnd,&rect);

		srand((UINT)time(NULL));
		HBRUSH hBrush= CreateSolidBrush(RGB(rand()%256,rand()%256,rand()%256));
		FillRect(hDC,&rect,hBrush);
		
		EndPaint(hWnd,&ps);
		break;
	}
	case WM_CLOSE://窗口关闭消息
		DestroyWindow(hWnd);//销毁窗口
		break;
	case WM_DESTROY://窗口摧毁消息
		PostQuitMessage(0);
		break;
	case WM_TIMER:
		InvalidateRect(hWnd,NULL,TRUE);
		break;
	}


	return DefWindowProc(hWnd,uMsg,wParam,lParam);//默认消息处理函数
}