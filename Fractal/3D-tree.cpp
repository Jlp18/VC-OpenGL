#include <GL/glut.h>

#include "3D-tree.h"

GLint WindW = 800;
GLint WindH = 600;
GLfloat oldx, oldy;//����ƶ�����
GLfloat xangle = 15.0f;
GLfloat yangle = -15.0f;//��ת����  



GLfloat PI = 3.14;
string way[3]; //�ṩ���ɹ��� 
string rule, temprule;

float len; //������
float len1;
//float Alphax;
float Alphay;
float Alphaz;
int k;   //������
int n;  //��������

Node   stack[150];
int    stackpointer;

static GLuint textName[3];
char* filename[3] = { "data2\\timg.bmp", "data2\\wall.bmp", "data2\\door1.bmp" };
Image image[3];

void Draw_Cube(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat z1, GLfloat z2);
void LSystemRule();
void drawGrass();

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
/////////////////////////////////
void  init()
{
	//glClearColor(0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-25.0, 25.0, -25.0, 25.0, -25.0, 25.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	
	LSystemRule();
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

void LSystemRule()
{
	//��ʼ��
	way[0] = "FA[+X][-&X]-%XB";
	len = 10;
	Alphaz = 30;
	Alphay = 60;
	n = 8;
	k = 0;
	stackpointer = 0;//ջ��ָ��
	for (int i = 0; i <150; i++)
	{
		stack[i].x = 0.0;
		stack[i].y = 0.0;
		stack[i].z = 0.0;
		stack[i].directionz = 0;
		stack[i].directiony = 0;
	}
	temprule = way[0];
	for (int i = 1; i <= n; i++)
	{
		int curlen = temprule.length();
		int pos = 0, j = 0;
		while (j < curlen)
		{
			if (temprule[j] == 'X')//�����������е�F�滻���ķ�ģ��
			{
				rule +=  way[0];
				j++;
				pos = rule.length() - 1;
			}
			else//����ת��
			{
				rule += temprule[j];
				pos++;
				j++;
			}
		}
		temprule = rule;
		rule.clear();
	}
	rule = temprule;//������֮����ķ�����
} 

void drawGrass()
{
	Node  Nextnode, Curnode;
	Curnode.x = 0.0;
	Curnode.y = 0.0;
	Curnode.z = 0.0;
	Curnode.directionz = 85;
	Curnode.directiony = 0;
	int length = rule.length();
	int  i = 0;
	
	glTranslatef(0.0, -15.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	Draw_Cube(-15.0, 15.0, -2.0, -0.0, -15.0, 15.0);//����
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	while (i < length)
	{
		switch (rule[i])
		{
		case 'F':
			if(len<=0.9)
			{
				glLineWidth(2);
				glColor3f((float)242 / 255, (float)128 / 255, (float)191 / 255);
				//glColor3f((float)34/255, (float)139/255, (float)34/255);
			}
			else if(len>0.9&&len<4.0)
			{
				glLineWidth(2);
				//glColor3f((float)210/255, (float)180/255, (float)140/255);
				glColor3f((float)34 / 255, (float)139 / 255, (float)34 / 255);
			}
			//else if(len>1.8&&len<3)
				//glColor3f((float)34/255, (float)139/255, (float)34/255);
			else
			{
				glLineWidth(5);
				glColor3f((float)62/255, (float)42/255, (float)45/255);
			}
			Nextnode.x = Curnode.x + len * cos(Curnode.directionz * PI / 180) * cos(Curnode.directiony * PI / 180);
			Nextnode.y = Curnode.y + len * sin(Curnode.directionz * PI / 180);
			Nextnode.z = Curnode.z - len * cos(Curnode.directionz * PI / 180) * sin(Curnode.directiony * PI / 180);
			Nextnode.directionz = Curnode.directionz;
			Nextnode.directiony = Curnode.directiony;
			glBegin(GL_LINES);
			glVertex3f(Curnode.x, Curnode.y, Curnode.z);
			glVertex3f(Nextnode.x, Nextnode.y, Nextnode.z);
			glEnd();
			Curnode = Nextnode;
			k++;
			break;
		case 'X':
			glColor3f((float)34/255, (float)139/255, (float)34/255);
			glLineWidth(1);
			Nextnode.x = Curnode.x + len1 * cos(Curnode.directionz * PI / 180) * cos(Curnode.directiony * PI / 180);
			Nextnode.y = Curnode.y + len1 * sin(Curnode.directionz * PI / 180);
			Nextnode.z = Curnode.z - len1 * cos(Curnode.directionz * PI / 180) * sin(Curnode.directiony * PI / 180);
			Nextnode.directionz = Curnode.directionz;
			Nextnode.directiony = Curnode.directiony;
			glBegin(GL_LINES);
			glVertex3f(Curnode.x, Curnode.y, Curnode.z);
			glVertex3f(Nextnode.x, Nextnode.y, Nextnode.z);
			glEnd();
			Curnode = Nextnode;
			break;
		case 'A':
			len=len*7/10;
			len1=len;
			break;
		case 'B':
			len=len*10/7;
			break;
		case '[':
			stack[stackpointer] = Curnode;
			stackpointer++;
			break;
		case ']':
			Curnode = stack[stackpointer - 1];
			stackpointer--;
			break;
		case '+':
			Curnode.directionz = Curnode.directionz + Alphaz;
			break;
		case '-':
			Curnode.directionz = Curnode.directionz - Alphaz;
			break;
		case '&':
			Curnode.directiony = Curnode.directiony + Alphay;
			break;
		case '%':
			Curnode.directiony = Curnode.directiony - Alphay;
			break;
		default:
			;
		}
		i++;
	}
	glPopMatrix();
	
}


void  display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glLoadIdentity();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	//glPushMatrix();
	glRotatef(xangle, 1.0, 0.0, 0.0);
	glRotatef(yangle, 0.0, 1.0, 0.0);//��ת
	drawGrass();
	//glPopMatrix();
	glFlush();
	glutSwapBuffers();
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	GLfloat f = 25.0f;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-f, f, -f*(GLfloat)h / (GLfloat)w,
		f*(GLfloat)h / (GLfloat)w, -f, f);
	else
		glOrtho(-f*(GLfloat)w / (GLfloat)h,
		f*(GLfloat)w / (GLfloat)h, -f, f, -f, f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int btn, int state, int x, int y)
{
	if ((btn == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)){
		oldx = x; oldy = y;
	}
}

void motion(int x, int y)
{
		GLint deltax = oldx - x;
		GLint deltay = oldy - y;
		yangle += 360 * (GLfloat)deltax / (GLfloat)WindW;//������Ļ����껬���ľ�����������ת�ĽǶ�  
		xangle += 360 * (GLfloat)deltay / (GLfloat)WindH;
		oldx = x;//��¼��ʱ��������꣬�����������,������ת�����ɿ� 
		oldy = y;
		glutPostRedisplay();
}

int  main(int  argc, char  **argv)
{
	glutInit(&argc, argv);    
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Cayley tree 3D");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);    
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	init();	 
	glutMainLoop(); 
	return 0; 
}
