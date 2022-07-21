#include <windows.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

#include <gl\gl.h>
#include <gl\\glu.h>
#include "IntersactionTwoObject.ClassSphere.cpp"

using namespace std;
#pragma comment (linker, "/defaultlib:opengl32.lib")
#pragma comment (linker, "/defaultlib:glu32.lib")

extern HDC hdc_main;
extern HGLRC hglrcMain;
extern GLUquadricObj* g_pGluQuadObj;
extern HINSTANCE hinstance_application;
BOOL SetPixelFormat(HDC dc);




// установка формата пикселей
BOOL SetPixelFormat(HDC dc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cStencilBits = 0;
	pfd.cDepthBits = 24;
	pfd.cAccumBits = 0;
	pfd.iLayerType = PFD_MAIN_PLANE;
	int pf = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, pf, &pfd);
	return !(pfd.dwFlags & PFD_NEED_PALETTE);
}
//INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
//INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	static bool s_fInit;
//
//	switch (message)
//	{
//	case WM_INITDIALOG:
//	{
//		s_fInit = 1;
//		SetDlgItemReal(hDlg, IDC_SPHERE_X, length_beam);
//		SetDlgItemReal(hDlg, IDC_SPHERE_Y, width_beam);
//		SetDlgItemReal(hDlg, IDC_SPHERE_Z, hight_beam);
//		SetDlgItemReal(hDlg, IDC_TORUS_X, width_channel);
//		SetDlgItemReal(hDlg, IDC_TORUS_Y, hight_channel);
//		s_fInit = 0;
//
//
//	}
//	return (INT_PTR)TRUE;
//
//	case WM_COMMAND:
//	{
//
//		if (s_fInit == 1)
//			return 0;
//
//		GetDlgItemReal(hDlg, IDC_SPHERE_X, length_beam);
//		GetDlgItemReal(hDlg, IDC_SPHERE_Y, width_beam);
//		GetDlgItemReal(hDlg, IDC_SPHERE_Z, hight_beam);
//		GetDlgItemReal(hDlg, IDC_TORUS_X, length_beam);
//		GetDlgItemReal(hDlg, IDC_TORUS_Y, width_beam);
//		GetDlgItemReal(hDlg, IDC_TORUS_Z, hight_beam);
//		InvalidateRect(hwnd, nullptr, FALSE);
//
//	}
//	break;
//
//	case WM_CLOSE:
//		DestroyWindow(hwnd);
//		break;
//	}
//	return (INT_PTR)FALSE;
//}
BOOL MainOnCreate(HWND hwnd)
{
	//инициализация тора
	//инициализация сферы
	//определение пересечений
	// получить контекст окна
	//CreateDialog(hinstance_application, MAKEINTRESOURCE(IDD_DIALOG1),hwnd,DlgProc)
	//Sphere sphere = Sphere(0, 0, 0, 1);
	//vector<Point> vector = sphere.Initializing();
	
	// (значение дескриптора не меняется, т.к. класс окна имеет стиль CS_OWNDC)
	hdc_main = GetDC(hwnd);
	// установить формат пикселей
	SetPixelFormat(hdc_main);
	// создать контекст воспроизведения OpenGL, сделать его текущим
	hglrcMain = wglCreateContext(hdc_main);
	wglMakeCurrent(hdc_main, hglrcMain);
	// создать квадратичный объект OpenGL для рисования поверхностей
	g_pGluQuadObj = gluNewQuadric();
	assert(g_pGluQuadObj);
	return TRUE;

}
