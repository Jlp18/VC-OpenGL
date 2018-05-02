#include <iostream>
#include <gl\glut.h>

using namespace std;
#define PI 3.1415926f;

//窗口大小
GLint windowWidth = 400;
GLint windowHeight = 300;

void display()
{
	glClearColor(0.0f , 0.0f , 0.0f , 1.0f);
	glClearStencil(1);
	glEnable(GL_STENCIL_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//glViewport(0 , 0 , 400 , 300);
	//将当前Matrix状态入栈
	glPushMatrix();
	//坐标系统绕x轴旋转
	//glRotatef(0.0f , 1.0f , 0.0f , 0.0f);
	//坐标系统绕y轴旋转
	//glRotatef(0.0f , 0.0f , 1.0f , 0.0f);
	gluLookAt(-1 , 1 , 5 , 0 , 0 , 0 , 0 , 1 , 0);
	//进行平滑处理
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH , GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH , GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH , GL_NICEST);


	//红色绘制坐标系
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
	//坐标方向
	glPushMatrix();  
    glTranslatef(9.0f , 0.0f , 0.0f);  
    glRotatef(90.0f , 0.0f , 9.0f , 0.0f);  
    glutSolidCone(0.3 , 0.6 , 10 , 10);  //圆锥代替箭头
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
	glVertex3f(1.0f , 1.0f , 0.0f); //下底
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
	glVertex3f(1.0f , 1.0f , 3.0f);  //上底
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
	//横宽比率
	GLfloat ratio;
	//设置坐标系为x(-100.0f , 100.0f)、y(-100.0f , 100.0f)、z(-100.0f , 100.0f)
	GLfloat coordinatesize = 10.0f;
	//窗口宽高为零直接返回
	if(w == 0 || h == 0)
	{
		return;
	}
	//设置视口和窗口大小一致
	glViewport(0 , 0 , w , h);
	//对投影矩阵应用随后的矩阵操作
	glMatrixMode(GL_PROJECTION);
	//重置当前指定的矩阵为单位矩阵
	glLoadIdentity();
	ratio = (GLfloat)w/(GLfloat)h;
	//正交投影
	if(w < h)
	{
		glOrtho(-coordinatesize,coordinatesize,-coordinatesize/ratio,coordinatesize/ratio,-coordinatesize,coordinatesize);
	}
	else
	{
		glOrtho(-coordinatesize*ratio,coordinatesize*ratio,-coordinatesize,coordinatesize,-coordinatesize,coordinatesize);
	}
	//对模型视图矩阵堆栈应用随后的矩阵操作
	glMatrixMode(GL_MODELVIEW);
	//重置当前指定的矩阵为单位矩阵
	glLoadIdentity();
}


int main(int argc , char* argv[])
{
	glutInit(&argc , argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutCreateWindow("3D");
	glutReshapeWindow(windowWidth , windowHeight);
	//窗口居中显示
	glutPositionWindow(100.0 , 100.0);
	glutReshapeFunc(changeSize);
	glutDisplayFunc(display);
	
	glutMainLoop();
	return 0;
}