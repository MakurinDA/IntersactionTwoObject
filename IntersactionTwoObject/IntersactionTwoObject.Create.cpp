#include <windows.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

#include <gl\gl.h>
#include <gl\\glu.h>
#include "resource.h"

#include "IntersactionTwoObject.ClassTorus.cpp"
#include <tchar.h>

using namespace std;
#pragma comment (linker, "/defaultlib:opengl32.lib")
#pragma comment (linker, "/defaultlib:glu32.lib")

extern HDC hdc_main;
extern HGLRC hglrcMain;
extern GLUquadricObj* g_pGluQuadObj;
extern HINSTANCE hinstance_application;
extern HWND hwnd_window;
LRESULT CALLBACK MainWindowProc(HWND, UINT, WPARAM, LPARAM);
BOOL SetPixelFormat(HDC dc);
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

Sphere sphere = Sphere(0, 0, 0, 5);
Torus torus = Torus(0, 4, 0, 6,1, 32);
//IntersactionObjects intersactionObjects;
double x_sphere=0, y_sphere=0, z_sphere=0;
double x_torus=0, y_torus=0, z_torus=0;
IntersactionObjects intersactionObjects = IntersactionObjects();

vector<Point> vector_points;


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
bool GetDlgItemReal(HWND, int, double&);
bool GetDlgItemReal(HWND hDlg, int id, double& val)
{
	TCHAR buff[512];
	GetDlgItemText(hDlg, id, buff, _countof(buff));

	LPTSTR err = nullptr;
	val = _tcstod(buff, &err);
	return nullptr == err;
}
void SetDlgItemReal(HWND hDlg, int id, double val)
{
	TCHAR buff[256];
	_stprintf_s(buff, _T("%g"), val);
	SetDlgItemText(hDlg, id, buff);
}

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static bool s_fInit;

	switch (message)
	{
	case WM_INITDIALOG:
	{
		s_fInit = 1;
		SetDlgItemReal(hDlg, IDC_SPHERE_X, x_sphere);
		SetDlgItemReal(hDlg, IDC_SPHERE_X, x_sphere);
		SetDlgItemReal(hDlg, IDC_SPHERE_Y, y_sphere);
		SetDlgItemReal(hDlg, IDC_SPHERE_Z, z_sphere);
		SetDlgItemReal(hDlg, IDC_TORUS_X, x_torus);
		SetDlgItemReal(hDlg, IDC_TORUS_Y, y_torus);
		SetDlgItemReal(hDlg, IDC_TORUS_Z, z_torus);

		s_fInit = 0;
		break;
	}
	//return (INT_PTR)TRUE;


	case WM_COMMAND:
	{

		if (s_fInit == 1)
		//	return 0;
			GetDlgItemReal(hDlg, IDC_SPHERE_X, x_sphere);
		GetDlgItemReal(hDlg, IDC_SPHERE_X, x_sphere);
		GetDlgItemReal(hDlg, IDC_SPHERE_Y, y_sphere);
		GetDlgItemReal(hDlg, IDC_SPHERE_Z, z_sphere);
		GetDlgItemReal(hDlg, IDC_TORUS_X, x_torus);
		GetDlgItemReal(hDlg, IDC_TORUS_Y, y_torus);
		GetDlgItemReal(hDlg, IDC_TORUS_Z, z_torus);
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_UPDATE_YU:
		{

			sphere.SetX(x_sphere);
			sphere.SetY(y_sphere);
			sphere.SetZ(z_sphere);

			torus.SetX(x_torus);
			torus.SetY(y_torus);
			torus.SetZ(z_torus);

			intersactionObjects.vector_points.clear();
			sphere.vector_points.clear();
			torus.vector_points.clear();
			intersactionObjects.vector_points = intersactionObjects.Intersection(sphere.Initializing(), torus.Initializing());
			InvalidateRect(hwnd_window, NULL, TRUE);
			break;
		}
		}
		InvalidateRect(hwnd_window, nullptr, FALSE);
		break;
	}

		
	case WM_CLOSE:
		DestroyWindow(hwnd_window);
		break;
	}
	return (INT_PTR)FALSE;
}
BOOL MainOnCreate(HWND hwnd)
{
	//инициализация тора
	//инициализация сферы
	//определение пересечений
	// получить контекст окна
	//CreateDialog(hinstance_application, MAKEINTRESOURCE(IDD_DIALOG1),hwnd,DlgProc)
	//Sphere sphere = Sphere(0, 0, 0, 1);
	//vector<Point> vector = sphere.Initializing();
	// 
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


	CreateDialog(hinstance_application, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DlgProc);
	//vector_points = intersactionObjects.Intersection(sphere.Initializing(), torus.Initializing());
	//intersactionObjects.vector_points = intersactionObjects.Intersection(sphere.Initializing(), torus.Initializing());
	return TRUE;

}
