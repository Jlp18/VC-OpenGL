#include <math.h>
#include <iostream>
#include <string>
using namespace std;
class  Node
{
public:
	float x, y, z;
	float directiony, directionz;
	//float directionx;
	Node(){}
};
class Image{
public:
	GLint imagewidth;
	GLint imageheight;
	GLint pixellength;
	GLubyte* pixeldata;
	Image(){
		pixeldata = NULL;
		pixellength = 0;
		imagewidth = 0;
		imageheight = 0;
	}
	~Image()
	{
		free(pixeldata);
	}
};

