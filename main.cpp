#include "semantic.h"
#define MAX_CHARS 200

HDC hDC;				// 窗口句柄，全局变量
char SrcFilePath[] = "d:\\test.txt";		// 用于存放源程序文件路径
static char* Name = "Compiler";	// 窗口名
//semantics_class drawer;			// 函数绘图对象，视源程序而定
static bool PrepareWindow(HINSTANCE,HINSTANCE,int);
static bool CheckSrcFile(LPSTR);
static LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);


// ------------------------- window程序主函数
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	// 保存源文件路径
	strcpy(lpCmdLine,SrcFilePath);

	// 初始化窗口.
	if ( PrepareWindow(hInstance,hPrevInstance,nCmdShow) != true)
	{	MessageBox(NULL,"窗口初始化失败 !","错误",MB_OK);
		return 1;
	}

	// 检查要分析的源程序文件
	//if ( !CheckSrcFile(lpCmdLine)) return 1;

	// --------------------------------------------
	//		调用绘图语言解释器，调用方法视源程序而定
	analyse_tree();
	// --------------------------------------------

	// 进入window消息循环
	MSG Msg;
	while(GetMessage(&Msg,NULL,0,0))
	{	TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

// ------------------------- 初始化窗口函数
bool PrepareWindow(HINSTANCE hInst,
                   HINSTANCE hPrevInstance,
		   int	     nCmdShow)
{	HWND	   hWnd;
	WNDCLASS   W;

	memset(&W,0,sizeof(WNDCLASS));
	W.style = CS_HREDRAW | CS_VREDRAW;
	W.lpfnWndProc = WndProc;
	W.hInstance = hInst;
	W.hCursor = LoadCursor(NULL,IDC_ARROW);
	W.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
	W.lpszClassName =Name;
	RegisterClass(&W);

	hWnd = CreateWindow(Name, Name, WS_OVERLAPPEDWINDOW,10,10,740,490,NULL,NULL,hInst,NULL);
	if(hWnd == NULL) return false;

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	SetCursor(LoadCursor(hInst,IDC_ARROW));

	hDC = GetDC(hWnd);
	return true;
}



// ------------------------- 检查源程序文件是否合法函数
/*bool CheckSrcFile(LPSTR lpszCmdParam)
{	FILE * file = NULL;

	if(strlen(lpszCmdParam) == 0)
	{	MessageBox(NULL,"no file", "error1", MB_OK);
		return false;
	}
	if((file = fopen(lpszCmdParam, "r")) == NULL)
	{	MessageBox(NULL,"open file error", "error2", MB_OK);
		MessageBox(NULL,lpszCmdParam, "filename", MB_OK);
		return false;
	}
	else fclose(file);
	return true;
}*/

// ------------------------- 窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd,UINT Message,WPARAM wParam,LPARAM lParam)
{	switch(Message)
	{	case WM_DESTROY:
			ReleaseDC(hWnd,hDC);
			PostQuitMessage(0);
			return 0;
		case WM_PAINT:
			PAINTSTRUCT pt;
			BeginPaint(hWnd,&pt);
			// --------------------------------------------
			//		调用绘图语言解释器，调用方法视源程序而定
			analyse_tree();

			// --------------------------------------------
			EndPaint(hWnd,&pt);
		default:
			return DefWindowProc(hWnd,Message,wParam,lParam);
	}
}



