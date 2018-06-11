#include <GL/glut.h>
#include <math.h>
#include <iostream>
#define MAX_NUM_POINTS 4
class point{
public:
	point(float s=0, float t=0) :x(s), y(t){}
	float x, y;
};
static GLint width = 500, height = 500;

static int n = 0;
point *P;
void  init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -1.0, 10);
	glMatrixMode(GL_MODELVIEW);
	// Set the clear color to black
	glClearColor(0.0, 0.0, 0.0, 0.0); //black

	P = new point[MAX_NUM_POINTS];
	//n = 3;
}
long Fac(int n)//阶乘函数
{
	int f;
	if (0 == n || 1 == n)
		f = 1;
	else
		f = n*Fac(n - 1);
	return f;
}
float C(const int &n, const int &i)//Bernstein第一项
{
	return (float)Fac(n) / (Fac(i)*Fac(n - i));
}

void drawPoint()
{
	glColor3f(0.0, 1.0, 0.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(P[i].x, P[i].y);
		std::cout << P[i].x << " ";
		std::cout << P[i].y << std::endl;
	}
	glEnd();

}
//Draw a cube curce using Bernstein polynomials 
void drawBezier()
{
	std::cout << "Bernstein polynomials\n";
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);  //lines between two points
	for (float t = 0.0; t <= 1.0; t += 0.01)
	{
		float x = 0, y = 0;
		for (int i = 0; i < n ; i++)
		{
			x += P[i].x*C(n-1, i)*pow(t, i)*pow(1 - t, n-1 - i);
			y += P[i].y*C(n-1, i)*pow(t, i)*pow(1 - t, n-1 - i);
			//std::cout << "x-y:" << x << " " << y << std::endl;
		}
		glVertex2f(x, y);
	}
	glEnd();
	glFlush();
}
// Draw a cubic Beizer curve using de Casteljau recursion
void drawBeizer_de()
{
	std::cout << "De Casteljau\n";
	point pp[MAX_NUM_POINTS][4];
	for (int k = 0; k < n; k++)
	{
		pp[k][0] = P[k];
	}
	glColor3f(1.0, 1.0, 0.0);

	glBegin(GL_LINE_STRIP);  //lines between two points
	for (float t = 0.0; t < 1.0; t+=0.01)
	{ 
		for (int r = 1; r < n ; r++)//de Casteljau recursion
		{
			for (int i = 0; i < n - r; i++)
			{
				pp[i][r].x = (1 - t)*pp[i][r - 1].x + t*pp[i + 1][r - 1].x;
				pp[i][r].y = (1 - t)*pp[i][r - 1].y + t*pp[i + 1][r - 1].y;
			}
		}
		glVertex2f(pp[0][n-1].x, pp[0][n-1].y);
	}
	glEnd();
	glFlush();
}
//OpenGL draw a curve
void drawCurves()
{
	std::cout << "OpenGL\n";
	GLfloat ctrPoint[4][3];  //  4 cotrol points
	for (int i = 0; i < 4; i++)
	{ 
		ctrPoint[i][0] = P[i].x;
		ctrPoint[i][1] = P[i].y;
		ctrPoint[i][2] = 0.0;
	}
	glMap1f(GL_MAP1_VERTEX_3, //生成的数据类型
		0.0,    //t值的下界
		100.0,  //t值的上界
		3,      //顶点在数据中的间隔，x,y,z所以间隔是3
		4,      //t方向上的阶，即控制点的个数
		&ctrPoint[0][0]);  //指向控制点数据的指针
	//必须在绘制顶点之前开启
	glEnable(GL_MAP1_VERTEX_3);
	//使用画线的方式来连接点
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	int i;
	for (i = 0; i< 100; i ++)
	{
		glEvalCoord1f((GLfloat)i);
	}
	glEnd();
	glFlush();
}

void  display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawPoint(); // draw control points
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-9.5, -9.5);
	glVertex2f(9.5, -9.5);
	glVertex2f(9.5, 9.5);
	glVertex2f(-9.5, 9.5);
	glEnd();
	glFlush();
}
void mouse(int button, int state, int x, int y)
{
	float wx, wy;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		/* Translate screen coordinate system to view coordinate system */
		wx = (20.0 * (x - 250)) / (float)(width);
		wy = (20.0 * (height/2 - y)) / (float)(height);
		/* See if we have room for any more control points */
		if (n == MAX_NUM_POINTS) return;
		/* Save the point */
		P[n].x = wx;
		P[n].y = wy;
		std::cout <<"x-y:"<< x << " "<<y<<std::endl;
		
		std::cout << P[n].x <<" ";
		std::cout << P[n].y << std::endl;
		n++;
		/* Draw the point */
		glColor3f(0.0, 1.0, 0.0);
		glPointSize(5.0);
		glBegin(GL_POINTS);
		glVertex3f(wx, wy, 0.0);
		glEnd();
		glFlush();
	}
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
	case 'Q':
		exit(0);
		break;
	case 'c':
	case 'C':   //redraw
		n = 0;
		glutPostRedisplay();
		break;
	case 'e':
	case 'E':  //erase curve
		glutPostRedisplay();
		break;
	}
}
void processMenu(int value)
{
	switch (value)
	{
	case 1:
		drawBezier();
		break;
	case 2:
		drawBeizer_de();
		break;
	case 3:
		drawCurves();
		break;
	}
	//glutPostRedisplay();
}
void reshape(int w, int h)
{
	width = w; height = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-10.0, 10.0, -10.0*(GLfloat)h / (GLfloat)w,
		10.0*(GLfloat)h / (GLfloat)w, -1.0, 10.0);
	else
		glOrtho(-10.0*(GLfloat)w / (GLfloat)h,
		10.0*(GLfloat)w / (GLfloat)h, -10.0, 10.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}
int  main(int  argc, char  **argv)
{
	glutInit(&argc, argv);    // Initialize GLUT function callings
	//sets the initial display mode
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// Set window position, from the left and top corner of the screen, in numbers of pixels 
	glutInitWindowPosition(200, 100);

	// Set window size (width, height) in number of pixels     
	glutInitWindowSize(500, 500);

	// Specify a window creation event 
	glutCreateWindow("Bezier Curve");

	int nModeMenu = glutCreateMenu(processMenu);
	glutAddMenuEntry("Draw by Bernstein polynomials", 1);
	glutAddMenuEntry("Draw by De Casteljau recursion", 2);
	glutAddMenuEntry("Draw By OpenGL", 3);
	//将菜单榜定到鼠标右键上  
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	//A window is reshaped
	glutReshapeFunc(reshape);

	// Specify the drawing function that is called when the window 
	glutDisplayFunc(display);         // is created or re-drew

	init();	    // Invoke this function for initialization	
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMainLoop();    // Enter the event processing loop

	return 0;          // Indicate normal termination 		
}
