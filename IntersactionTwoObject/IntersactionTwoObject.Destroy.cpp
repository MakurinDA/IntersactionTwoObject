#include <windows.h>

#include <gl\gl.h>
#include <gl\\glu.h>

#pragma comment (linker, "/defaultlib:opengl32.lib")
#pragma comment (linker, "/defaultlib:glu32.lib")

extern GLUquadricObj* g_pGluQuadObj ;
extern HGLRC hglrcMain; 

void MainOnDestroy(HWND hwnd)
{
	if (g_pGluQuadObj)
	{
		gluDeleteQuadric(g_pGluQuadObj);
		g_pGluQuadObj = nullptr;
	}
	// удалить контекст воспроизведения OpenGL
	wglMakeCurrent(NULL, NULL);
	if (hglrcMain)
		wglDeleteContext(hglrcMain);
	PostQuitMessage(0);
}