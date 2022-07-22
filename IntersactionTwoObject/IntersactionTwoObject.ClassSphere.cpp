#include <windows.h>
#include <math.h>
#include <vector>
#include <gl\gl.h>
#include <gl\\glu.h>
#include "IntersactionTwoObject.StructPoint.cpp"

using namespace std;



extern HDC hdc_main;
extern GLUquadricObj* g_pGluQuadObj;
class Sphere
{
private:
	double x0 , y0 , z0 ;
	double R;



#define PI    3.14159265
public:
	void SetX(double X)
	{
		x0 = X;
	}
	void SetY(double Y)
	{
		y0 = Y;
	}
	void SetZ(double Z)
	{
		z0 = Z;
	}

	vector<Point> vector_points;
	vector<Point> Initializing()
	{
		int chastota = 10;
		Point intermediate_point;
		double x, y, z;
		int level_of_detail = 4;
		for (int i = -chastota * level_of_detail; i < chastota * level_of_detail; i++)
		{
			for (int j = -chastota * level_of_detail; j < chastota * level_of_detail; j++)
			{
				x = i;
				y = j;
				x /= (level_of_detail * 2);
				y /= (level_of_detail * 2);
				z = sqrt(-pow(x, 2) - pow(y, 2) + pow(R, 2));



				intermediate_point.x = x + x0;
				intermediate_point.y = y + y0;
				intermediate_point.z = z + z0;



				//if (z !=0)
				vector_points.insert(vector_points.end(), intermediate_point);

				intermediate_point.z = -z + z0;
				////	if (z != 0)
				vector_points.insert(vector_points.end(), intermediate_point);
			}

		}
			return vector_points;
	}
	void Draw()
	{
		glPushMatrix();
		glTranslated(x0,y0,z0);
		gluSphere(g_pGluQuadObj, R, 32, 32);
		glPopMatrix();
	}

	//void SetX(double x00)
	//{
	//}

	Sphere(double x00, double y00, double z00, double R0)
	{
		x0 = x00;
		y0 = y00;
		z0 = z00;
		R = R0;

	}
};