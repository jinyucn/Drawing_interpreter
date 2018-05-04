#include "semantic.h"
#define MAX_CHARS 200

HDC hDC;				// ���ھ����ȫ�ֱ���
char SrcFilePath[] = "d:\\test.txt";		// ���ڴ��Դ�����ļ�·��
static char* Name = "Compiler";	// ������
//semantics_class drawer;			// ������ͼ������Դ�������
static bool PrepareWindow(HINSTANCE,HINSTANCE,int);
static bool CheckSrcFile(LPSTR);
static LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);


// ------------------------- window����������
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	// ����Դ�ļ�·��
	strcpy(lpCmdLine,SrcFilePath);

	// ��ʼ������.
	if ( PrepareWindow(hInstance,hPrevInstance,nCmdShow) != true)
	{	MessageBox(NULL,"���ڳ�ʼ��ʧ�� !","����",MB_OK);
		return 1;
	}

	// ���Ҫ������Դ�����ļ�
	//if ( !CheckSrcFile(lpCmdLine)) return 1;

	// --------------------------------------------
	//		���û�ͼ���Խ����������÷�����Դ�������
	analyse_tree();
	// --------------------------------------------

	// ����window��Ϣѭ��
	MSG Msg;
	while(GetMessage(&Msg,NULL,0,0))
	{	TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

// ------------------------- ��ʼ�����ں���
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



// ------------------------- ���Դ�����ļ��Ƿ�Ϸ�����
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

// ------------------------- ���ڴ�����
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
			//		���û�ͼ���Խ����������÷�����Դ�������
			analyse_tree();

			// --------------------------------------------
			EndPaint(hWnd,&pt);
		default:
			return DefWindowProc(hWnd,Message,wParam,lParam);
	}
}



