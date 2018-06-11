#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <GL/glut.h>
using namespace std;
#define DELAY 12

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

//***********************************************************************************************
double rotate_x = 0.0;
double rotate_y = 0.0;

# define  white  1.0 ,  1.0  ,  1.0   // ����ɫ�ĺ궨��  
# define  green  0.0 ,  0.502,  0.0  
# define  red    1.0 ,  0.0  ,  0.0  
# define  gray   0.502, 0.502,0.502  
# define  hgray  0.117, 0.180,0.227  
# define  blue   0.0  , 0.0  ,  1.0  
# define  pi  3.14159265  
# define  gold   1.0,215.0/255.0,0.0  
# define  hgreen 0.0,100.0/255.0,0.0  
# define  brown  210.0/255.0, 105.0/255.0,  30.0/255.0  
# define  men   244.0/255.0 ,164.0/255.0 , 96.0/255.0  
# define  menba   139.0/255.0 ,69.0/255.0,19.0/255.0  
double house[2] = {0.0 , 0.0};
double tree[2] = {0.0 , 0.0};
double fang[8][3];             // ���峤�����8������  
// ����constract����  �������������������ĵ�ʱ��  
// ���������7������ ����ֵ��fang  
double san[8][3];              // �������Ϊ���εĳ�����  
void cons(double x, double y, double z, double x1, double y1, double z1){
	san[0][0] = x;
	san[0][1] = y;
	san[0][2] = z;     //  ��0����  

	san[1][0] = x;
	san[1][1] = y;
	san[1][2] = z + z1;   //  ��1����  

	san[4][0] = x;
	san[4][1] = y + y1;
	san[4][2] = z;     //  ��4����  

	san[5][0] = x;
	san[5][1] = y + y1;
	san[5][2] = z + z1 / 2;      //  ��5����  
	for (int i = 0; i<3; i++){
		if (i == 0){
			san[3][i] = san[0][i] + x1;
			san[2][i] = san[1][i] + x1;
			san[6][i] = san[4][i] + x1;
			san[7][i] = san[5][i] + x1;
		}
		else{
			san[3][i] = san[0][i];
			san[2][i] = san[1][i];
			san[6][i] = san[4][i];
			san[7][i] = san[5][i];
		}
	}
}
void constract(double x, double y, double z, double x1, double y1, double z1){
	fang[0][0] = x;
	fang[0][1] = y;
	fang[0][2] = z;        //  ��0����  

	fang[1][0] = x;
	fang[1][1] = y;
	fang[1][2] = z + z1;     //  ��һ����  

	fang[2][0] = x + x1;
	fang[2][1] = y;
	fang[2][2] = z + z1;     //  �ڶ�����  

	fang[3][0] = x + x1;
	fang[3][1] = y;
	fang[3][2] = z;        //  ��������  
	for (int i = 0; i<4; i++){  // for()ѭ�������������ĸ���  
		for (int j = 0; j<3; j++){
			if (j == 1)
				fang[i + 4][j] = fang[i][j] + y1;
			else
				fang[i + 4][j] = fang[i][j];
		}
	}
}
void build2(){
	glBegin(GL_POLYGON);
	//glColor3f(red);  
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(san[0][0], san[0][1], san[0][2]);
	glVertex3f(san[1][0], san[1][1], san[1][2]);
	glVertex3f(san[2][0], san[2][1], san[2][2]);
	glVertex3f(san[3][0], san[3][1], san[3][2]);
	glEnd();   //     �µ�  

	glBegin(GL_POLYGON);
	//glColor3f(green);  
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(san[1][0], san[1][1], san[1][2]);
	glVertex3f(san[0][0], san[0][1], san[0][2]);
	glVertex3f(san[4][0], san[4][1], san[4][2]);
	glVertex3f(san[5][0], san[5][1], san[5][2]);
	glEnd();   //     ����  

	glBegin(GL_POLYGON);
	//glColor3f(green);  
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(san[7][0], san[7][1], san[7][2]);
	glVertex3f(san[6][0], san[6][1], san[6][2]);
	glVertex3f(san[3][0], san[3][1], san[3][2]);
	glVertex3f(san[2][0], san[2][1], san[2][2]);
	glEnd();   //     ����  

	glBegin(GL_POLYGON);
	//glColor3f(green);  
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(san[5][0], san[5][1], san[5][2]);
	glVertex3f(san[6][0], san[6][1], san[6][2]);
	glVertex3f(san[2][0], san[2][1], san[2][2]);
	glVertex3f(san[1][0], san[1][1], san[1][2]);
	glEnd();   //     ǰ��  

	glBegin(GL_POLYGON);
	//glColor3f(green);  
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(san[0][0], san[0][1], san[0][2]);
	glVertex3f(san[3][0], san[3][1], san[3][2]);
	glVertex3f(san[7][0], san[7][1], san[7][2]);
	glVertex3f(san[4][0], san[4][1], san[4][2]);
	glEnd();   //     ����  

	glBegin(GL_POLYGON);
	//glColor3f(red);  
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(san[4][0], san[4][1], san[4][2]);
	glVertex3f(san[7][0], san[7][1], san[7][2]);
	glVertex3f(san[6][0], san[6][1], san[6][2]);
	glVertex3f(san[5][0], san[5][1], san[5][2]);
	glEnd();   //     ����  
}
void build(){
	glBegin(GL_POLYGON);
	//glColor3f(red);  
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(fang[0][0], fang[0][1], fang[0][2]);
	glVertex3f(fang[1][0], fang[1][1], fang[1][2]);
	glVertex3f(fang[2][0], fang[2][1], fang[2][2]);
	glVertex3f(fang[3][0], fang[3][1], fang[3][2]);
	glEnd();   //     �µ�  

	glBegin(GL_POLYGON);
	//glColor3f(green);  
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(fang[1][0], fang[1][1], fang[1][2]);
	glVertex3f(fang[0][0], fang[0][1], fang[0][2]);
	glVertex3f(fang[4][0], fang[4][1], fang[4][2]);
	glVertex3f(fang[5][0], fang[5][1], fang[5][2]);
	glEnd();   //     ����  

	glBegin(GL_POLYGON);
	//glColor3f(green);  
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(fang[7][0], fang[7][1], fang[7][2]);
	glVertex3f(fang[6][0], fang[6][1], fang[6][2]);
	glVertex3f(fang[2][0], fang[2][1], fang[2][2]);
	glVertex3f(fang[3][0], fang[3][1], fang[3][2]);
	glEnd();   //     ����  

	glBegin(GL_POLYGON);
	//glColor3f(green);  
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(fang[5][0], fang[5][1], fang[5][2]);
	glVertex3f(fang[6][0], fang[6][1], fang[6][2]);
	glVertex3f(fang[2][0], fang[2][1], fang[2][2]);
	glVertex3f(fang[1][0], fang[1][1], fang[1][2]);
	glEnd();   //     ǰ��  

	glBegin(GL_POLYGON);
	//glColor3f(green);  
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(fang[0][0], fang[0][1], fang[0][2]);
	glVertex3f(fang[3][0], fang[3][1], fang[3][2]);
	glVertex3f(fang[7][0], fang[7][1], fang[7][2]);
	glVertex3f(fang[4][0], fang[4][1], fang[4][2]);
	glEnd();   //     ����  

	glBegin(GL_POLYGON);
	//glColor3f(red);  
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(fang[4][0], fang[4][1], fang[4][2]);
	glVertex3f(fang[7][0], fang[7][1], fang[7][2]);
	glVertex3f(fang[6][0], fang[6][1], fang[6][2]);
	glVertex3f(fang[5][0], fang[5][1], fang[5][2]);
	glEnd();   //     ����  
}

