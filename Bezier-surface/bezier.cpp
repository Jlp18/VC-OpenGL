#include<windows.h>
#include<gl\glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define ROUND(a) int(a + 0.5)

double Fei = 0;
double Thta = 0;

int i, j;

struct P2D{
	int x, y;
};

struct P3D{
	int x, y, z;
};

P2D P2d[4][4];
P3D P3d[4][4], T[4][4];
double MT[4][4];

void Init(){
	glColor3f(1.0, 1.0, 1.0);
	P3d[0][0].x = 100;
	P3d[0][0].y = 20;
	P3d[0][0].z = 0;
	P3d[0][1].x = 150;
	P3d[0][1].y = 0;
	P3d[0][1].z = 100;
	P3d[0][2].x = 50;
	P3d[0][2].y = -130;
	P3d[0][2].z = 100;
	P3d[0][3].x = 0;
	P3d[0][3].y = 250;
	P3d[0][3].z = 50;
	P3d[1][0].x = 150;
	P3d[1][0].y = 100;
	P3d[1][0].z = -100;
	P3d[1][1].x = 100;
	P3d[1][1].y = 30;
	P3d[1][1].z = 100;
	P3d[1][2].x = 50;
	P3d[1][2].y = -40;
	P3d[1][2].z = 100;
	P3d[1][3].x = 0;
	P3d[1][3].y = -110;
	P3d[1][3].z = 100;
	P3d[2][0].x = 140;
	P3d[2][0].y = -280;
	P3d[2][0].z = 90;
	P3d[2][1].x = 80;
	P3d[2][1].y = 110;
	P3d[2][1].z = 120;
	P3d[2][2].x = 30;
	P3d[2][2].y = 30;
	P3d[2][2].z = 130;
	P3d[2][3].x = -50;
	P3d[2][3].y = -100;
	P3d[2][3].z = 150;
	P3d[3][0].x = 150;
	P3d[3][0].y = 350;
	P3d[3][0].z = 30;
	P3d[3][1].x = 50;
	P3d[3][1].y = 200;
	P3d[3][1].z = 150;
	P3d[3][2].x = 0;
	P3d[3][2].y = 50;
	P3d[3][2].z = 200;
	P3d[3][3].x = -100;
	P3d[3][3].y = 100;
	P3d[3][3].z = 100;
}

void Transform3DTo2D(){
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			P2d[i][j].x = P3d[i][j].y - P3d[i][j].x / sqrtf(2);
			P2d[i][j].y = -P3d[i][j].z + P3d[i][j].x / sqrtf(2);
		}
	}
}

void KeepOriginalMatrix(P3D Orig[4][4], P3D Dest[4][4]){
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			Dest[i][j].x = Orig[i][j].x;
			Dest[i][j].y = Orig[i][j].y;
			Dest[i][j].z = Orig[i][j].z;
		}
	}
}

void Calculate1(double M0 [][4], P3D P0 [][4]){
	KeepOriginalMatrix(P0, T);
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			P3d[i][j].x = M0[i][0] * T[0][j].x + M0[i][1] * T[1][j].x + M0[i][2] * T[2][j].x + M0[i][3] * T[3][j].x;
			P3d[i][j].y = M0[i][0] * T[0][j].y + M0[i][1] * T[1][j].y + M0[i][2] * T[2][j].y + M0[i][3] * T[3][j].y;
			P3d[i][j].z = M0[i][0] * T[0][j].z + M0[i][1] * T[1][j].z + M0[i][2] * T[2][j].z + M0[i][3] * T[3][j].z;
		}
	}
}

void Calculate2(P3D P0 [][4], double M1 [][4]){
	KeepOriginalMatrix(P0, T);
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			P3d[i][j].x = T[i][0].x * M1[0][j] + T[i][1].x * M1[1][j] + T[i][2].x * M1[2][j] + T[i][3].x * M1[3][j];
			P3d[i][j].y = T[i][0].y * M1[0][j] + T[i][1].y * M1[1][j] + T[i][2].y * M1[2][j] + T[i][3].y * M1[3][j];
			P3d[i][j].z = T[i][0].z * M1[0][j] + T[i][1].z * M1[1][j] + T[i][2].z * M1[2][j] + T[i][3].z * M1[3][j];
		}
	}
}

void MatrixRotate(double M0 [][4]){
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			MT[j][i] = M0[i][j];
		}
	}
}

void myDisplay(){
	glClear(GL_COLOR_BUFFER_BIT);
	double x = 0;
	double y = 0;
	double v = 0;
	double u = 0;
	double u1 = 0;
	double u2 = 0;
	double u3 = 0;
	double u4 = 0;
	double v1 = 0;
	double v2 = 0;
	double v3 = 0;
	double v4 = 0;
	double M[4][4] = { { -1, 3, -3, 1 }, { 3, -6, 3, 0 }, { -3, 3, 0, 0 }, { 1, 0, 0, 0 } };
	for (u = 0; u <= 1; u += 0.01){
		for (v = 0; v <= 1; v += 0.01){
			u1 = u*u*u;
			u2 = u*u;
			u3 = u;
			u4 = 1;
			v1 = v*v*v;
			v2 = v*v;
			v3 = v;
			v4 = 1;
			x = (u1 * P2d[0][0].x + u2 * P2d[1][0].x + u3 * P2d[2][0].x + u4 * P2d[3][0].x) * v1 + (u1 * P2d[0][1].x + u2 * P2d[1][1].x + u3 * P2d[2][1].x + u4 * P2d[3][1].x) * v2 + (u1 * P2d[0][2].x + u2 * P2d[1][2].x + u3 * P2d[2][2].x + u4 * P2d[3][2].x) * v3 + (u1 * P2d[0][3].x + u2 * P2d[1][3].x + u3 * P2d[2][3].x + u4 * P2d[3][3].x) * v4;
			y = (u1 * P2d[0][0].y + u2 * P2d[1][0].y + u3 * P2d[2][0].y + u4 * P2d[3][0].y) * v1 + (u1 * P2d[0][1].y + u2 * P2d[1][1].y + u3 * P2d[2][1].y + u4 * P2d[3][1].y) * v2 + (u1 * P2d[0][2].y + u2 * P2d[1][2].y + u3 * P2d[2][2].y + u4 * P2d[3][2].y) * v3 + (u1 * P2d[0][3].y + u2 * P2d[1][3].y + u3 * P2d[2][3].y + u4 * P2d[3][3].y) * v4;
			glPointSize(3);
			glBegin(GL_POINTS);
			glColor3f(1.0, 1.0, 1.0);
			glVertex2f(ROUND(1000 / 2 + x), ROUND(2000 / 2 + y));
			glutSwapBuffers();
			glEnd();
		}
	}
	glPopMatrix();
	glFlush();
}

void SpecialKeys(int key, int x, int y){
	if (key == GLUT_KEY_UP)
		Fei--;
	if (key == GLUT_KEY_DOWN)
		Fei++;
	if (key == GLUT_KEY_LEFT)
		Thta--;
	if (key == GLUT_KEY_RIGHT)
		Thta++;
	glutPostRedisplay();
}

void reshape(int w, int h){
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
}

int main(int argc, char *argv []){
	Init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1550, 820);
	glutCreateWindow(" ");
	Transform3DTo2D();
	glutDisplayFunc(&myDisplay);
	glutSpecialFunc(SpecialKeys);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}