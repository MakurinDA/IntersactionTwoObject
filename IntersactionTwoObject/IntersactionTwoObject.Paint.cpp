#include <windows.h>
#include <math.h>

#include <gl\gl.h>
#include <gl\\glu.h>
#include "IntersactionTwoObject.ClassTorus.cpp"
#include "IntersactionTwoObject.ClassSphere.cpp"



#pragma comment (linker, "/defaultlib:opengl32.lib")
#pragma comment (linker, "/defaultlib:glu32.lib")

extern HDC hdc_main;
extern GLUquadricObj* g_pGluQuadObj;
extern float fAngViewX, fAngViewY;
void Draw(HDC hdc);
void DrawSphere(double r);
void DrawTor(double, double, int);
void SetLight();





BOOL MainOnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	Draw(hdc_main);
	EndPaint(hwnd, &ps);
	return TRUE;
}
void Draw(HDC hdc)
{
	//Устанавливает фон 
	glClearColor(0.2, 0.2, 0.2, 0);
	//Очищает буферы
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Заменяет текущую матрицу на матрицу идентификаторов
	glLoadIdentity();
	//Включаем режим освещения
	glEnable(GL_LIGHTING);
	//Устанавливаем освещение
	SetLight();
	// матрицы поворота отностительно осей X и Y
	glRotatef(fAngViewX, 1.0f, 0.0f, 0.0f);
	glRotatef(fAngViewY, 0.0f, 1.0f, 0.0f);
	glRotatef(1, 0.0f, 0.0f, 1.0f);
	//Толщина линии
	glLineWidth(1.0f);
	//Режим отображения фигуры
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	//Устанавливает текстуру фигуры
	float sphere_mat[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sphere_mat);

	glPushMatrix();
	//glTranslated(, , );
	Sphere sphere = Sphere(0,0,0,5);
	sphere.Draw();
	
	glPopMatrix();

	float torus_mat[] = { 0.0f, 1.0f, 1.0f, 0.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, torus_mat);

	glPushMatrix();
	//glTranslated(, , );
	Torus torus = Torus(0, 0, 0, 8, 2, 32);
	torus.Draw();
	glPopMatrix();

	glDisable(GL_LIGHTING);
	glFinish();
	SwapBuffers(hdc);

}
void SetLight()
{
	GLfloat lightPos[] = { -1.0, 1.0, 1.0, 0.0 };
	GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	glEnable(GL_LIGHT0);
}

