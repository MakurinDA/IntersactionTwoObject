#include <windows.h>
#include <math.h>
#include <vector>

#include <gl\gl.h>
#include <gl\\glu.h>
#include "IntersactionTwoObject.ClassSphere.cpp"

using namespace std;
extern HDC hdc_main;
extern GLUquadricObj* g_pGluQuadObj;
class IntersactionObjects
{
private:
	
struct C3dVector
{
	double x, y, z;
};


public :
vector<Point> vector_points;
	vector<Point>  Intersection(vector<Point> vector1, vector<Point> vector2)
	{
		Point intermediate_point;
		double tochnost = 0.2;
		for (int i = 0; i < vector1.size(); i++)
			for (int j = 0; j < vector2.size(); j++)
			{

				if ((abs(vector1[i].x - vector2[j].x) < tochnost) && (abs(vector1[i].y - vector2[j].y) < tochnost) && (abs(vector1[i].z - vector2[j].z) < tochnost))
				{
					intermediate_point.x = vector2[j].x;
					intermediate_point.y = vector2[j].y;
					intermediate_point.z = vector2[j].z;
					vector_points.insert(vector_points.end(), intermediate_point);
				}

			}
		return vector_points;
	}
	void Draw(vector<Point> vector_points)
	{
		//Point intermediate_point;

		for (int i = 0; i < vector_points.size(); i++)
		{
			glPushMatrix();
			glTranslated(vector_points[i].x, vector_points[i].y, vector_points[i].z);
		//	Sphere sphere2 = Sphere(0,0,0,2);
			//sphere2.Draw();
			//n++;
			gluSphere(g_pGluQuadObj, 0.2, 16, 16);
			//	DrawSphere(0.2);
			glPopMatrix();

		}
		
	}
	IntersactionObjects()
	{
	}
};