void display2(void)
{
	//****************************���ӵ���װ壨��ɫΪ ��ɫ��********  
	glBegin(GL_POLYGON);
	constract(0, 0, 0, 5, 0.1, 5);
	glColor3f(green);
	build();
	//****************************���ӳ���װ壨��ɫ  ���ɫ��****************  
	glBegin(GL_POLYGON);
	constract(3.3, 0.2, 2.5, 1.4, 0.01, 2.5);
	glColor3f(gray);
	build();

	//****************************����դ����������ɫΪ ��ɫ��********  
	glBegin(GL_POLYGON);
	constract(0.1, 0.1, 0.1, 0.2, 0.2, 4.8);
	glColor3f(white);
	build();       //    ��Ӧ��A��  
	constract(0.3, 0.1, 0.1, 4.4, 0.2, 0.2);
	glColor3f(white);
	build();       //    ��Ӧ��B��  
	constract(4.7, 0.1, 0.1, 0.2, 0.2, 4.8);
	glColor3f(white);
	build();       //    ��Ӧ��C��  
	constract(0.3, 0.1, 4.7, 1, 0.2, 0.2);
	glColor3f(white);
	build();       //    ��Ӧ��D��  
	constract(2.3, 0.1, 4.7, 1, 0.2, 0.2);
	glColor3f(white);
	build();       //    ��Ӧ��F��  
	//****************************����դ�����ӣ���ɫΪ ��ɫ��********  
	glBegin(GL_POLYGON);
	constract(0.1, 0.1, 0.1, 0.2, 0.5, 0.2);
	glColor3f(white);
	build();       //    ��Ӧ��A��  
	glBegin(GL_POLYGON);
	constract(4.7, 0.1, 0.1, 0.2, 0.5, 0.2);
	glColor3f(white);
	build();       //    ��Ӧ��C��  
	glBegin(GL_POLYGON);
	constract(2.3, 0.1, 4.7, 0.2, 0.5, 0.2);
	glColor3f(white);
	build();       //    ��Ӧ��F��  
	glBegin(GL_POLYGON);
	constract(0.1, 0.1, 4.7, 0.2, 0.5, 0.2);
	glColor3f(white);
	build();       //    ��Ӧ��E��  
	glBegin(GL_POLYGON);
	constract(4.7, 0.1, 4.7, 0.2, 0.5, 0.2);
	glColor3f(white);
	build();       //    ��Ӧ��G��  
	glBegin(GL_POLYGON);
	constract(3.1, 0.1, 4.7, 0.2, 0.5, 0.2);
	glColor3f(white);
	build();       //    ��Ӧ��H��  
	glBegin(GL_POLYGON);
	constract(1.1, 0.1, 4.7, 0.2, 0.5, 0.2);
	glColor3f(white);
	build();       //    ��Ӧ��I��  
	//****************************����դ������ɫΪ ���ɫ��********  
	glColor3f(hgray);
	for (int i = 35; i<470; i += 25)
	{
		constract(0.15,0.2, i/100.0, 0.06, 0.3, 0.06);
		build();         //�������  
	}
	for (int i = 35; i<470; i += 25)
	{
		constract(4.75, 0.2, i/100.0, 0.06, 0.3, 0.06);
		build();          // �ұ�����  
	}
	for (int i = 35; i<470; i += 25)
	{
		constract(i/100.0, 0.2, 0.15, 0.06, 0.3, 0.06);
		build();          // �ϱߺ���  
	}
	for (int i = 35; i<110; i += 25)
	{
		constract(i/100.0, 0.2, 4.85, 0.06, 0.3, 0.06);
		build();          // �±ߺ���1  
	}
	for (int i = 250; i<310; i += 25)
	{
		constract(i/100.0, 0.2, 4.85, 0.06, 0.3, 0.06);
		build();          // �±ߺ���2  
	}
	//****************************���ӳ���ǽ����ɫΪ ��ɫ��********  
	glColor3f(white);
	constract(3.2, 0.1, 2.5, 0.1, 1.0, 2.2);
	build();
	constract(4.6, 0.1, 2.5, 0.1, 1.0, 2.2);
	build();
	//****************************���ӳ��ⶥ���ɫΪ ���ɫ��********  
	glColor3f(hgray);
	constract(3.2, 1.1, 2.5, 1.5, 0.1, 2.2);
	build();
	//****************************�������ҺͿ�����ǽ�ڣ���ɫΪ ��ɫ��********  
	glColor3f(white);
	constract(0.5, 0.1, 0.5, 0.12, 1.5, 2.0);
	build();     //��ǽ��  
	glColor3f(white);
	constract(4.38, 0.1, 0.5, 0.12, 1.5, 2.0);
	build();     //��ǽ��  
	glColor3f(white);
	constract(0.62, 0.1, 0.5, 3.76, 1.5, 0.12);
	build();     //��ǽ��  
	glColor3f(white);
	constract(0.62, 0.1, 2.35, 3.76, 0.5, 0.12);
	build();     //��ǽ��1  
	glColor3f(white);
	constract(0.62, 0.6, 2.35, 0.5, 0.5, 0.12);
	build();     //��ǽ��2  
	glColor3f(white);
	constract(1.62, 0.6, 2.35, 2.76, 0.5, 0.12);
	build();     //��ǽ��3  
	glColor3f(white);
	constract(0.62, 1.1, 2.35, 3.76, 0.5, 0.12);
	build();     //��ǽ��4  
	//****************************�������ҺͿ����Ĳ�������ɫΪ ��ɫ��********  
	glColor4f(blue, 0.35);
	constract(0.62 + 0.5, 0.6, 2.35, 0.5, 0.5, 0.12);
	build();
	//****************************���ӳ��ⲣ������ɫΪ ���ɫ��********  
	glColor4f(blue, 0.35);
	constract(3.3, 0.22, 4.5, 1.3, 0.9, 0.1);
	build();
	//****************************���ӷ��� ����ɫ ��ɫ��************  
	glColor3f(red);
	cons(0.5, 1.6, 1.4, 4.0, 0.27, 1.1);
	build2();
	cons(0.5, 1.87, 1.4, 4.0, 0.27, 0.9);
	build2();
	cons(0.5, 2.14, 1.4, 4.0, 0.27, 0.7);
	build2();
	cons(0.5, 2.41, 1.4, 4.0, 0.15, 0.5);
	build2();
	glColor3f(red);
	cons(0.5, 1.6, 1.4, 4.0, 0.27, -1.1);
	build2();
	cons(0.5, 1.87, 1.4, 4.0, 0.27, -0.9);
	build2();
	cons(0.5, 2.14, 1.4, 4.0, 0.27, -0.7);
	build2();
	cons(0.5, 2.41, 1.4, 4.0, 0.15, -0.5);
	build2();
	//************************************* ��*************  
	glColor3f(men);
	constract(2.3, 0.1, 2.5, 0.5, 1.0, 0.05);
	build();              //����  
	glColor3f(menba);
	constract(2.35, 0.6, 2.55, 0.05, 0.05, 0.05);
	build();              //�Ű���  
	//**************************************С·*************  
	for (int i = 0; i<6; i++)
	{
		glColor3f(brown);
		constract(2.35 - i * 0.15, 0.1, 2.5 + i * 0.4, 0.4, 0.02, 0.2);
		build();
	}
	//**************************************̫��*************  
	glColor3f(gold);
	glTranslatef(2.5, 8.0, 0);
	glutSolidSphere(0.35, 20, 20);
	glTranslatef(-2.5, -8.0, 0);
	//**************************************����*************  
	glColor3f(brown);
	constract(0.6, 0.1, 3.9, 0.15, 0.7, 0.15);
	build();
	//**************************************��Ҷ*************  
	glColor3f(hgreen);
	glTranslatef(0.6, 0.7, 4.0);
	glutSolidSphere(0.25, 10, 10);  //��1  
	glTranslatef(0.2, 0, 0);
	glutSolidSphere(0.25, 10, 10);  //��2  
	glTranslatef(-0.1, 0, -0.1);
	glutSolidSphere(0.25, 10, 10);  //��3  
	glTranslatef(0, 0, 0.2);
	glutSolidSphere(0.25, 10, 10);  //��4  
	glTranslatef(0, 0.1, -0.1);
	glutSolidSphere(0.25, 10, 10);  //��4  
}


