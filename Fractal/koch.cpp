#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include "point2.h"
 
GLdouble PI = 3.14;
Point2 pStart(-3.0, 0.0), pEnd(3.0, 0.0), pMiddle(0.0, 2.496);  

void  init()
{
	// Set the clear color to black
	glClearColor(0.0, 0.0, 0.0, 0.0);

}
GLfloat colors[][3] = { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.5, 0.8, 1.0 } };
void drawKoch(Point2 a, Point2 b)
{
	static int i = 0;
	glLineWidth(4.0);
	glBegin(GL_LINES);
	glColor3fv(colors[i++ % 4]);
	glVertex2f(a.x, a.y);
	glVertex2f(b.x, b.y);
	glEnd();
}

void divideKoch(Point2 aP, Point2 bP, int m)
{
	Point2 cPoint, ePoint, dPoint;
	if (m>0) //mµÝ¹é´ÎÊý
	{
		cPoint.x = aP.x + (bP.x - aP.x) / 3;
		cPoint.y = aP.y + (bP.y - aP.y) / 3;
		ePoint.x = bP.x - (bP.x - aP.x) / 3;
		ePoint.y = bP.y - (bP.y - aP.y) / 3;
		float Length = sqrt((ePoint.x - cPoint.x) * (ePoint.x - cPoint.x) + (ePoint.y - cPoint.y) * (ePoint.y - cPoint.y));
		float alpha = atan((ePoint.y - cPoint.y) / (ePoint.x - cPoint.x));
		if ((ePoint.x - cPoint.x) < 0)
			alpha = alpha + PI;  //PI= 3.14
		dPoint.y = cPoint.y + sin(alpha + PI / 3) * Length;
		dPoint.x = cPoint.x + cos(alpha + PI / 3) * Length;
		divideKoch(aP, cPoint, m - 1);
		divideKoch(ePoint, bP, m - 1);
		divideKoch(cPoint, dPoint, m - 1);
		divideKoch(dPoint, ePoint, m - 1);
	}
	else
		drawKoch(aP, bP);
}

void  display()
{
	// Clear the color and depth buffers.  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Koch(a[0],a[1]);  
	int n = 4;
	divideKoch( pEnd, pStart, n);
	divideKoch(pMiddle, pEnd, n);
	divideKoch(pStart, pMiddle, n);

	glFlush();
	glutSwapBuffers();
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	GLfloat f = 6.0f;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-f, f, -f*(GLfloat)h / (GLfloat)w,
		f*(GLfloat)h / (GLfloat)w, -f, f);
	else
		glOrtho(-f*(GLfloat)w / (GLfloat)h,
		f*(GLfloat)w / (GLfloat)h, -f, f, -f, f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int  main(int  argc, char  **argv)
{
	glutInit(&argc, argv);    // Initialize GLUT function callings
	//sets the initial display mode
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	// Set window position, from the left and top corner of the screen, in numbers of pixels 
	glutInitWindowPosition(200, 100);

	// Set window size (width, height) in number of pixels     
	glutInitWindowSize(600, 600);

	// Specify a window creation event 
	glutCreateWindow("Koch");
	//A window is reshaped
	glutReshapeFunc(reshape);

	// Specify the drawing function that is called when the window 
	glutDisplayFunc(display);         // is created or re-drew

	//init();	    // Invoke this function for initialization	

	glutMainLoop();    // Enter the event processing loop

	return 0;          // Indicate normal termination 		
}
