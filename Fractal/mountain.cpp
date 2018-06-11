#include <gl/glut.h>
#include <stdlib.h>
#include <math.h>

GLfloat colors[][3] = { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.5, 0.8, 1.0 } };
GLdouble PI = 3.1415926;

void mountain()
{
	float x, y;
	int k;
	float d[4][6] = { { 0.5, 0.0, 0.0, 0.5, 0.0, 0.0 }, { 0.5, 0.0, 0.0, 0.5, 2.0, 0.0 }, { -0.4, 0.0, 1.0, 0.4, 0.0, 1.0 }, { -0.5, 0.0, 0.0, 0.5, 2.0, 1.0 } };

	x = 0;
	y = 0;
	for (long i = 0; i < 20000; i++)
	{
		k = rand() % 4;
		x = d[k][0] * x + d[k][1] * y + d[k][4];
		y = d[k][2] * x + d[k][3] * y + d[k][5];
		//pDC->SetPixel(200 - 100 * x / 2, 200 - 100 * y / 2, RGB(15, 123, 15));
		glPointSize(2);
		glBegin(GL_POINTS);
		glColor3f(0.02, 0.48, 0.05);
		glVertex2f(x*10, y*10);
		glEnd();
	}
}
float Gauss()
{
	int i;
	
	int NumRand = 5;
	int MAX = RAND_MAX;
	float GaussAdd = sqrt(float(3 * NumRand));
	float GaussFac = 2 * GaussAdd / (NumRand*MAX);

	float sum = 0;
	//srand(0);
	for (i = 0; i<NumRand; i++)
		sum = sum + rand();

	return (GaussFac*sum - GaussAdd);
}
/////////////////////////////////////////////////////////
// th -- the angle of trees
void tree(int n, float x0, float y0, float len, int th)
{
	float x1, y1, x2, y2, x3, y3;
	float scale;
	int th1, th2;
	float m_pzj = 30;

	scale = 0.70;
	th1 = m_pzj + 10 * Gauss();
	th2 = m_pzj + 10 * Gauss();

	if (n == 0) return;
	x1 = x0 + len*cos(th*PI / 180);
	y1 = y0 + len*sin(th*PI / 180);
	x2 = x1 + scale*len*cos((th + th1)*PI / 180);
	y2 = y1 + scale*len*sin((th + th1)*PI / 180);
	x3 = x1 + scale*len*cos((th - th2)*PI / 180);
	y3 = y1 + scale*len*sin((th - th2)*PI / 180);

	if (n < 4)
	{
		glColor3f(0.84, 0.02, 0.03);
		
	}
	
	if ( n >= 4 && n <= 8)
	{
		glColor3f(1.0, 0.8, 0.0);
		glLineWidth(3);
	}
		
	if (n > 8)
	{ 
		glColor3f(0.43, 0.28, 0.18);
		glLineWidth(5);
	}
	
	glBegin(GL_LINES);
		glVertex2f(x0*0.2, y0*0.2);
		glVertex2f(x1*0.2, y1*0.2);
		glVertex2f(x1*0.2, y1*0.2);
		glVertex2f(x2*0.2, y2*0.2);
		glVertex2f(x1*0.2, y1*0.2);
		glVertex2f(x3*0.2, y3*0.2);
	glEnd();

	tree(n - 1, x1, y1, scale*len, th + th1);
	tree(n - 1, x1, y1, scale*len, th - th2);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPushMatrix();
		glTranslatef(10.0, 10.0, 0.0);
		mountain();
		glScalef(0.45, 0.45, 0.0);
		tree(10, 50.0, 0.0, 50, 75);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(10.0, 10.0, 0.0);
		glScalef(0.3, 0.3, 0.0);
		tree(10, 10.0, 0.0, 50, 90);
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void resize(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 50.0, 0, 50.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Mountain& Tree");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);

	glutMainLoop();
	return 0;
}