//***************************************Draw a Tree**************************************
#define speed 0.003
#define N 6
#define M 3   //̫���� �ػ�����  ����ѭ������
bool g_leftMouseButtonDown = false;
GLUquadric *qObj;  //�������������������������
float R[N + 1], H[N + 1], k, p, q, m, alpha, z[N + 1], a = 6;

float Gauss(float min, float max)
{
	int a = rand()%3, b = rand()%3, c = rand()%3, d = rand()%3;
	int x = a + b + c + d;
	double y = (x*sqrt(3.0)) / RAND_MAX - sqrt(12.0);
	double mid = (min + max) / 2;
	float z = (float)(mid + (max - mid)*y / (2 * sqrt(3.0)));
	return z;
}
void setData(void)
{
	R[N] = 0.3;
	H[N] = 2.4;
	z[N] = H[N];
	k = 0.5;
	p = 0.6;
	q = 0.5;
	m = 0.7;
	alpha = 45;
	for (int i = N - 1; i >= 0; i--)
	{
		R[i] = R[i + 1] * q;
		H[i] = H[i + 1] * m;
		z[i] = z[i + 1] * p;
	}
}
void drawTree(int n)
{
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.1, 0.15, 0.1, 1.0 };
	GLfloat specular[] = { 0.1, 0.1, 0.1, 1.0 };
	if (n == 0)  //����Ҷ���д���
	{
		float h = Gauss(0.4, 0.7);
		gluCylinder(qObj, R[n], k*R[n], H[n] * h, 20, 20); //���ƶ������棬Բ����
		glTranslatef(0, 0, H[n] * h);
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, 5);
		glRotatef(Gauss(10, 50), 1, 0, 0);
		glRotatef(45, 0, 1, 0);
		glRotatef(90, 1, 0, 0);
		glScalef(1, 1, 0.1);
		glutSolidCube(0.15);
		return;
	}
	else
	{
		gluCylinder(qObj, R[n], k*R[n], H[n], 20, 20);

		glTranslatef(0, 0, H[n]);
		glPushMatrix();
		glTranslatef(0, 0, -H[n] * Gauss(0.0, 0.4));
		glRotatef(Gauss(30, 80), 0, 0, 1);
		glRotatef(Gauss(40, 70), 0, 1, 0);
		drawTree(n - 1);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0, 0, -H[n] * Gauss(0.0, 0.4));
		glRotatef(Gauss(140, 200), 0, 0, 1);
		glRotatef(Gauss(40, 70), 0, 1, 0);
		drawTree(n - 1);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0, 0, -H[n] * Gauss(0.0, 0.4));
		glRotatef(Gauss(260, 320), 0, 0, 1);
		glRotatef(Gauss(40, 70), 0, 1, 0);
		drawTree(n - 1);
		glPopMatrix();
		glRotatef(Gauss(5, 15), 0, 1, 0);
		glRotatef(Gauss(30, 50), 0, 0, 1);
		drawTree(n - 1);
	}
}


