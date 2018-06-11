#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib") 
#include "GL/glut.h"
//#include "iostream"
//#include"Cmath"
//using namespace std;
//////////////////////////////////////////////////////////////////////////////
//static float d = 0.0f;
void myMainWinDraw( );

void init()
{
  
    glClearColor(0.0, 0.0, 0.0, 0.0);
     glColor3f(0.0f, 0.0f, 0.0f);
     glMatrixMode( GL_MODELVIEW );
	 glLoadIdentity();
    gluLookAt(0.0,0.0,1.0, 1.,2.0,3.0,0.0,1.0,0.0);


  
}

///////////////////////////////////////////////////////////////////////////////
void reshape( int w, int h )
{
	glViewport(0,0, (GLsizei)w, (GLsizei)h );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
   
    /* gluPerspective(90,(GLfloat)w/(GLfloat)h,1.0,100);*/
   
 	 if (w<=h)
        glOrtho(-7.0, 7.0, -7.0*h/w, 7.0*h/w, -7.0, 10.0);
    else
        glOrtho(-7.0* w/h, 7.0*w/h, -7.0, 7.0, -7.0, 10.0);

}


void main( )
{

	glutInitDisplayMode( GLUT_RGB |GLUT_DOUBLE| GLUT_DEPTH );// GLUT_SINGLE 
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( 500, 500 );
	glutCreateWindow("ÊµÀý");
	init();
	glutDisplayFunc(myMainWinDraw);
    glutReshapeFunc( reshape );        

	glutMainLoop();
	return;
}

void myMainWinDraw()
{//
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 	
//	  glTranslatef(0.0,0.0,-10.0);
	 glBegin(GL_POLYGON);
	glColor3f(0.0,1.0,0.5);
	 glVertex3f(-6.0,0.0,6.0);
	 glVertex3f(6.0,0.0,6.0);
	 glVertex3f(6.0,0.0,-6.0);
	 glVertex3f(-6.0,0.0,-6.0);
	glEnd();
 /*  d -= 1.5f;
 	if(d<-52.0f)
	 	d = 0.0f;*/

	glBegin ( GL_QUADS );
	glColor3f(0.0,1.0,0.2);
    glVertex3f (0,0,-1); 
    glVertex3f (2,0,-1); 
    glVertex3f (2,0,1); 
    glVertex3f (0,0,1); 
    glEnd ();
 
    glBegin(GL_TRIANGLE_STRIP);
     glColor3f(0.0,0.0,1.0);
	glVertex3f(2,0,1);
	glVertex3f(2,2,1);
    glVertex3f(2,0,-1);
    glVertex3f(2,2,-1);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.0,0.5,0.0);
    glVertex3f(2,0,-1);
    glVertex3f(2,2,-1);
    glVertex3f(0,0,-1);
    glVertex3f(0,2,-1);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.0,0.2,1.2);
    glVertex3f(0,0,-1);
    glVertex3f(0,2,-1);
    glVertex3f(0,0,1);
    glVertex3f(0,2,1);
	glEnd();
   	glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1.0,0.5,0.0);
	glVertex3f(0,0,1);
	glVertex3f(0,2,1);
	glVertex3f(2,0,1);
	glVertex3f(2,2,1);
    glEnd();
   glBegin(GL_TRIANGLE_STRIP);
     glColor3f(0.5,1.0,0.0);
      glVertex3f(0,2,1 );
      glVertex3f(2,2,1 );
      glVertex3f(1, 3,1);
	   glColor3f(0.5,0.0,1.5);
	   glVertex3f(2,2,-1);
      glVertex3f(1,3,-1);      
       glVertex3f(0,2,-1); 
	 
	  glColor3f(0.5,0.5,0.5);
       
	  glVertex3f(1,3,1);
	  glVertex3f(0,2,1);
	   glEnd();
     	 
	glutSwapBuffers();
}
