#include <windows.h>
#include <math.h>

#include <gl\gl.h>
#include <gl\\glu.h>
#include "IntersactionTwoObject.ClassTorus.cpp"




#pragma comment (linker, "/defaultlib:opengl32.lib")
#pragma comment (linker, "/defaultlib:glu32.lib")

extern HDC hdc_main;
extern GLUquadricObj* g_pGluQuadObj;
extern float fAngViewX, fAngViewY;
extern Sphere sphere;
extern Torus torus;
extern IntersactionObjects intersactionObjects;
extern vector<Point> vector_points;
void Draw(HDC hdc);
void DrawSphere(double r);
void DrawTor(double, double, int);
void SetLight();
extern double x_sphere, y_sphere, z_sphere;
extern double x_torus, y_torus, z_torus;




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

	//������������� ��� 
	glClearColor(0.2, 0.2, 0.2, 0);
	//������� ������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//�������� ������� ������� �� ������� ���������������
	glLoadIdentity();
	//�������� ����� ���������
	glEnable(GL_LIGHTING);
	//������������� ���������
	SetLight();
	// ������� �������� ������������� ���� X � Y
	glRotatef(fAngViewX, 1.0f, 0.0f, 0.0f);
	glRotatef(fAngViewY, 0.0f, 1.0f, 0.0f);
	glRotatef(1, 0.0f, 0.0f, 1.0f);
	//������� �����
	glLineWidth(1.0f);
	//����� ����������� ������
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	//������������� �������� ������
	float sphere_mat[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sphere_mat);
	sphere.Draw();

	float torus_mat[] = { 0.0f, 1.0f, 1.0f, 0.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, torus_mat);
	torus.Draw();

	float intersaction_mat[] = { 1.0f, 0.0f, 0.0f, 0.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, intersaction_mat);
	intersactionObjects.Draw(intersactionObjects.vector_points);

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