//***************************************************

static GLuint textName[3];
char* filename[3] = { "data2\\timg.bmp", "data2\\dixia.bmp", "data2\\door1.bmp" };
Image image[3];

//Skeleton Const
const double BASIC_SIZE = 0.30;
const double STRETCH_SCALE = 0.8;
const double JOINT_SPAN = 1.25;
const double HEAD_RADIUS = 0.05;
const double THIGH_SCALE_X = 0.7;
const double THIGH_SCALE_Y = 0.2;
const double THIGH_SCALE_Z = 0.2;
const double CALF_SCALE_X = 0.8;
const double CALF_SCALE_Y = 0.2;
const double CALF_SCALE_Z = 0.2;
const double FOOT_SCALE_X = 0.5;
const double FOOT_SCALE_Y = 0.15;
const double FOOT_SCALE_Z = 0.2;
const double BODY_SCALE_X = 0.25;
const double BODY_SCALE_Y = 1.25;
const double BODY_SCALE_Z = 0.75;
const double ARM_SCALE_X = 0.45;
const double ARM_SCALE_Y = 0.15;
const double ARM_SCALE_Z = 0.15;
const double FOREARM_SCALE_X = 0.65;
const double FOREARM_SCALE_Y = 0.15;
const double FOREARM_SCALE_Z = 0.15;
const static double PI = acos(-1.0);

