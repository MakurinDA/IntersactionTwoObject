#include <windows.h>

#include <gl\gl.h>
#include <gl\\glu.h>

#pragma comment (linker, "/defaultlib:opengl32.lib")
#pragma comment (linker, "/defaultlib:glu32.lib")

float fAngViewX = 30,
fAngViewY = 45;

extern int stPosX, stPosY;

extern int g_wndW, g_wndH;
BOOL MainOnMouseMove(HWND hwnd_, int x, int y, UINT flags)
{
	if (!((MK_LBUTTON | MK_RBUTTON) & flags))
		return FALSE;

	if (MK_LBUTTON == flags)
	{
		float fDAng = 180.0f * (x - stPosX) / g_wndW;
		fAngViewY += fDAng;
		if (fAngViewY > 360.0f)
			fAngViewY -= 360.0f;
		if (fAngViewY < -360.0f)
			fAngViewY += 360.0f;
		fDAng = 180.0f * (y - stPosY) / g_wndH;
		fAngViewX += fDAng;
		if (fAngViewX > 360.0f)
			fAngViewX -= 360.0f;
		if (fAngViewX < -360.0f)
			fAngViewX += 360.0f;
		stPosX = x;
		stPosY = y;
	}
	else
	{
		stPosX = x;
		stPosY = y;
	}
	InvalidateRect(hwnd_, NULL, FALSE);
	return TRUE;
}