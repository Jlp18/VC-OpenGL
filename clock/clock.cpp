#include <gl/glut.h>
#include <gl/GLU.h>
#include <gl/GL.h>
#include <iostream>
#include <Windows.h>
#include <math.h>
using namespace std;

const int Width = 600 ,Height = 600;
const GLfloat PI = 3.141592653f;

float h = 0.0f;
float m = 0.0f;
float s = 0.0f;




int x_start = 0 , y_start = 0 , x_end = 500 , y_end = 500; //直线两端
int r = 100; //圆心及半径


void MidPointLine(int x0 , int y0 , int x1 , int y1)  //中点画直线
{
		int a , b , d1 , d2 , d , x , y;
		float m;
		if(x1 < x0)
		{
			d = x0 , x0 = x1 , x1 = d;
			d = y0 , y0 = y1 , y1 = d;
		}
		a = y0 - y1;
		b = x1 - x0;
		if(b == 0)
		{
			m = -1 * a * 100;
		}
		else
		{
			m = (float)a / (x0 - x1);
		}
		x = x0;
		y = y0;
		glVertex2i(x , y);
		
		if(m >= 0 && m <= 1)
		{
			d = 2 * a + b;
			d1 = 2 * a;
			d2 = 2 * (a + b);
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

		else if (m <= 0 && m >= -1)
		{
			d = 2 * a - b;
			d1 = 2 * a - 2 * b;
			d2 = 2 * a;
			while(x < x1)
			{
				if(d > 0)
				{
					x++;
					y--;
					d += d1;
				}
				else
				{
					x++;
					d += d2;
				}
				glVertex2i(x , y);
			}
		}

		else if (m > 1)
		{
			d = a + 2 * b;
			d1 = 2 * (a + b);
			d2 = 2 * b;
			while (y < y1)
			{
				if (d > 0)
				{
					x++;
					y++;
					d += d1;
				}
				else
				{
					y++;
					d += d2;
				}
				glVertex2i(x , y);
			}
		}

		else
		{
			d = a - 2 * b;
			d1 = -2 * b;
			d2 = 2 * (a - b);
			while(y > y1)
			{
				if(d <= 0)
				{
					x++;
					y--;
					d += d2;
				}
				else
				{
					y--;
					d += d1;
				}
				glVertex2i(x , y);
			}
		}
}

void MidCricle(int x0 , int y0 , int r)    //中点画圆
{
	int x , y;
	float d;
	x = 0;
	y = r;
	d = 1.25 - r;
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2i(x + x0 , y + y0);
	while(x < y)
	{
		if(d < 0)
		{
			d +=2*x+3;
		}
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		glVertex2i(x + x0 , y + y0);
		glVertex2i(y + y0 , x + x0);
		glVertex2i(-x + x0 , y + y0);
		glVertex2i(y + y0 , -x + x0);
		glVertex2i(x + x0 , -y + y0);
		glVertex2i(-y + y0 , x + x0);
		glVertex2i(-x + x0 , -y + y0);
		glVertex2i(-y + y0 , -x + x0);
	}

}

void Clock_node(int r)
{
	int lines = 60;
	float ship1 = 10;
	float ship2 = 5;
	for(int i = 0;  i<lines; i++)
	{
		if (i == 0)
		{
			glLineWidth(5);
			//glColor3f(1.0 , 0.0 , 0.0);
			glBegin(GL_LINES);

			glVertex2f(Width/2 , Height/2 + (r - ship1));
			glVertex2f(Width/2 , Height/2 + r);
			glEnd();
		}
		if(i % 5 == 0)   //粗时间点
		{
			glLineWidth(5);
			glBegin(GL_LINES);
			glVertex2f(Width/2 + (r - ship1)*sin(2 * PI / lines * i) , Height/2 + (r - ship1)*cos(2 * PI / lines * i));
			glVertex2f(Width/2 + r*sin(2 * PI /lines * i) , Height/2 + r*cos(2 * PI /lines * i));
			glEnd();
		}
		else    //细时间点 
		{
			glLineWidth(2);
			glBegin(GL_LINES);
			glVertex2f(Width/2 + (r - ship2)*sin(2 * PI / lines * i) , Height/2 + (r - ship2)*cos(2 * PI / lines * i));
			glVertex2f(Width/2 + r*sin(2 * PI /lines * i) , Height/2 + r*cos(2 * PI /lines * i));
			glEnd();
		}
	}
	glBegin(GL_POLYGON);
		for(int i = 0 ; i < 100 ; i++)
		{
			glVertex2i(Width/2 + 5 * cos(2 * PI / 100 * i) , Height/2 + 5 * sin(2 * PI / 100 * i));
		}
	glEnd();

	int h_pointer_len = r - 3 * ship1;
	int m_pointer_len = r - ship1;
	int s_pointer_len = r - ship1 + 2 * ship1;

	float s_Angle = s / 60.0;
	float m_Angle = (m * 60 + s) / 3600.0;
	float h2 = h >= 12 ? (h - 12) : h;
	float h_Angle = (h2 * 60 * 60 + m *60 + s) / (12 * 60 * 60);

	glLineWidth(1);  //秒针粗细
	glBegin(GL_LINES);
	MidPointLine(Width/2 - 2 * ship1 * sin(2 * PI * s_Angle) , Height/2 - 2 * ship1 * cos(2 * PI * s_Angle) , Width/2 + (r - ship2) * sin(2 * PI * s_Angle) , Height/2 + (r - ship2) * cos(2 * PI * s_Angle));
	//glVertex2f(Width/2 - 2 * ship1 * sin(2 * PI * s_Angle) , Height/2 - 2 * ship1 * cos(2 * PI * s_Angle));
	//glVertex2f(Width/2 + (r - ship2) * sin(2 * PI * s_Angle) , Height/2 + (r - ship2) * cos(2 * PI * s_Angle));
	glEnd();

	glLineWidth(3);  //分针粗细
	glBegin(GL_LINES);
	glVertex2f(Width/2 , Height/2);
	glVertex2f(Width/2 + m_pointer_len * sin(2 * PI * m_Angle) , Height/2 + m_pointer_len * cos(2 * PI * m_Angle));
	glEnd();

	glLineWidth(5);  //时针粗细
	glBegin(GL_LINES);
	glVertex2f(Width/2 , Height/2);
	glVertex2f(Width/2 + h_pointer_len * sin(2 * PI * h_Angle) , Height/2 + h_pointer_len * cos(2 * PI * h_Angle));
	glEnd();


	glFlush();
}

/*
  回调函数
*/
void timerFunc(int value)
{
	s += 1;
	int carry1 = 0;
	if(s >= 60)
	{
		s = 0;
		carry1 = 1;
	}
	m += carry1;
	int carry2 = 0;
	if(m >= 60)
	{
		m = 0;
		carry2 = 1;
	}
	h += carry2;
	if(h >= 24)
	{
		h = 0;
	}

	//重画
	glutPostRedisplay();

	//定时器，每秒执行一次timerFunc
	glutTimerFunc(1000 , timerFunc , 1);
}

void lineSegment()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0 , 0.0 , 0.0);
	//glViewport(0 , 0 , 800 , 800);
	//glBegin(GL_POINTS);
	//MidPointLine(x_start , y_start , x_end , y_end);
	MidCricle(Width/2 , Height/2 , r);
	glBegin(GL_LINES);
	Clock_node(r);
	glEnd();
	glFlush();
}


/*void cricleSegment()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0 , 0.0 , 0.0);
	glBegin(GL_POINTS);
	MidCricle(r);
	glEnd();
	glFlush();
}*/

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);  
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50 , 100);
	glutInitWindowSize(Width , Height);
	glutCreateWindow("My Clock");
	glClearColor(1.0 , 1.0 , 1.0 , 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0 , 500.0 , 0.0 , 500.0);

	//获取系统当前时间
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	h = sys.wHour;
	m = sys.wMinute;
	s = sys.wSecond;

	glutDisplayFunc(lineSegment);
	glutTimerFunc(1000 , timerFunc , 1);
	glutMainLoop();
	return 0;
}


