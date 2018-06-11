#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;
#define N 6
int g_mousePosition[2] = { 0, 0 };
float g_centerRotate[] = { 0, 0, 0 };
bool g_leftMouseButtonDown = false;
GLUquadric *qObj;
GLuint theLeaf;
float R[N + 1], H[N + 1], k, p, q, m, alpha, z[N + 1], a = 6;

float Gauss(float min, float max)
{
	int a = rand(), b = rand(), c = rand(), d = rand();
	int x = a + b + c + d;
	double y = (x*sqrt(3.0)) / RAND_MAX - sqrt(12.0);
	double mid = (min + max) / 2;
	float z = (float)(mid + (max - mid)*y / (2 * sqrt(3.0)));
	return z;
}
void setData(void)
{
	R[N] = 0.3;
	H[N] = 2.4;
	z[N] = H[N];
	k = 0.5;
	p = 0.6;
	q = 0.5;
	m = 0.7;
	alpha = 45;
	for (int i = N - 1; i >= 0; i--)
	{
		R[i] = R[i + 1] * q;
		H[i] = H[i + 1] * m;
		z[i] = z[i + 1] * p;
	}
}
void init(void)
{
	GLfloat white_light[] = { 0, 1.0, 0, 1.0 };//{0.6, 0.6, 0.6, 1.0};
	GLfloat light_position[] = { 4, 4, 4, 0 };
	qObj = gluNewQuadric();
	glClearColor(0.6, 0.6, 0.6, 0.0);
	glClearDepth(1.0);
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
}

void drawTree(int n)
{
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.1, 0.15, 0.1, 1.0 };
	GLfloat specular[] = { 0.1, 0.1, 0.1, 1.0 };
	if (n == 0)
	{
		float h = Gauss(0.4, 0.7);
		gluCylinder(qObj, R[n], k*R[n], H[n] * h, 20, 20);
		glTranslatef(0, 0, H[n] * h);
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, 5);
		glRotatef(Gauss(10, 50), 1, 0, 0);
		glRotatef(45, 0, 1, 0);
		glRotatef(90, 1, 0, 0);
		glScalef(1, 1, 0.1);
		glutSolidCube(0.15);
		return;
	}
	else
	{
		gluCylinder(qObj, R[n], k*R[n], H[n], 20, 20);

		glTranslatef(0, 0, H[n]);
		glPushMatrix();
		glTranslatef(0, 0, -H[n] * Gauss(0.0, 0.4));
		glRotatef(Gauss(30, 80), 0, 0, 1);
		glRotatef(Gauss(40, 70), 0, 1, 0);
		drawTree(n - 1);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0, 0, -H[n] * Gauss(0.0, 0.4));
		glRotatef(Gauss(140, 200), 0, 0, 1);
		glRotatef(Gauss(40, 70), 0, 1, 0);
		drawTree(n - 1);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0, 0, -H[n] * Gauss(0.0, 0.4));
		glRotatef(Gauss(260, 320), 0, 0, 1);
		glRotatef(Gauss(40, 70), 0, 1, 0);
		drawTree(n - 1);
		glPopMatrix();
		glRotatef(Gauss(5, 15), 0, 1, 0);
		glRotatef(Gauss(30, 50), 0, 0, 1);
		drawTree(n - 1);
	}
}
void display(void)
{
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat tree_diffuse[] = { 0.3, 0.25, 0.1, 1.0 };
	GLfloat tree_specular[] = { 0.1, 0.1, 0.1, 1.0 };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, -4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, tree_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, tree_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 8);

	glRotatef(g_centerRotate[0], 1, 0, 0);
	glRotatef(g_centerRotate[1], 0, 1, 0);
	glRotatef(g_centerRotate[2], 0, 0, 1);
	glTranslatef(0, 0, -3.0);
	setData();
	drawTree(N);
	glutSwapBuffers();
}
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-a, a, -a, a, 0.01, 1.0e3);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void keyboardKeyPressed(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'a':
	case 'A':
		g_centerRotate[2] -= 5;
		glutPostRedisplay();
		break;
	case 'd':
	case 'D':
		g_centerRotate[2] += 5;
		glutPostRedisplay();
		break;
	case 'w':
	case 'W':
		g_centerRotate[0] -= 5;
		glutPostRedisplay();
		break;
	case 's':
	case 'S':
		g_centerRotate[0] += 5;
		glutPostRedisplay();
		break;
	case 'r':
	case 'R':
		g_centerRotate[0] = 0;
		g_centerRotate[1] = 0;
		g_centerRotate[2] = 0;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}
void mouseMotionActive(int x, int y)
{
	int mouseDelta[2] = { x - g_mousePosition[0], y - g_mousePosition[1] };

	if (g_leftMouseButtonDown)
	{
		g_centerRotate[1] += 1.0 * mouseDelta[0];
		g_centerRotate[0] += 1.0 * mouseDelta[1];
	}
	g_mousePosition[0] = x;
	g_mousePosition[1] = y;

	glutPostRedisplay();
}
void mouseMotionPassive(int x, int y)
{
	g_mousePosition[0] = x;
	g_mousePosition[1] = y;
}
void mouseButtonPressed(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		g_leftMouseButtonDown = (state == GLUT_DOWN);
	g_mousePosition[0] = x;
	g_mousePosition[1] = y;
}

int main(int argc, char* argv[])
{
	int seed;
	cout << "Input the seed: ";
	cin >> seed;
	srand(seed);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(200, 50);
	glutCreateWindow("Fractal Tree");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardKeyPressed);
	glutMouseFunc(mouseButtonPressed);
	glutMotionFunc(mouseMotionActive);
	glutPassiveMotionFunc(mouseMotionPassive);
	glutMainLoop();
	return 0;
}
