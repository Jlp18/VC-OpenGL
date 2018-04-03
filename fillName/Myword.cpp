#include <gl/glut.h>
#include <iostream>

typedef float Color[3];  //颜色数据类型


void getpixel(GLint x , GLint y , Color color)  //获取像素点的颜色
{
	glReadPixels(x , y , 1 , 1 , GL_RGB , GL_FLOAT , color);
}

int compareColor(Color color1 , Color color2) //颜色比较
{
	if(color1[0] != color2[0] || color1[1] != color2[1] || color1[2] != color2[2])
	{
		return 0;
	}
	else
	{
		return 1;
	}
}



/*void boundaryFill4(int x , int y , Color fillColor , Color boarderColor)
{
	Color interiorColor;
	if(compareColor(interiorColor , fillColor) == 0 &&compareColor(interiorColor , boarderColor) == 0)
	{
		setpixel(x , y);
		boundaryFill4(x+1 , y , fillColor , boarderColor);
		boundaryFill4(x-1 , y , fillColor , boarderColor);
		boundaryFill4(x , y+1 , fillColor , boarderColor);
		boundaryFill4(x , y-1 , fillColor , boarderColor);
	}
}
*/
void boundaryFill8(int x , int y , Color fillColor , Color boarderColor)
{
	Color interiorColor , a , b , c , d;
	getpixel(x , y , interiorColor);
	getpixel(x+1 , y , a);
	getpixel(x , y-1 , b);
	getpixel(x , y+1 , c);
	getpixel(x-1 , y ,d);
	int i = 0;
	//四邻接点超过两个点与边界颜色相同，则该点会被遍历到，不必单独画
	if(compareColor(a , boarderColor) == 1) i++;
	if(compareColor(b , boarderColor) == 1) i++;
	if(compareColor(c , boarderColor) == 1) i++;
	if(compareColor(d , boarderColor) == 1) i++;
	if(i <= 1)
	{
		if(compareColor(interiorColor , fillColor) == 0 && compareColor(interiorColor , boarderColor) == 0)
		{
			glBegin(GL_POINTS);
	        glVertex2f(x , y);
	        glEnd();
			boundaryFill8(x+1 , y , fillColor , boarderColor);
			boundaryFill8(x , y-1 , fillColor , boarderColor);
			boundaryFill8(x-1 , y , fillColor , boarderColor);
			boundaryFill8(x , y+1 , fillColor , boarderColor);
			boundaryFill8(x+1 , y-1 , fillColor , boarderColor);
			boundaryFill8(x-1 , y-1 , fillColor , boarderColor);
			boundaryFill8(x-1 , y+1 , fillColor , boarderColor);
			boundaryFill8(x+1 , y+1 , fillColor , boarderColor);
		}
	}
}





void shape()
{
	//一半
	glBegin(GL_LINE_LOOP);
	glLineWidth(3);
	glVertex2i(200 , 200);
	//圆滑
	glVertex2i(202 , 202);
	glVertex2i(204 , 207);
	glVertex2i(206 , 213);
	glVertex2i(209 , 223);

	glVertex2i(210 , 225);


	glVertex2i(210 , 280);
	glVertex2i(240 , 280);
	glVertex2i(240 , 192);
	glVertex2i(230 , 205);
	glVertex2i(235 , 205);
	glVertex2i(235 , 225);
	//圆滑
	glVertex2i(215 , 225);
	glVertex2i(214 , 222);
	glVertex2i(213 , 218);
	glVertex2i(210 , 212);
	glVertex2i(208 , 206);
	glVertex2i(204 , 198);
	glVertex2i(200 , 196);
	glEnd();

	
	glBegin(GL_LINE_LOOP);
	glVertex2i(215 , 255);
	glVertex2i(215 , 275);
	glVertex2i(235 , 275);
	glVertex2i(235 , 255);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex2i(215 , 250);
	glVertex2i(235 , 250);
	glVertex2i(235 , 230);
	glVertex2i(215 , 230);
	glEnd();


	//另一半
	glBegin(GL_LINE_LOOP);
	glLineWidth(3);
	glVertex2i(155 , 200);
	//圆滑
	glVertex2i(157 , 202);
	glVertex2i(159 , 207);
	glVertex2i(161 , 213);
	glVertex2i(164 , 223);

	glVertex2i(165 , 225);


	glVertex2i(165 , 280);
	glVertex2i(195 , 280);
	glVertex2i(195 , 192);
	glVertex2i(185 , 205);
	glVertex2i(190 , 205);
	glVertex2i(190 , 225);
	//圆滑
	glVertex2i(170 , 225);
	glVertex2i(169 , 222);
	glVertex2i(168 , 218);
	glVertex2i(165 , 212);
	glVertex2i(163 , 206);
	glVertex2i(159 , 198);
	glVertex2i(155 , 196);
	glEnd();

	
	glBegin(GL_LINE_LOOP);
	glVertex2i(170 , 255);
	glVertex2i(170 , 275);
	glVertex2i(190 , 275);
	glVertex2i(190 , 255);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex2i(170 , 250);
	glVertex2i(190 , 250);
	glVertex2i(190 , 230);
	glVertex2i(170 , 230);
	glEnd();


	/*glBegin(GL_LINE_LOOP);
    glLineWidth(5);
    //此处修改坐标，绘制多边形
    glVertex2f(100, 100);
    glVertex2f(100, 200);
    glVertex2f(200, 200);
    glVertex2f(200, 100);
    glEnd();*/


}


void display()
{
	Color fillColor = {0.0 , 0.0 , 0.0};// 黑色填充
	Color boarderColor = {0.0 , 1.0 , 0.0}; //内框边界颜色
	Color boarderColor2 = {1.0 , 1.0 , 1.0}; //消失边框
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0 , 0 , 500 , 500);
	glColor3fv(boarderColor);
	shape();
	glColor3fv(fillColor);
	boundaryFill8(167 , 277 , fillColor , boarderColor);
	boundaryFill8(212 , 277 , fillColor , boarderColor);
	//boundaryFill8(220 , 240 , fillColor , boarderColor);
	glColor3fv(boarderColor2);
	shape();
	glFlush();
}


int main(int argc , char *argv[])
{
	glutInit(&argc , argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500 , 500);
    glutInitWindowPosition(100, 100);
	glutCreateWindow("My Word");
	glClearColor(1.0 , 1.0 , 1.0 , 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0 , 500.0 , 0.0 , 500.0);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
