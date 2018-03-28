#include "stdafx.h"
#include <iostream>
#include <GL/gl>
#include <GL/glut>
#include <math.h>
using namespace std;

int x_start = 0 , y_start = 0 , x_end = 2 , y_end = 2;

void MidPointLine(int x0 , int y0 , int x1 , int y1)
{
	if((x0 != x1) && (y0 != y1))
	{
		int a , b , d1 , d2 , d , x , y;
		a = y0 - y1;
		b = x1 - x0;
		d = 2 * a + b;
		d1 = 2 * a;
		d2 = 2 *(a + b);
		x = x0;
		y = y0;
		glVertex2i(x , y);
		while(x < x1)
		{
			if(d < 0)
			{
				x++;
				y++;
				d += d2;
			}
			else
			{
				x++;
				d += d1;
			}
			glVertex2i(x , y);
		}
	}
	else
	{
		int mid , d;
		if(x0 == x1)
		{
			int x = x0;
			int y;
			y = (y0 <= y1)?y0:y1;
			d = fabs((double)(y0 - y1));
			while(d <= 0)
			{
				glVertex2i(x , y);
				y++;
				d--;
			}
		}
	}
}

void lineSegment()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0 , 0.0 , 0.0);
	glBegin(GL_POINTS);
	MidPointLine(x_start , y_start , x_end , y_end);
	glEnd();
	glFlush();
}

void main()
{
	glutInit(&argc , argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50 , 100);
	glutInitWindowSize(500 , 500);
	glutCreateWindow("中点画线法");
	glClearColor(1.0 , 1.0 , 1.0 , 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0 , 500.0 , 0.0 , 500.0);
	glutDisplayFunc(lineSegment);
	glutMainLoop();
	return 0;
}

