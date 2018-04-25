#include <gl\glut.h>
#include <iostream>
#define PI 3.1415926
using namespace std;
class CP2
{
public:
	CP2();
	CP2(double , double);
public:
	double x , y , w;
};

CP2::CP2()
{

}
CP2::CP2(double m , double n)
{
	x = m;
	y = n;
	w = 1;
}
class CTransform   //二维几何变换类
{
public:
	CTransform();
	//virtual ~CTransform();
	void SetMat(CP2* , int);
	void Identity();  //单位矩阵
	void Translate(double , double);  //平移变换矩阵
	void Scale(double , double);  //比例变换矩阵
	void Scale(double , double , CP2);  //相对于任意点的比例变换矩阵 还没定义
	void Rotate(double);  //旋转变换矩阵
	void Rotate(double , CP2);  //相对于任意点的旋转变换矩阵
	void ReflectO();  //原点反射变换矩阵
	void ReflectX();  //X轴反射变换矩阵
	void ReflectY();  //Y轴反射变换矩阵
	void Shear(double , double);  //错切变换矩阵
	void MultiMatrix();  //矩阵相乘
public:
	double T[3][3];
	CP2 *POld;
	int num;
};

CTransform::CTransform()
{
	POld = new CP2[3];
}
void CTransform:: SetMat(CP2 *p , int n)
{
	num = n;
	POld = p;
}

void CTransform::Identity() //单位矩阵
{
	T[0][0] = 1.0;
	T[0][1] = 0.0;
	T[0][2] = 0.0;
	T[1][0] = 0.0;
	T[1][1] = 1.0;
	T[1][2] = 0.0;
	T[2][0] = 0.0;
	T[2][1] = 0.0;
	T[2][2] = 1.0;
}
void CTransform::Translate(double tx , double ty)  //平移变换矩阵
{
	Identity();
	T[2][0] = tx;
	T[2][1] = ty;
	MultiMatrix();
}
void CTransform::Scale(double sx , double sy)  //比例变换矩阵
{
	Identity();
	T[0][0] = sx;
	T[1][1] = sy;
	MultiMatrix();
}
void CTransform::Rotate(double beta)  //旋转变换矩阵
{
	Identity();
	double rad = beta * PI / 180;
	T[0][0] = cos(rad);
	T[0][1] = sin(rad);
	T[1][0] = -sin(rad);
	T[1][1] = cos(rad);
	MultiMatrix();
}
void CTransform::Rotate(double beta , CP2 p)  //相对于任意点的旋转变换矩阵
{
	Translate(-p.x , -p.y);
	Rotate(beta);
	Translate(p.x , p.y);
}
void CTransform::ReflectO()  //原点反射变换矩阵
{
	Identity();
	T[0][0] = -1;
	T[1][1] = -1;
	MultiMatrix();
}
void CTransform::ReflectX()  //X轴反射变换矩阵
{
	Identity();
	T[0][0] = 1;
	T[1][1] = -1;
	MultiMatrix();
}
void CTransform::ReflectY()  //Y轴反射变换矩阵
{
	Identity();
	T[0][0] = -1;
	T[1][1] = 1;
	MultiMatrix();
}
void CTransform::Shear(double b , double c)  //错切变换矩阵
{
	Identity();
	T[0][1] = b;
	T[1][0] = c;
	MultiMatrix();
}

void CTransform::MultiMatrix()  //矩阵相乘
{
	CP2 *PNew = new CP2[num];
	for(int i = 0 ; i < num ; i++)
	{
		PNew[i] = POld[i];
	}
	for(int j = 0 ; j < num ; j++)
	{
		POld[j].x = PNew[j].x * T[0][0] + PNew[j].y * T[1][0] + PNew[j].w * T[2][0];
		POld[j].y = PNew[j].x * T[0][1] + PNew[j].y * T[1][1] + PNew[j].w * T[2][1];
		POld[j].w = PNew[j].x * T[0][2] + PNew[j].y * T[1][2] + PNew[j].w * T[2][2];
 	}
	delete []PNew;
}

void DrawTriangle()
{
	CTransform Ctransform;
	CP2 *p = new CP2[3];
	p[0].x = 100;p[0].y = 100;p[0].w = 1;
	p[1].x = 150;p[1].y = 100;p[1].w = 1;
	p[2].x = 125;p[2].y = 150;p[2].w = 1;
	Ctransform.SetMat(p , 3);
	//Ctransform.Shear(0.1 , 0.1);
	glBegin(GL_TRIANGLES);
	for(int i = 0 ; i < 3 ; i++)
	{
		glVertex2i(p[i].x , p[i].y);
	}
	glEnd();

	//可以将Draw函数添加到类成员中
	//在此处可以做几何变换 

	//CP2 q(0.0 , 0.0);
	Ctransform.ReflectO();
	glBegin(GL_TRIANGLES);
	for(int i = 0 ; i < 3 ; i++)
	{
		glVertex2i(p[i].x , p[i].y);
	}
	glEnd();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0 , 0 , 500 , 500);
	glColor3f(0.0 , 0.0 , 0.0);
	DrawTriangle();
	/*glPointSize(10);
	glBegin(GL_POINTS);
	
	glVertex2i(10 , 10);
	glEnd();*/
	glFlush();
}



int main(int argc , char *argv[])
{
	glutInit(&argc , argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500 , 500);
	glutInitWindowPosition(100 , 100);
	glutCreateWindow("2D_Change");
	glClearColor(1.0 , 1.0 , 1.0 , 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-250.0 , 250.0 , -250.0 , 250.0);
	//glOrtho(-320.0 , 320.0 , -240.0 , 240.0 , 1.0 , 100.0);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}