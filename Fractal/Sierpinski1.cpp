#include <stdio.h>
#include <stdlib.h>

#include <gl/glut.h>

GLfloat colors[][3] = { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.5, 0.8, 1.0 } };

void IF_sierpinski()
{
	long n = 100000; //0000
	float m[7][7] = { 0 };
	float a, b, c, d, e, f, p;
	float x = 0, y = 0;
	float x1, y1;
	// W1
	m[0][0] = 0.5;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0.5;
	m[0][4] = 0;
	m[0][5] = 0;
	m[0][6] = 0.333;
	//W2
	m[1][0] = 0.5;
	m[1][1] = 0;
	m[1][2] = 0;
	m[1][3] = 0.5;
	m[1][4] = 0.5;
	m[1][5] = 0;
	m[1][6] = 0.333;
	//W3
	m[2][0] = 0.5;
	m[2][1] = 0;
	m[2][2] = 0;
	m[2][3] = 0.5;
	m[2][4] = 0.25;
	m[2][5] = 0.5;
	m[2][6] = 0.334;
	int i = 0;
	while (n > 0)
	{
		p = (float)rand() / RAND_MAX;
		if (p <= m[0][6]) {
			a = m[0][0]; b = m[0][1]; c = m[0][2]; d = m[0][3]; e = m[0][4];
			f = m[0][5];
		}
		else if (p <= m[0][6] + m[1][6]) {
			a = m[1][0]; b = m[1][1]; c = m[1][2]; d = m[1][3]; e = m[1][4];
			f = m[1][5];
		}
		else if (p <= m[0][6] + m[1][6] + m[2][6]) {
			a = m[2][0]; b = m[2][1]; c = m[2][2]; d = m[2][3]; e = m[2][4];
			f = m[2][5];
		}
		else {
			a = m[3][0]; b = m[3][1]; c = m[3][2]; d = m[3][3]; e = m[3][4];
			f = m[3][5];
		}
		x1 = (a * x) + (b * y) + e;  y1 = (c * x) + (d * y) + f;
		x = x1; y = y1;
		
		glPointSize(3);
		glBegin(GL_POINTS);
		glColor3fv(colors[i++ % 4]); //
			glVertex2f(x*200, y*200);
		glEnd();
		n--;
	}
}

void sierpinski()
{
	GLfloat vertices[3][3] = {{0.0,0.0,0.0}, {25.0, 50.0,0.0}, {50.0,0.0,0.0}};
	// an arbitrary triangle in the plane z = 0;
	GLfloat p[3] = {7.5, 5.0, 0.0};
	
	// or set to any desired initial point inside the triangle;
	int  j,k;
	//int  rand();
	glPointSize(2);
	glBegin(GL_POINTS);
	
	for (k = 0; k < 5000; k++)
	{
		/* pick a random vertex from 0,1,2*/
		j = rand()%3;
		// compute new location;
		p[0] = (p[0]+vertices[j][0])/2;
		p[1] = (p[1]+vertices[j][1])/2;
		// display() new point
		glColor3fv(colors[j]);
		glVertex3fv(p);
	}
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	//sierpinski();
	IF_sierpinski();
	
	glFlush();
	glutSwapBuffers();
}



void resize(GLsizei w,GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,50.0,0,50.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc,char* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB |GLUT_DEPTH);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("2D Sierpinski");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	
	glutMainLoop();
	return 0;
}