//Skeleton Parameter
float grass[4] = {-10.0f,10.0f,-10.0f,10.0f};
float neck[3] = {0.0f,BASIC_SIZE * BODY_SCALE_Y + HEAD_RADIUS,0.0f};
float spine[3] = {0.0f,BASIC_SIZE * BODY_SCALE_Y / 2,0.0f};
float thighL[3] = {BASIC_SIZE * THIGH_SCALE_X / 2,0.0f,BASIC_SIZE * THIGH_SCALE_Z};
float calfL[3] = {BASIC_SIZE * CALF_SCALE_X / 2,0.0f,0.0f};
float thighR[3] = {BASIC_SIZE * THIGH_SCALE_X / 2,0.0f,-BASIC_SIZE * THIGH_SCALE_Z};
float calfR[3] = {BASIC_SIZE * CALF_SCALE_X / 2,0.0f,0.0f};
float armL[3] = {BASIC_SIZE * ARM_SCALE_X / 2,0.0f,BASIC_SIZE * (ARM_SCALE_Z + BODY_SCALE_Z) / 2};
float armR[3] = {BASIC_SIZE * ARM_SCALE_X / 2,0.0f,-BASIC_SIZE * (ARM_SCALE_Z + BODY_SCALE_Z) / 2};

//Relative Parameter
bool left_forward = true;
bool right_forward = false;
bool look_from_left = true;
double floor_move_x = 0.0;
double floor_move_y = 0.0;
double view_stretch = 1.0;
double near_sight = 1.0;
double far_sight = 200.0;
double lookatX = -20.06;
double lookatY = 10;
double lookatZ = 20.06;
double centerX = 0;
double centerY = 0;
double centerZ = 0;
int scr_w;
int scr_h;
int vangle = 0;
float left_thigh_angle = -60;
float left_calf_angle = 30;
float left_foot_angle = 90;
float right_thigh_angle = -120;
float right_calf_angle = 30;
float right_foot_angle = 90;
float left_arm_angle = -90;
float left_forearm_angle = -30;
float right_arm_angle = -75;
float right_forearm_angle = -15;


void readImage(char* fname, int m)
{
	FILE* pfile = NULL;
	fopen_s(&pfile, fname, "rb");
	if (pfile == 0) exit(0);
	//��ȡͼ���С

	fseek(pfile, 0x0012, SEEK_SET);
	fread(&image[m].imagewidth, sizeof(image[m].imagewidth), 1, pfile);
	fread(&image[m].imageheight, sizeof(image[m].imageheight), 1, pfile);
	//�����������ݳ���
	image[m].pixellength = image[m].imagewidth * 3;
	while (image[m].pixellength % 4 != 0) image[m].pixellength++; // �������ݣ�ֱ��pixellength�ǵı���
	image[m].pixellength *= image[m].imageheight;
	//��ȡ��������
	image[m].pixeldata = (GLubyte*)malloc(image[m].pixellength);
	if (image[m].pixeldata == 0) exit(0);
	fseek(pfile, 54, SEEK_SET);
	fread(image[m].pixeldata, image[m].pixellength, 1, pfile);

	//�ر��ļ�
	fclose(pfile);

}
void init()
{
    glClearColor(0.0f,0.0f,0.0f,0.0f);
	glShadeModel(GLU_SMOOTH);
    glEnable(GL_DEPTH_TEST);

	qObj = gluNewQuadric();  //�������μ��������

	GLfloat sun_direction[] = { -100.0, 100.0, 100.0, 0.0 };  //��Դ
	GLfloat sun_intensity[] = { 1.0, 1.0, 1.0, 1.0 };  //�������
	GLfloat ambient_intensity[] = { 0.5, 0.5, 0.5, 1.0 };  //������

	glEnable(GL_LIGHTING);              // Set up ambient light.  
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);

	glEnable(GL_LIGHT0);                // Set up sunlight.  
	glLightfv(GL_LIGHT0, GL_POSITION, sun_direction);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_intensity);

	glEnable(GL_COLOR_MATERIAL);        // Configure glColor().  
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);


	for (int i = 0; i < 3; i++)
	{
		//��ȡͼ���ļ�
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		readImage(filename[i], i);
		
		glGenTextures(1, &textName[i]);
		glBindTexture(GL_TEXTURE_2D, textName[i]);
		//��������
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[i].imagewidth, image[i].imageheight, 0,
			GL_BGR_EXT, GL_UNSIGNED_BYTE, image[i].pixeldata);

		//�����������
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//����������
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);  //����
	}
	
	glDisable(GL_BLEND);
}



