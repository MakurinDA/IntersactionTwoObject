#include <windows.h>
#include <math.h>

#include <gl\gl.h>
#include <gl\\glu.h>

struct C3dVector
{
	double x, y, z;
};

class Torus
{
private:
	double x0, y0, z0, r_max, r_min, n;
#define PI    3.14159265
public:
	void Draw()
	{
		/*----------------------*/
 /* нарисовать тор       */
 /*----------------------*/
		GLfloat         x1, x2, x3, x4,
			y1, y2, y3, y4,
			z1, z2, z3, z4, xn, yn, zn,
			fi, fi_max, dr, dr1, DFI, ln;

		C3dVector  v1, v2, v3, v12, v13, vn[10];

		int  i;

		glFrontFace(GL_CCW);

		DFI = 2 * PI / n;

		glBegin(GL_QUADS);

		for (fi_max = -PI; fi_max < PI; fi_max += DFI)
		{
			for (fi = -PI; fi < PI; fi += DFI)
			{
				dr = r_min * cos(fi);
				dr1 = r_min * cos(fi + DFI);

				x1 = (r_max + dr) * cos(fi_max);      x2 = (r_max + dr1) * cos(fi_max);
				x3 = (r_max + dr1) * cos(fi_max + DFI);  x4 = (r_max + dr) * cos(fi_max + DFI);

				y1 = (r_max + dr) * sin(fi_max);      y2 = (r_max + dr1) * sin(fi_max);
				y3 = (r_max + dr1) * sin(fi_max + DFI);  y4 = (r_max + dr) * sin(fi_max + DFI);

				z1 = r_min * sin(fi);    z2 = r_min * sin(fi + DFI);
				z3 = z2;               z4 = z1;


				/*
				v1.x=x1;   v1.y=y1 ; v1.z=z1;
				v2.x=x2;   v2.y=y2 ; v2.z=z2;
				v3.x=x3;   v3.y=y3 ; v3.z=z3;

				v13= v1 - v3;
				v12= v1 - v2;
				vn = v12 ^ v13;
				*/

				vn[0].x = x1; vn[0].y = y1; vn[0].z = z1;
				vn[1].x = x2; vn[1].y = y2; vn[1].z = z2;
				vn[2].x = x3; vn[2].y = y3; vn[2].z = z3;
				vn[3].x = x4; vn[3].y = y4; vn[3].z = z4;

				for (i = 0; i < 4; i++)
				{
					ln = sqrt(vn[i].x * vn[i].x + vn[i].y * vn[i].y);

					xn = vn[i].x - r_max * (vn[i].x / ln);
					yn = vn[i].y - r_max * (vn[i].y / ln);
					zn = vn[i].z;

					glNormal3f(xn, yn, zn);

					glVertex3f(vn[i].x, vn[i].y, vn[i].z);
				}

				//glNormal3f(vn.x, vn.y , vn.z );

				/*
				glVertex3f(x1, y1, z1);
				glVertex3f(x2, y2, z2);
				glVertex3f(x3, y3, z3);
				glVertex3f(x4, y4, z4);
				*/

			}
		}
		glEnd();


		glFrontFace(GL_CW);

	}
	Torus(double x00, double y00, double z00, double Rmax, double Rmin, int n0)
	{
		x0 = x00;
		y0 = y00;
		z0 = z00;
		r_max = Rmax;
		r_min = Rmin;
		n = n0;

	}
};