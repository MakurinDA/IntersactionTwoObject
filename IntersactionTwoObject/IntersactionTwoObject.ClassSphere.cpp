#include <windows.h>
#include <math.h>
#include <vector>
#include <gl\gl.h>
#include <gl\\glu.h>
using namespace std;


struct Point
{
	double x;
	double y;
	double z;
};
extern HDC hdc_main;
extern GLUquadricObj* g_pGluQuadObj;
class Sphere
{
private:
	double x0 = 0, y0 = 0, z0 = 0;
	double R = 1;

	vector<Point> vector_points;
#define PI    3.14159265
public:
	vector<Point> Initializing()
	{
		int chastota = 10;
		Point intermediate_point;
		double x, y, z;
		int level_of_detail = 5;
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

			return vector_points;
		}
	}
	void Draw()
	{
		gluSphere(g_pGluQuadObj, R, 32, 32);
	}
	//void SetX(double x00)
	//{
	//}

	Sphere(double x0, double y0, double z0, double R)
	{
		x0 = x0;
		y0 = y0;
		z0 = z0;
		R = R;



	}
};