void Draw_Cube(GLfloat x1,GLfloat x2,GLfloat y1,GLfloat y2,GLfloat z1,GLfloat z2)  
{//����������ɣ���֪�����������ɹ���˸�����  
	int i;  
	GLfloat vertex[8][3] = {  
		//�˸����㣬��v1-v8  
		x1,y1,z2,  //0
		x2,y1,z2,  //1
		x1,y2,z2,  //2
		x2,y2,z2,  //3
		x1,y1,z1,  //4
		x2,y1,z1,  //5
		x1,y2,z1,  //6
		x2,y2,z1,  //7
	};  
	GLint surface[6][4] = {  
		//v1��Ӧ0,�Դ�����  
		0,1,3,2,  //front
		4,5,7,6,  //back
		2,3,7,6,  //top
		0,1,5,4,  //bottom
		0,2,6,4,  //left
		1,3,7,5   //right
	};
	
	//��ÿ��������ֳ���������� 
	for(i = 0; i < 6; i++)  
	{
		if (i == 2)
			glBindTexture(GL_TEXTURE_2D, textName[0]);
		else
			glBindTexture(GL_TEXTURE_2D, textName[1]);
		glBegin(GL_POLYGON);//ָ�����Ʒ�ʽ��������� GL_POLYGON ��������� GL_LINE_LOOP
		
		glTexCoord2f(0.0, 0.0); glVertex3fv(vertex[surface[i][0]]);
		glTexCoord2f(0.0, 1.0); glVertex3fv(vertex[surface[i][1]]);
		glTexCoord2f(1.0, 1.0); glVertex3fv(vertex[surface[i][2]]);
		glTexCoord2f(1.0, 0.0); glVertex3fv(vertex[surface[i][3]]);
		glEnd();  
	}
	
}  
void display()
{
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat tree_diffuse[] = { 0.3, 0.25, 0.1, 1.0 }; //�������
	GLfloat tree_specular[] = { 0.1 , 0.1, 0.1, 1.0 };  //�����
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glColor3f(0.3f,0.3f,0.3f);

	glPushMatrix();
	glTranslatef(1.0 , 0.0 , 0.0);

	glPopMatrix();
	glColor3f(0.3f,0.3f,0.3f);
	glEnable(GL_TEXTURE_2D);
	Draw_Cube(grass[0], grass[1], -0.6, -0.59, grass[2], grass[3]);//����
	
	glDisable(GL_TEXTURE_2D);
	//��Ԩ��
    //Head
	glPushMatrix();
    glRotatef(vangle,0.0f,1.0f,0.0f);
    glPushMatrix();
        glTranslatef(neck[0],neck[1],neck[2]);
		glutSolidSphere(HEAD_RADIUS,20,20);
    glPopMatrix();
    //Body
    glPushMatrix();
        glTranslatef(spine[0],spine[1],spine[2]);
        glScalef(BODY_SCALE_X,BODY_SCALE_Y,BODY_SCALE_Z);
        glutSolidCube(BASIC_SIZE);
    glPopMatrix();
    glColor3f(0.5f,0.5f,0.5f);
    //Left leg
    glPushMatrix();
        //Hip
        glPushMatrix();
            glTranslatef(0.0f,0.0f,BASIC_SIZE * THIGH_SCALE_Z);
            glutSolidSphere(BASIC_SIZE * THIGH_SCALE_Y  / 2 * JOINT_SPAN,10,10);
        glPopMatrix();
        //Thigh
        glRotatef((GLfloat)left_thigh_angle,0.0f,0.0f,1.0f);
        glTranslatef(thighL[0],thighL[1],thighL[2]);
        glPushMatrix();
            glScalef(THIGH_SCALE_X,THIGH_SCALE_Y,THIGH_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
        //Knee
        glTranslatef(BASIC_SIZE * THIGH_SCALE_X / 2,0.0f,0.0f);
        glutSolidSphere(BASIC_SIZE * THIGH_SCALE_Y / 2 * JOINT_SPAN,10,10);
        //Calf
        glRotatef((GLfloat)left_calf_angle,0.0f,0.0f,1.0f);
        glTranslatef(calfL[0],calfL[1],calfL[2]);
        glPushMatrix();
            glScalef(CALF_SCALE_X,CALF_SCALE_Y,CALF_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
        //Foot
        glTranslatef(BASIC_SIZE * CALF_SCALE_X / 2,0.0f,0.0f);
        glTranslatef(-BASIC_SIZE * FOOT_SCALE_X / 2 + BASIC_SIZE * THIGH_SCALE_Y,-BASIC_SIZE * CALF_SCALE_Y / 2,0.0f);
        glRotatef((GLfloat)left_foot_angle,0.0f,0.0f,1.0f);
        glPushMatrix();
            glScalef(FOOT_SCALE_X,FOOT_SCALE_Y,FOOT_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
    glPopMatrix();
    //Left Arm
    glPushMatrix();
    glTranslatef(0.0f,BASIC_SIZE * BODY_SCALE_Y,0.0f);
        //Arm
        glRotatef((GLfloat)left_arm_angle,0.0f,0.0f,1.0f);
        glTranslatef(armL[0],armL[1],armL[2]);
        glPushMatrix();
            glScalef(ARM_SCALE_X,ARM_SCALE_Y,ARM_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
        //Elbow
        glTranslatef(BASIC_SIZE * ARM_SCALE_X / 2,0.0f,0.0f);
        glutSolidSphere(BASIC_SIZE * ARM_SCALE_Y / 2 * JOINT_SPAN,10,10);
        //Forearm
        glRotatef((GLfloat)left_forearm_angle,0.0f,0.0f,1.0f);
        glTranslatef(BASIC_SIZE * FOREARM_SCALE_X / 2,0.0f,0.0f);
        glPushMatrix();
            glScalef(FOREARM_SCALE_X,FOREARM_SCALE_Y,FOREARM_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
    glPopMatrix();
    glColor3f(0.7f,0.7f,0.7f);
    //Right leg
    glPushMatrix();
        //Hip
        glPushMatrix();
            glTranslatef(0.0f,0.0f,-BASIC_SIZE * THIGH_SCALE_Z);
            glutSolidSphere(BASIC_SIZE * THIGH_SCALE_Y / 2 * JOINT_SPAN,10,10);
        glPopMatrix();
        //Thigh
        glRotatef((GLfloat)right_thigh_angle,0.0f,0.0f,1.0f);
        glTranslatef(thighR[0],thighR[1],thighR[2]);
        glPushMatrix();
            glScalef(THIGH_SCALE_X,THIGH_SCALE_Y,THIGH_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
        //Knee
        glTranslatef(BASIC_SIZE * THIGH_SCALE_X / 2,0.0f,0.0f);
        glutSolidSphere(BASIC_SIZE * THIGH_SCALE_Y / 2 * JOINT_SPAN,10,10);
        //Calf
        glRotatef((GLfloat)right_calf_angle,0.0f,0.0f,1.0f);
        glTranslatef(calfR[0],calfR[1],calfR[2]);
        glPushMatrix();
            glScalef(CALF_SCALE_X,CALF_SCALE_Y,CALF_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
        //Foot
        glTranslatef(BASIC_SIZE * CALF_SCALE_X / 2,0.0f,0.0f);
        glTranslatef(-BASIC_SIZE * FOOT_SCALE_X / 2 + BASIC_SIZE * THIGH_SCALE_Y,-BASIC_SIZE * CALF_SCALE_Y / 2,0.0f);
        glRotatef((GLfloat)right_foot_angle,0.0f,0.0f,1.0f);
        glPushMatrix();
            glScalef(FOOT_SCALE_X,FOOT_SCALE_Y,FOOT_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
    glPopMatrix();
    //Right Arm
    glPushMatrix();
    glTranslatef(0.0f,BASIC_SIZE * BODY_SCALE_Y,0.0f);
        //Arm
        glRotatef((GLfloat)right_arm_angle,0.0f,0.0f,1.0f);
        glTranslatef(armR[0],armR[1],armR[2]);
        glPushMatrix();
            glScalef(ARM_SCALE_X,ARM_SCALE_Y,ARM_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
        //Elbow
        glTranslatef(BASIC_SIZE * ARM_SCALE_X / 2,0.0f,0.0f);
        glutSolidSphere(BASIC_SIZE * ARM_SCALE_Y / 2 * JOINT_SPAN,10,10);
        //Forearm
        glRotatef((GLfloat)right_forearm_angle,0.0f,0.0f,1.0f);
        glTranslatef(BASIC_SIZE * FOREARM_SCALE_X / 2,0.0f,0.0f);
        glPushMatrix();
            glScalef(FOREARM_SCALE_X,FOREARM_SCALE_Y,FOREARM_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
	glPushMatrix();
	glTranslatef(house[0] , -0.6 , house[1]-8.0);
	display2();
	glPopMatrix();
	glPushMatrix();  //��һ����
	glColor3f(1.0 , 1.0 , 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, tree_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, tree_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 8);
	glTranslatef(tree[0]-4.5, -0.6, tree[1]-5.0);
	glRotatef(-90.0 , 1.0 , 0.0 , 0.0);
	setData();
	drawTree(M);
	glPopMatrix();

	glPushMatrix();  //�ڶ�����
	glColor3f(0.0 , 1.0 , 1.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, tree_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, tree_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 8);
	glTranslatef(tree[0]+3.5, -0.6, tree[1]+5.0);
	glRotatef(-90.0 , 1.0 , 0.0 , 0.0);
	setData();
	drawTree(M);
	glPopMatrix();

	glPushMatrix();  //��������
	glColor3f(0.0 , 1.0 , 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, tree_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, tree_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 8);
	glTranslatef(tree[0]-3.5, -0.6, tree[1]+5.0);
	glRotatef(-90.0 , 1.0 , 0.0 , 0.0);
	setData();
	drawTree(M);
	glPopMatrix();
	
    glFlush();
    glutSwapBuffers();
}

void refresh(int c)
{
    centerY = -(1 - sin(-left_thigh_angle / 180.0 * PI)) * BASIC_SIZE * THIGH_SCALE_X + BASIC_SIZE * FOOT_SCALE_Y / 2;
    if (left_thigh_angle < -120)
    {
        left_forward = false;
    }
    else if (left_thigh_angle > -60)
    {
        left_forward = true;
    }
    if (right_thigh_angle < -120)
    {
        right_forward = false;
    }
    else if (right_thigh_angle > -60)
    {
        right_forward = true;
    }
    if (left_forward)
    {
        left_thigh_angle--;
        if (left_thigh_angle < -90)
            left_calf_angle++;
        else left_calf_angle--;
        left_arm_angle += 0.25;
        left_forearm_angle += 0.5;
    }
    else
    {
        left_thigh_angle++;
        if (left_thigh_angle <= -90)
          left_calf_angle--;
        else left_calf_angle++;
        left_arm_angle -= 0.25;
        left_forearm_angle -= 0.5;
    }
    if (right_forward)
    {
        right_thigh_angle--;
        if (right_thigh_angle < -90)
          right_calf_angle++;
        else right_calf_angle--;
        right_arm_angle += 0.25;
        right_forearm_angle += 0.5;
    }
    else
    {
        right_thigh_angle++;
        if (right_thigh_angle <= -90)
          right_calf_angle--;
        else right_calf_angle++;
        right_arm_angle -= 0.25;
        right_forearm_angle -= 0.5;
    }

	if((vangle >= 0 && vangle <= 360) || (vangle < 0 && vangle > -360))
	{
		if(grass[0] <= 0.0 && grass[3] >= 0.0 && grass[1] >= 0.0)
		{
			grass[0] += speed*cos((double)vangle / 180.0 * PI);
			grass[1] += speed*cos((double)vangle / 180.0 * PI);
			grass[2] -= speed*sin((double)vangle / 180.0 * PI);
			grass[3] -= speed*sin((double)vangle / 180.0 * PI);

			house[0] += speed*cos((double)vangle / 180.0 * PI);
			house[1] -= speed*sin((double)vangle / 180.0 * PI);

			tree[0] += speed*cos((double)vangle / 180.0 * PI);
			tree[1] -= speed*sin((double)vangle / 180.0 * PI);
		}
		else if(grass[0] <= 0 && grass[0] >= -10.0)
		{
			grass[0] += speed*cos((double)vangle / 180.0 * PI);
			grass[1] += speed*cos((double)vangle / 180.0 * PI);
		}
		else if(grass[3] >= 0)
		{
			grass[2] -= speed*sin((double)vangle / 180.0 * PI);
			grass[3] -= speed*sin((double)vangle / 180.0 * PI);
		}

		if(grass[0] > 0)
		{
			grass[0] = 0.0;
		}
		if(grass[1] < 0)
		{
			grass[1]  = 0.0;
		}
		if(grass[2] > 0)
		{
			grass[2]  = 0.0;
		}
		if(grass[3] < 0)
		{
			grass[3] = 0.0;
		}
	}
    glutPostRedisplay();
    glutTimerFunc(DELAY,refresh,0);
}

void reshape(int w,int h)
{
    scr_w = w;
    scr_h = h;
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0,(GLfloat)scr_w / (GLfloat)scr_h,near_sight * view_stretch,far_sight * view_stretch);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(lookatX,lookatY,lookatZ,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
}

void passiveMotion(int x,int y)
{
    lookatX = -1.5 + (double)x / scr_w * 3;
    lookatY = 1 - (double)y / scr_h * 2;
	if (look_from_left)
		lookatZ = sqrt(2.25 - lookatX * lookatX);
	else lookatZ = -sqrt(2.25 - lookatX * lookatX);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(lookatX * view_stretch,lookatY * view_stretch,lookatZ * view_stretch,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
}

void mouse(int button,int state,int x,int y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)
			{
				if (near_sight * view_stretch > 0.5)
					view_stretch *= STRETCH_SCALE;
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluPerspective(75.0,(GLfloat)scr_w / (GLfloat)scr_h,near_sight * view_stretch,far_sight * view_stretch);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				gluLookAt(lookatX * view_stretch,lookatY * view_stretch,lookatZ * view_stretch,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
			}
			break;
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN)
			{
				if (far_sight * view_stretch < 4000.0)
					view_stretch /= STRETCH_SCALE;
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluPerspective(75.0,(GLfloat)scr_w / (GLfloat)scr_h,near_sight * view_stretch,far_sight * view_stretch);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				gluLookAt(lookatX * view_stretch,lookatY * view_stretch,lookatZ * view_stretch,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
			}
			break;
	}
}
void control(unsigned char key,int x,int y)
{
    switch(key)
    {
        case 'a':
            vangle = (vangle + 1) % 360;
            break;
        case 'd':
            vangle = (vangle - 1) % 360;
            break;
        case 'w':
			vangle = -(180 - vangle) % 360;
			break;
        case 's':
            vangle = -(180 - vangle) % 360;
            break;
		case 32:
			look_from_left = !look_from_left;
			if (look_from_left)
				lookatZ = sqrt(2.25 - lookatX * lookatX);
			else lookatZ = -sqrt(2.25 - lookatX * lookatX);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(lookatX * view_stretch,lookatY * view_stretch,lookatZ * view_stretch,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
			break;
		case 27:
			exit(0);
        default:
            break;
    }
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("��Ԩ��������");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(passiveMotion);
	glutMouseFunc(mouse);
    glutKeyboardFunc(control);
    refresh(0);
    glutMainLoop();
    return 0;
}
