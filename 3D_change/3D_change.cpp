#include <iostream>
#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "CP3.h"

#include "Transform.h"

using namespace std;
  
int WinHeight , WinWidth;
double dx = 0.0 , dy = 0.0 , dz = 0.0;
double sx = 1.0 , sy = 1.0 , sz = 1.0;
double degree = 0.0;
bool temp = false;
void F()
{
	
	Transform transform;
	CP3 *p = new CP3[8];
	p[0].x = 0.0 ; p[0].y = 0.0 ; p[0].z = 0.0 ; p[0].r = 1.0;
	p[1].x = 1.0 ; p[1].y = 0.0 ; p[1].z = 0.0 ; p[1].r = 1.0;
	p[2].x = 1.0 ; p[2].y = 1.0 ; p[2].z = 0.0 ; p[2].r = 1.0;
	p[3].x = 0.0 ; p[3].y = 1.0 ; p[3].z = 0.0 ; p[3].r = 1.0;
	
	p[4].x = 0.0 ; p[4].y = 0.0 ; p[4].z = 1.0 ; p[4].r = 1.0;
	p[5].x = 1.0 ; p[5].y = 0.0 ; p[5].z = 1.0 ; p[5].r = 1.0;
	p[6].x = 1.0 ; p[6].y = 1.0 ; p[6].z = 1.0 ; p[6].r = 1.0;
	p[7].x = 0.0 ; p[7].y = 1.0 ; p[7].z = 1.0 ; p[7].r = 1.0;


	transform.SetMat(p , 8);
	transform.Translate(dx , dy , dz);  //移动
	transform.Scale(sx , sy , sz);  //缩放
	transform.Rotate(degree);
	if(temp)
	{
		transform.ReflectX();
		temp = false;
	}
	//四个点确定一个面
	int m1[4] = {0 , 1 , 2 , 3};
	int m2[4] = {0 , 1 , 5 , 4};
	int m3[4] = {0 , 3 , 7 , 4};
	int m4[4] = {2 , 3 , 7 , 6};
	int m5[4] = {1 , 2 , 6 , 5};
	int m6[4] = {4 , 5 , 6 , 7};
	
	glBegin(GL_QUADS);
	{
		for(int i = 0 ; i < 4 ; i ++)
		{
			glColor3f(0.0 , 0.0 , 1.0);
			glVertex3f(p[m1[i]].x , p[m1[i]].y , p[m1[i]].z);
		}
		for(int i = 0 ; i < 4 ; i++)
		{
			glColor3f(1.0 , 0.0 , 0.0);
			glVertex3f(p[m2[i]].x , p[m2[i]].y , p[m2[i]].z);
		}
		for(int i = 0 ; i < 4 ; i++)
		{
			glColor3f(0.0 , 1.0 , 0.0);
			glVertex3f(p[m3[i]].x , p[m3[i]].y , p[m3[i]].z);
		}
		for(int i = 0 ; i < 4 ; i++)
		{
			glColor3f(0.5 , 0.5 , 0.5);
			glVertex3f(p[m4[i]].x , p[m4[i]].y , p[m4[i]].z);
		}
		for(int i = 0 ; i < 4 ; i++)
		{
			glColor3f(1.0 , 0.0 , 1.0);
			glVertex3f(p[m5[i]].x , p[m5[i]].y , p[m5[i]].z);
		}
		for(int i = 0 ; i < 4 ; i++)
		{
			glColor3f(1.0 , 1.0 , 0.0);
			glVertex3f(p[m6[i]].x , p[m6[i]].y , p[m6[i]].z);
		}
	}
	glEnd();

	//glutSwapBuffers();
}

void G()
{
	//红色绘制坐标系
	glColor3f(1.0f , 0.0f , 0.0f);
	glLineWidth(2);
	glDisable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex3f(0.0f , 0.0f , 0.0f);
	glVertex3f(5.0f , 0.0f , 0.0f);
	glVertex3f(0.0f , 0.0f , 0.0f);
	glVertex3f(0.0f , 5.0f , 0.0f);
	glVertex3f(0.0f , 0.0f , 0.0f);
	glVertex3f(0.0f , 0.0f , 5.0f);
	glEnd();

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(0.1 , 0x0101);
	glBegin(GL_LINES);
	glVertex3f(-5.0f , 0.0f , 0.0f);
	glVertex3f(0.0f , 0.0f , 0.0f);
	glVertex3f(0.0f , -5.0f , 0.0f);
	glVertex3f(0.0f , 0.0f , 0.0f);
	glVertex3f(0.0f , 0.0f , -5.0f);
	glVertex3f(0.0f , 0.0f , 0.0f);
	glEnd();

	//坐标方向  x轴箭头
	glPushMatrix();  
    glTranslatef(5.0f , 0.0f , 0.0f);  
    glRotatef(90.0f , 0.0f , 5.0f , 0.0f);  
    glutSolidCone(0.3 , 0.6 , 10 , 10);  //圆锥代替箭头
    glPopMatrix(); 
	//y轴箭头
	glPushMatrix();
	glTranslatef(0.0f , 5.0f , 0.0f);
	glRotatef(90.0 , -5.0 , 0.0 , 0.0);
	glutSolidCone(0.3 , 0.6 , 10 , 10);
	glPopMatrix();
	//z轴箭头
	glPushMatrix();
	glTranslatef(0.0f , 0.0f , 5.0f);
	glutSolidCone(0.3 , 0.6 , 10 , 10);
	glPopMatrix();


	glColor3f(0.0 , 1.0 , 1.0);
	glPushMatrix();  
	glutSolidSphere(1, 16 , 16);//实心球
	glPopMatrix();


	glutSwapBuffers();
	
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0,1.0,1.0,0.0);
	
	F();
	G();
	glFlush();
}

void Reshape(int w, int h)
{
    WinWidth = w;
    WinHeight = h;
    // //改变显示区域，起始位置为客户端窗口左下角（非坐标原点）
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //宽高比改为当前值，视线区域与屏幕大小一致；
    gluPerspective(45, 1.0*WinWidth / WinHeight, 1, 1000);
    // 开启更新深度缓冲区的功能
    glEnable(GL_DEPTH_TEST);
    // 摄像机视图观看，从 （0，5，20） 往（0，0，0）处看，（0，1，0）为正方向
    gluLookAt(20, 20, 20, 0, 0, 0, 0, 1, 0);
}

void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)   dy +=1.0f;
	if (key == GLUT_KEY_DOWN)   dy -=1.0f;
	if (key == GLUT_KEY_LEFT)  dx -= 1.0f;
    if (key == GLUT_KEY_RIGHT)   dx += 1.0f;
	if (key == GLUT_KEY_F11) 
	{
		sx += 0.2;
		sy += 0.2;
		sz += 0.2;
	}
	if(key == GLUT_KEY_F12)
	{
		sx -= 0.2;
		sy -= 0.2;
		sz -= 0.2;
	}
	if(key == GLUT_KEY_F10)
	{
		degree += 5.0;
	}

	if(key == GLUT_KEY_INSERT)  //是否xoy面反射变换
	{
		temp = true;
	}

    //刷新窗口
    glutPostRedisplay();
}


int main(int argc , char *argv[])
{
	glutInit(&argc , argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE);
	glClearColor(1.0 , 1.0 , 1.0 , 0.0);
	glutInitWindowSize(400 , 400);
	glutCreateWindow("3D");
	glutDisplayFunc(&display);
	glutReshapeFunc(&Reshape);
	glutSpecialFunc(SpecialKeys);
	glutMainLoop();
	return 0;
}



