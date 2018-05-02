#include <iostream>
#include <gl\glut.h>

using namespace std;
#define PI 3.1415926f;

//���ڴ�С
GLint windowWidth = 400;
GLint windowHeight = 300;

void display()
{
	glClearColor(0.0f , 0.0f , 0.0f , 1.0f);
	glClearStencil(1);
	glEnable(GL_STENCIL_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//glViewport(0 , 0 , 400 , 300);
	//����ǰMatrix״̬��ջ
	glPushMatrix();
	//����ϵͳ��x����ת
	//glRotatef(0.0f , 1.0f , 0.0f , 0.0f);
	//����ϵͳ��y����ת
	//glRotatef(0.0f , 0.0f , 1.0f , 0.0f);
	gluLookAt(-1 , 1 , 5 , 0 , 0 , 0 , 0 , 1 , 0);
	//����ƽ������
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH , GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH , GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH , GL_NICEST);


	//��ɫ��������ϵ
	glColor3f(1.0f , 0.0f , 0.0f);
	glLineWidth(2);
	glDisable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex3f(0.0f , 0.0f , 0.0f);
	glVertex3f(9.0f , 0.0f , 0.0f);
	glVertex3f(0.0f , 0.0f , 0.0f);
	glVertex3f(0.0f , 9.0f , 0.0f);
	glVertex3f(0.0f , 0.0f , 0.0f);
	glVertex3f(0.0f , 0.0f , 9.0f);
	glEnd();

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(0.1 , 0x0101);
	glBegin(GL_LINES);
	glVertex3f(-9.0f , 0.0f , 0.0f);
	glVertex3f(0.0f , 0.0f , 0.0f);
	glVertex3f(0.0f , -9.0f , 0.0f);
	glVertex3f(0.0f , 0.0f , 0.0f);
	glVertex3f(0.0f , 0.0f , -9.0f);
	glVertex3f(0.0f , 0.0f , 0.0f);
	glEnd();
	//���귽��
	glPushMatrix();  
    glTranslatef(9.0f , 0.0f , 0.0f);  
    glRotatef(90.0f , 0.0f , 9.0f , 0.0f);  
    glutSolidCone(0.3 , 0.6 , 10 , 10);  //Բ׶�����ͷ
    glPopMatrix(); 

	glPushMatrix();
	glTranslatef(0.0f , 9.0f , 0.0f);
	glRotatef(90.0 , -9.0 , 0.0 , 0.0);
	glutSolidCone(0.3 , 0.6 , 10 , 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f , 0.0f , 9.0f);
	glutSolidCone(0.3 , 0.6 , 10 , 10);
	glPopMatrix();

	glDisable(GL_LINE_STIPPLE);
	glColor3f(0.8f , 0.8f , 0.8f);
	glBegin(GL_QUADS);
	glVertex3f(1.0f , 1.0f , 0.0f); //�µ�
	glVertex3f(1.0f , 4.0f , 0.0f);
	glVertex3f(4.0f , 4.0f , 0.0f);
	glVertex3f(4.0f , 1.0f , 0.0f);

	glVertex3f(1.0f , 4.0f , 0.0f);  
	glVertex3f(4.0f , 4.0f , 0.0f);
	glVertex3f(4.0f , 4.0f , 3.0f);
	glVertex3f(1.0f , 4.0f , 3.0f);

	glVertex3f(1.0f , 1.0f , 0.0f);
	glVertex3f(4.0f , 1.0f , 0.0f);
	glVertex3f(4.0f , 1.0f , 3.0f);
	glVertex3f(1.0f , 1.0f , 3.0f);

	glVertex3f(4.0f , 1.0f , 0.0f);
	glVertex3f(4.0f , 4.0f , 0.0f);
	glVertex3f(4.0f , 4.0f , 3.0f);
	glVertex3f(4.0f , 1.0f , 3.0f);
	glEnd();
	glColor3f(0.6f , 0.6f , 0.6f);
	glBegin(GL_QUADS);
	glVertex3f(1.0f , 1.0f , 3.0f);  //�ϵ�
	glVertex3f(1.0f , 4.0f , 3.0f);
	glVertex3f(4.0f , 4.0f , 3.0f);
	glVertex3f(4.0f , 1.0f , 3.0f);
	glEnd();
	

	
	glColor3f(0.4f , 0.4f , 0.4f);
	glBegin(GL_QUADS);
	glVertex3f(1.0f , 1.0f , 0.0f);
	glVertex3f(1.0f , 4.0f , 0.0f);
	glVertex3f(1.0f , 4.0f , 3.0f);
	glVertex3f(1.0f , 1.0f , 3.0f);
	glEnd();





	//glPushMatrix();
	glutSwapBuffers(); 
}

void changeSize(GLint w , GLint h)
{
	//������
	GLfloat ratio;
	//��������ϵΪx(-100.0f , 100.0f)��y(-100.0f , 100.0f)��z(-100.0f , 100.0f)
	GLfloat coordinatesize = 10.0f;
	//���ڿ��Ϊ��ֱ�ӷ���
	if(w == 0 || h == 0)
	{
		return;
	}
	//�����ӿںʹ��ڴ�Сһ��
	glViewport(0 , 0 , w , h);
	//��ͶӰ����Ӧ�����ľ������
	glMatrixMode(GL_PROJECTION);
	//���õ�ǰָ���ľ���Ϊ��λ����
	glLoadIdentity();
	ratio = (GLfloat)w/(GLfloat)h;
	//����ͶӰ
	if(w < h)
	{
		glOrtho(-coordinatesize,coordinatesize,-coordinatesize/ratio,coordinatesize/ratio,-coordinatesize,coordinatesize);
	}
	else
	{
		glOrtho(-coordinatesize*ratio,coordinatesize*ratio,-coordinatesize,coordinatesize,-coordinatesize,coordinatesize);
	}
	//��ģ����ͼ�����ջӦ�����ľ������
	glMatrixMode(GL_MODELVIEW);
	//���õ�ǰָ���ľ���Ϊ��λ����
	glLoadIdentity();
}


int main(int argc , char* argv[])
{
	glutInit(&argc , argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutCreateWindow("3D");
	glutReshapeWindow(windowWidth , windowHeight);
	//���ھ�����ʾ
	glutPositionWindow(100.0 , 100.0);
	glutReshapeFunc(changeSize);
	glutDisplayFunc(display);
	
	glutMainLoop();
	return 0;
}