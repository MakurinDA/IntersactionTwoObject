#include <windows.h>

#include <gl\gl.h>
#include <gl\\glu.h>


#pragma comment (linker, "/defaultlib:opengl32.lib")
#pragma comment (linker, "/defaultlib:glu32.lib")

/*
������� ���������� ��� �������� ����,
�������� HINSTANCE,HWND,HDC � �.�.
*/

HINSTANCE hinstance_application;// ���������� ���������� 
HWND hwnd_window;// ���������� ����
HDC hdc_main;//���������� ��������� ����������

const char* pc_WindowClassName = "WindowClass";
const char* pc_wndTitle = "Windows ����������";


int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
/*
APIENTRY ���������� ��� ������ ����� ���������� � ����������� � �����
���� ���������� ���������
*/

BOOL InitializeApp(void);
void UninitializeApp(void);
void UnregisterWndClasses(void);

BOOL CreateWindows(void);
BOOL RegisterClassaOkna(void);

LRESULT CALLBACK MainWindowProc(HWND, UINT, WPARAM, LPARAM);

BOOL MainOnCreate(HWND);
BOOL MainOnDestroy(HWND);
BOOL MainOnPaint(HWND);
BOOL MainOnSize(HWND, int, int);
BOOL MainOnLButtonDown(HWND , int , int );
BOOL MainOnMouseMove(HWND , int , int , UINT );


int WINAPI WinMain(HINSTANCE hi_crr, HINSTANCE, LPSTR, int)
{
	MSG msg;
	/*
	�������� ������������� � ������������ ����������
	*/

	InitializeApp();
	BOOL return_;
	while (return_ = GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if (return_ == -1)
		{
			MessageBox(hwnd_window, "return_ = -1", "������", MB_ICONSTOP);
			return 0;
		}
		else
		{
			TranslateMessage(&msg);
			/*
			�� WM_KEYDOWN/WM_KEYUP ��������� ���������
			WM_CHAR/WM_SYSCHAR
			*/
			DispatchMessage(&msg);
			/*
			���������� ��������� � ������� ���������
			*/
		}
	}
	UninitializeApp();
	/*
	��������� ��������� �� ������� ��������� ����������� ������
	� �������� ��� � �������� ���������, ����������� �����������
	������������ ��������� ���� ��� �������� ��� ����������
	GetMessage(��������� �� MSG,������� ��������� ���������� �� ������� ����������
	���������� ����, ��� ��������� ������ ���� ���������
	NULL => ��������� ��������� ������ ����,
	� ������ �������� ��������
	0 => ���������� ��� ��������� ��������� ,
	�� ����� �������� ������������,
	0 => ���������� ��� ��������� ���������)
	if ��������� WM_QUIT, �� ���������� 0, else !0
	*/
	return msg.wParam;
}
/*
�������� �������
WinMain(���������� ��������(����� ���������������� ���������),
���������� ���������� �������� ������� � =0,
��������� �� ��������� ���������� � ��������� �� cmd,
���������� ����� ������ ���� �������� ���� �� �����)
*/
BOOL InitializeApp()
{
	if (!RegisterClassaOkna())
	{
		MessageBox(NULL, "������ ����������� ������� ����", pc_wndTitle, MB_OK);
		//MessageBox(���������� ���� ���������,���������� ������,��������� ����,����� ������ ����)
	}
	CreateWindows();
	ShowWindow(hwnd_window, SW_SHOW);
	//ShowWindow(���������� ����, ����� ������ ����)
	UpdateWindow(hwnd_window);
	//��������� ������� ������� ��������� ����
	return TRUE;
}
void UninitializeApp()
{
	UnregisterWndClasses();

}
void UnregisterWndClasses()
{
	UnregisterClass(pc_WindowClassName, hinstance_application);
	/*
	�������� ����������� ������ ����, ���������� ������
	*/
}
BOOL CreateWindows()
{

	hwnd_window = CreateWindow(pc_WindowClassName,// ��� ������
		pc_wndTitle,// ��� ���� 
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX |//����� ����:1.������� ������������� ���� 2.������� ���� ���� 3.������ ����������� 
		WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CLIPCHILDREN,//4.������ ������������� 5. ����� � ���������� �������� 6.��������� ������� �������� ���� ��� ���������� � ������������ ����
		0,// ��������� ���� �� ��� X �� ���������
		0,// ��������� ���� �� ��� Y �� ��������� 
		800,// ������ ���� 
		600,// ������ ���� 
		NULL,// ���������� ������������� ����(� ��� ��� ���)
		NULL,// ���������� ���� 
		hinstance_application,// ���������� ���������� ���������� 
		0// ��������� �� ������ ������������ �� ���������������� ������� WndProc
	);
	hdc_main = GetDC(hwnd_window);
	/*
	��������� ���������� ����������� ��������� ���������� ��� ������� �������
	����� ������������ ���������� � ����������� �������� ��� ��������� � ��������� ����������
	*/

	return TRUE;
}
BOOL RegisterClassaOkna(void)
{
	WNDCLASSEX wce_main;
	//������� ��������� ���������� �������� ������ ���� � ���������� wce_main
	memset(&wce_main, 0, sizeof(WNDCLASSEX));
	//��������� ������ ����������� ��������(������ WNDCLASSEX) ������
	wce_main.cbSize = sizeof(WNDCLASSEX);
	//������������� ������ ���� ��������� � ������
	wce_main.hInstance = hinstance_application;
	//���������� ���������� ������ ������� ������ �����
	wce_main.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC | CS_DBLCLKS;
	//����� ������
	wce_main.lpfnWndProc = (WNDPROC)MainWindowProc;
	//����� ������� �������
	wce_main.hCursor = LoadCursor(NULL, IDC_ARROW);
	//������ ���� ��� ����
	wce_main.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	//����� ��� ����
	wce_main.lpszClassName = pc_WindowClassName;
	//��� ������ ���� 
	return RegisterClassEx(&wce_main);
	//���������� ����� ��������� � ������� ������

}
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
			return MainOnCreate(hwnd);
			//��������� �� ���� 
	case WM_SIZE:
		return MainOnSize(hwnd, LOWORD(lParam), HIWORD(lParam));
	case WM_LBUTTONDOWN:
		return MainOnLButtonDown(hwnd, LOWORD(lParam), HIWORD(lParam));
	case WM_RBUTTONDOWN:

	case WM_MOUSEWHEEL:

		//��������� ��������
	case WM_KEYDOWN:

		// ������� �������� (��������� ���������)
	case WM_MOUSEMOVE:
		return MainOnMouseMove(hwnd, LOWORD(lParam), HIWORD(lParam), wParam);
		//����������� ���� � ���������� ������� 
	case WM_SYSCHAR:

		//ALT,SHIFT...
	case WM_PAINT:
		return MainOnPaint(hwnd);
		//����� ����� ���� 
	case WM_DESTROY:
		return MainOnDestroy(hwnd);
		//������������ ��� ��������� ��� ���������� ����
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
		//������������ ����� ��������� 

	}
	return 0L;
}
/*
������� ������� ���������
LRESULT => ������������� ��������, ������� ������������ � Windows
CALLBACK => ��� �������� ������ ������� � ������ �������
*/

BOOL MainOnDestroy(HWND hwnd)
{
	ReleaseDC(hwnd, hdc_main);
	PostQuitMessage(0);
	return TRUE;
}

