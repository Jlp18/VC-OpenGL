# ifndef CP3_H
# define CP3_H
#include <iostream>
#include <gl\glut.h>
using namespace std;
class CP3
{
public:
	double x;
	double y;
	double z;
	double r;
public:
	CP3(double , double , double);
	CP3();
};
CP3::CP3(){}

CP3::CP3(double a , double b , double c)
{
	x = a;
	y = b;
	z = c;
	r = 1;
}
#endif