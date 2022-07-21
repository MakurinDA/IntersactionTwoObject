#include <windows.h>

#include <gl\gl.h>
#include <gl\\glu.h>

#pragma comment (linker, "/defaultlib:opengl32.lib")
#pragma comment (linker, "/defaultlib:glu32.lib")

int stPosX, stPosY;

BOOL MainOnLButtonDown(HWND hwnd, int x, int y)
{
	stPosX = x;
	stPosY = y;
	return TRUE;
}