#include <windows.h>
#include <time.h>
#include <stdlib.h>

/*
ԭ����Ļ����ϵͳ����ʵ����һ�����ڡ�ȫ�����������̵�����������
���裺
1������һ�����ڳ���WinMain����QQ��360��VS��,����ȥ��������̨����main��
2���߿���󻯿���С���򡢹رտ򡢲˵�����Ҫ������˰�ɫ����
3����������󻯡�������ɺ������Сһ�������൱��һ�鲼����������������棩ֻ�ܹ�������ĳ��򡢿�����������
4���滭��������
5������ƶ�������������̰��¡�����̧��Ҫ����ĳ����˳����رճ���
*/

//���ڴ�����
LRESULT CALLBACK WindowProc(
	HWND hWnd,					//���ھ��
	UINT uMsg,					//��Ϣ��� 
	WPARAM wParam,				//������Ϣ  ����
	LPARAM lParam				//������Ϣ  100��200
	);

int __stdcall WinMain(
				HINSTANCE hInstance,	//Ӧ�ó���ʵ�����
				HINSTANCE hPreInstance,	//Ӧ�ó���ǰһ��ʵ�����
				LPSTR lpCmdLine,		//�����в���
				int nCmdShow			//������ʾ��ʽ 0,1,2,3
			)
{
	//Hello World
	//L���߱��������ַ���Ҫ����Unicode������б��룬֧��ȫ�����������
	//MessageBox(NULL,L"Hello World",L"������Ļ����ϵͳ",MB_OK);

	//���ڴ������裺
	//1����ƴ�����
	//char 
	wchar_t szAppClassName[]=L"TZScreensaver";

	WNDCLASS wndClass;
	wndClass.cbClsExtra=0;				//��������չ�ռ��С��0�ֽ�
	wndClass.cbWndExtra=0;				//���ڶ�����չ�ڴ�ռ��С 0�ֽ�
	wndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);//����һ����ɫ����
	wndClass.hCursor=LoadCursor(NULL,MAKEINTRESOURCE(IDC_ARROW));				//���Ĺ��
	wndClass.hIcon=NULL;					//����һ��ͼ��
	wndClass.hInstance=hInstance;			//Ӧ�ó���ʵ�����
	wndClass.lpfnWndProc=WindowProc;		//���ڴ�����
	wndClass.lpszClassName=szAppClassName;//����������
	wndClass.lpszMenuName=NULL;			//�˵���
	wndClass.style=CS_HREDRAW|CS_VREDRAW;//������ķ��

	//2��ע�ᴰ����
	RegisterClass(&wndClass);


	//3����ȡ��Ļ�Ŀ�͸�
	int nScreenWidth=GetSystemMetrics(SM_CXSCREEN);
	int nScreenHeight=GetSystemMetrics(SM_CYSCREEN);


	//4����������
	HWND hMainWnd=CreateWindow(
		szAppClassName,						//����������
		L"�ڿ���Ļ����ϵͳ",					//���ڵı���
		NULL,							//���ڵķ��
		0,									//�������ϽǺ�����
		0,									//�������Ͻ�������
		nScreenWidth,						//���ڵĿ��
		nScreenHeight,						//���ڵĸ߶�
		NULL,								//�����ھ��
		NULL,								//�˵����
		hInstance,							//ʵ�����
		NULL								//����
		);

	//5����ʾ����
	ShowWindow(hMainWnd,SW_SHOW);

	//6����Ϣѭ��
	MSG msg;
	//��Ϣ���� ��Ϣ��������
	while(GetMessage(&msg,NULL,0,0))
	{
		//���������Ϣת��Ϊ�ַ���Ϣ
		TranslateMessage(&msg);

		//����Ϣ�ַ����ص���������
		DispatchMessage(&msg);
	}


	return 0;//
}
//���ڴ�����
LRESULT CALLBACK WindowProc(
	HWND hWnd,					//���ھ��
	UINT uMsg,					//��Ϣ��� 
	WPARAM wParam,				//������Ϣ  ����
	LPARAM lParam				//������Ϣ  100��200
	)
{
	PAINTSTRUCT ps;
	HDC hDC=NULL;
	RECT rect;

	switch (uMsg)
	{
	case WM_LBUTTONDOWN://���������
		DestroyWindow(hWnd);//���ٴ���
		break;
	case WM_RBUTTONDOWN://����Ҽ����
		DestroyWindow(hWnd);//���ٴ���
		break;
	case WM_MBUTTONDOWN://����м�����
		DestroyWindow(hWnd);//���ٴ���
		break;
	case WM_KEYDOWN://���̰���
		DestroyWindow(hWnd);//���ٴ���
		break;
	case WM_MOUSEMOVE://����ƶ�
		break;
	case WM_CREATE://���ڴ�����Ϣ,���ڴ���֮���ڴ��ڻ�û�г��֣�
	{					
		//��ȡ����ķ��
		DWORD dwStyle=GetWindowLong(hWnd,GWL_STYLE);
		dwStyle=dwStyle&~WS_BORDER;
		dwStyle=dwStyle&~WS_CAPTION;
		dwStyle=dwStyle&~WS_SYSMENU;
		dwStyle=dwStyle&~WS_THICKFRAME;
		dwStyle=dwStyle&~WS_MAXIMIZEBOX;
		dwStyle=dwStyle&~WS_MINIMIZEBOX;
		//����Ӧ��������
		SetWindowLong(hWnd,GWL_STYLE,dwStyle);

		//������ʱ��
		SetTimer(hWnd,1,2000,NULL);

		break;
	}
	case WM_PAINT:
	{	
		hDC=BeginPaint(hWnd,&ps);
		/************************************************************************/
		//*
		/***********************************************************************/

		//��ȡ���E���ͻ�����С
		GetClientRect(hWnd,&rect);

		srand((UINT)time(NULL));
		HBRUSH hBrush= CreateSolidBrush(RGB(rand()%256,rand()%256,rand()%256));
		FillRect(hDC,&rect,hBrush);
		
		EndPaint(hWnd,&ps);
		break;
	}
	case WM_CLOSE://���ڹر���Ϣ
		DestroyWindow(hWnd);//���ٴ���
		break;
	case WM_DESTROY://���ڴݻ���Ϣ
		PostQuitMessage(0);
		break;
	case WM_TIMER:
		InvalidateRect(hWnd,NULL,TRUE);
		break;
	}


	return DefWindowProc(hWnd,uMsg,wParam,lParam);//Ĭ����Ϣ������
}