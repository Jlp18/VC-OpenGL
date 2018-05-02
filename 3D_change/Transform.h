#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <iostream>
#include "CP3.h"
using namespace std;
class Transform
{
public:
	Transform();
	//virtual ~Transform();
	void SetMat(CP3* , int);
	void Identity(); 
	void Translate(double , double , double);  //平移
	void Scale(double , double , double);  //缩放
	void Rotate(double);  //旋转  绕x轴转
	void ReflectX();   //xoy面反射变换
	void MultiMatrix();  //矩阵相乘
public:
	double T[4][4];
	CP3 *POld;
	int num;
};
Transform::Transform(){}
void Transform::SetMat(CP3 *p , int n)
{
	POld = p;
	num = n;
}
void Transform::Identity()
{
	for(int i = 0 ; i < 4 ; i++)
	{
		for(int j = 0 ; j < 4 ; j++)
		{
			if(i == j)
			{
				T[i][j] = 1;
			}
			else
			{
				T[i][j] = 0;
			}
		}
	}
}
void Transform::Translate(double x , double y , double z)
{
	Identity();
	T[3][0] = x;
	T[3][1] = y;
	T[3][2] = z;
	MultiMatrix();
}

void Transform::Scale(double sx , double sy ,double sz)
{
	Identity();
	T[0][0] = sx;
	T[1][1] = sy;
	T[2][2] = sz;
	MultiMatrix();
}

void Transform::Rotate(double deg)
{
	Identity();
	T[1][1] = cos(deg);
	T[1][2] = sin(deg);
	T[2][1] = -sin(deg);
	T[2][2] = cos(deg);
	MultiMatrix();
}

void Transform::ReflectX()
{
	Identity();
	T[2][2] = -1;
	MultiMatrix();
}

void Transform::MultiMatrix()
{
	CP3 *PNew = new CP3[num];
	for(int i = 0 ; i < num ; i++)
	{
		PNew[i] = POld[i];
	}
	for(int j = 0 ; j < num ; j++)
	{
		POld[j].x = PNew[j].x*T[0][0] + PNew[j].y*T[1][0] + PNew[j].z*T[2][0] + PNew[j].r*T[3][0];
		POld[j].y = PNew[j].x*T[0][1] + PNew[j].y*T[1][1] + PNew[j].z*T[2][1] + PNew[j].r*T[3][1];
		POld[j].z = PNew[j].x*T[0][2] + PNew[j].y*T[1][2] + PNew[j].z*T[2][2] + PNew[j].r*T[3][2];
		POld[j].r = PNew[j].x*T[0][3] + PNew[j].y*T[1][3] + PNew[j].z*T[2][3] + PNew[j].r*T[3][3];
	}
	delete []PNew;
}




#endif // !TRANSFORM_H
