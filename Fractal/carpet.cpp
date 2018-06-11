#include <stdio.h>
#include <stdlib.h>

#include <gl/glut.h>
#include "point2.h"

void sierpinski_carpet(int n, Point2 p0, Point2 p1)
{
	if (0 == n)
	{
		glColor3f(0.9, 0.4, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(p0.x, p0.y);
		glVertex2f(p1.x, p0.y);
		glVertex2f(p1.x, p1.y);
		glVertex2f(p0.x, p1.y);
		glEnd();
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(p0.x, p0.y);
		glVertex2f(p1.x, p0.y);
		glVertex2f(p1.x, p1.y);
		glVertex2f(p0.x, p1.y);
		glEnd();
		return;
	}
	double w = p1.x - p0.x, h = p1.y - p0.y;
	Point2 p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13;
	p2 = Point2(p0.x + w / 3, p0.y);
	p3 = Point2(p0.x + 2 * w / 3, p0.y);
	p4 = Point2(p1.x, p0.y + h / 3);
	p5 = Point2(p1.x, p0.y + 2 * h / 3);
	p6 = Point2(p0.x + 2 * w / 3, p1.y);
	p7 = Point2(p0.x + w / 3, p1.y);
	p8 = Point2(p0.x, p0.y + 2 * h / 3);
	p9 = Point2(p0.x, p0.y + h / 3);
	p10 = Point2(p0.x + w / 3, p0.y + h / 3);
	p11 = Point2(p0.x + 2 * w / 3, p0.y + h / 3);
	p12 = Point2(p0.x + 2 * w / 3, p0.y + 2 * h / 3);
	p13 = Point2(p0.x + w / 3, p0.y + 2 * h / 3);
	sierpinski_carpet(n - 1, p0, p10);
	sierpinski_carpet(n - 1, p2, p11);
	sierpinski_carpet(n - 1, p3, p4);
	sierpinski_carpet(n - 1, p9, p13);
	sierpinski_carpet(n - 1, p11, p5);
	sierpinski_carpet(n - 1, p8, p7);
	sierpinski_carpet(n - 1, p13, p6);
	sierpinski_carpet(n - 1, p12, p1);

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	Point2 pLeft(10, 10);
	Point2 pRight(40, 40);
	sierpinski_carpet(4, pLeft, pRight);

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
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(300, 200);
	glutCreateWindow("2D Sierpinski");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);

	glutMainLoop();
	return 0;
}