#include <windows.h>

#include <gl\gl.h>
#include <gl\\glu.h>

#pragma comment (linker, "/defaultlib:opengl32.lib")
#pragma comment (linker, "/defaultlib:glu32.lib")


void Init(int, int);
//ќбласть отсечени€
RECT rcClip;
int g_wndW, g_wndH;

void Init(int ww, int wh)
{
	glFrontFace(GL_CW);
	//glEnable (GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// определить область отсечени€
	int viewportSize = ww / 2;
	rcClip.left = ww / 2 - ww / 4;
	rcClip.bottom = wh / 2 + viewportSize / 2;

	rcClip.right = rcClip.left + viewportSize;
	rcClip.top = rcClip.bottom - viewportSize;

	glViewport(rcClip.left, rcClip.top,
		viewportSize, viewportSize);
	double Ortho = 10;
	glOrtho(-Ortho, Ortho, -Ortho, Ortho, -Ortho, Ortho);

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


BOOL MainOnSize(HWND hwnd, int g_wndW_, int g_wndH_)
{
	g_wndW = g_wndW_;
	g_wndH = g_wndH_;
	Init(g_wndW, g_wndH);
	return TRUE;
}