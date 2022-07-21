#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <assert.h>


#include <gl\gl.h>
#include <gl\\glu.h>

#pragma comment (linker, "/defaultlib:opengl32.lib")
#pragma comment (linker, "/defaultlib:glu32.lib")

using namespace std;

HGLRC hglrcMain;
GLUquadricObj* g_pGluQuadObj = NULL;

extern HDC hdc_main;









