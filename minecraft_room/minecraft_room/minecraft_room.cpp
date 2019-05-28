/*****************************************************************************
FILE : submit.c (Assignment 1)
NOTE : you have to implement functions in this file
*****************************************************************************/
/*****************************************************************************
Student Information
Student ID:   161620306
*****************************************************************************/

#include "pch.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

void init(void);
void display(void);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void idle(void);

void setLight0();
/* Global Variables */
GLfloat light_pos0[] = { 0, 3, -10, 1 };
GLfloat light_dir0[] = { 0, 0, -1 };
GLfloat light_cutoff0 = 120;
GLfloat light_amb0[] = { 0.4, 0.4, 0.4, 1.0 };
GLfloat light_dif0[] = { 0.4, 0.4, 0.4, 1.0 };
GLfloat light_spc0[] = { 1.0, 1.0, 1.0, 1.0 };

GLfloat light_dir1[] = { 0, -1.0f, 0 };
GLfloat light_cutoff1 = 20;
GLfloat light_amb1[] = { 0.15f, 0.1f, 0.1f, 1.0f };
GLfloat light_dif1[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat light_spc1[] = { 0.1f, 0.1f, 0.1f, 1.0f };

bool aRoomLight = false;
bool chestOpen = false;
bool createCreeper = false;
bool toKillACreeper = false;
bool dropEXP = false;
bool zombieScale = false;
int counter;
unsigned int shinningEXP = 0;
GLfloat creepX = 0.0, creepY = 0.0, creepZ = 0.0;
GLfloat cHeadRotate = 0.0;
GLfloat cBodyRotate = 0.0;
GLfloat cFeetRotate = 45.0;
GLfloat zombie = 1.2;

//Color matrice and Material matrice
GLubyte textWall[16][16][4] = {
	{{81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}},{{102, 79, 47, 255}, {102, 79, 47, 255}, {102, 79, 47, 255}, {102, 79, 47, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {81, 60, 34, 255}, {102, 79, 47, 255}, {102, 79, 47, 255}, {81, 60, 34, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}},{{128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {102, 79, 47, 255}, {128, 94, 54, 255}, {102, 79, 47, 255},{102, 79, 47, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {81, 60, 34, 255}, {102, 79, 47, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}},{{128, 94, 54, 255}, {106, 81, 49, 255}, {106, 81, 49, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}},{{81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}},{{128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255},{102, 79, 47, 255},{106, 81, 49, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {106, 81, 49, 255}, {81, 60, 34, 255}},{{128, 94, 54, 255}, {102, 79, 47, 255}, {102, 79, 47, 255},{106, 81, 49, 255},{106, 81, 49, 255}, {102, 79, 47, 255}, {128, 94, 54, 255}, {106, 81, 49, 255}, {106, 81, 49, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {102, 79, 47, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}},{{128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {81, 60, 34, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {102, 79, 47, 255}, {102, 79, 47, 255}, {128, 94, 54, 255}, {106, 81, 49, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}},{{81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}},{{102, 79, 47, 255}, {102, 79, 47, 255}, {102, 79, 47, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {81, 60, 34, 255}, {102, 79, 47, 255}, {102, 79, 47, 255}, {102, 79, 47, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {102, 79, 47, 255}, {128, 94, 54, 255}},{{128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {102, 79, 47, 255}, {128, 94, 54, 255}, {102, 79, 47, 255},{102, 79, 47, 255}, {128, 94, 54, 255}, {102, 79, 47, 255}, {102, 79, 47, 255}, {106, 81, 49, 255}, {128, 94, 54, 255},{128, 94, 54, 255}, {102, 79, 47, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}},{{128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {102, 79, 47, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {81, 60, 34, 255}},{{81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}, {81, 60, 34, 255}},{{128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255},{102, 79, 47, 255},{106, 81, 49, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}},{{128, 94, 54, 255}, {128, 94, 54, 255}, {102, 79, 47, 255},{102, 79, 47, 255},{102, 79, 47, 255}, {81, 60, 34, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {102, 79, 47, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}},{{128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {102, 79, 47, 255}, {128, 94, 54, 255}, {102, 79, 47, 255},{128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}, {128, 94, 54, 255}},
};
GLubyte textCreep[8][8][4] = {
	{{76, 175, 80, 255}, {92, 139, 88, 255}, {12, 79, 17, 255}, {165, 214, 167, 255}, {129, 199, 132, 255}, {12, 79, 17, 255}, {76, 175, 80, 255}, {101, 156, 103, 255}},{{165, 214, 167, 255}, {92, 136, 87, 255}, {40, 43, 40,255}, {40, 43, 40,255}, {40, 43, 40,255}, {40, 43, 40,255}, {92, 136, 87, 255}, {129, 199, 132, 255}},{{76, 175, 80, 255}, {235, 255, 233, 255}, {12, 79, 17, 255}, {40, 43, 40,255}, {40, 43, 40,255}, {12, 79, 17, 255}, {129, 199, 132, 255}, {76, 175, 80, 255}},{{27, 94, 32, 255}, {76, 175, 80, 255}, {165, 214, 167, 255}, {12, 79, 17, 255}, {12, 79, 17, 255}, {76, 175, 80, 255}, {76, 175, 80, 255}, {101, 156, 103, 255}},{{76, 175, 80, 255}, {39, 99, 44, 255}, {40, 43, 40,255}, {76, 179, 80, 255}, {235, 255, 233, 255}, {40, 43, 40,255}, {39, 99, 44, 255}, {129, 199, 132, 255}},{{165, 214, 167, 255}, {12, 79, 17, 255}, {45, 99, 39, 255}, {78, 175, 80, 255}, {129, 199, 132, 255}, {45, 99, 39, 255}, {12, 79, 17, 255}, {235, 255, 233, 255}},{{129, 199, 132, 255}, {76, 175, 80, 255}, {165, 214, 167, 255}, {235, 255, 233, 255}, {165, 214, 167, 255}, {235, 255, 233, 255}, {76, 175, 80, 255}, {76, 175, 80, 255}},{{27, 94, 32, 255}, {76, 175, 80, 255}, {235, 255, 233, 255}, {165, 214, 167, 255}, {76, 175, 80, 255}, {165, 214, 167, 255}, {76, 175, 80, 255}, {129, 199, 132, 255}},
};
GLfloat matObsidian[3][4] = { { 0.053750, 0.050000, 0.066250, 0.820000 },{ 0.182750, 0.170000, 0.225250, 0.820000 },{ 0.232741, 0.228634, 0.246435, 0.820000 } };
GLfloat matWhite[] = { 1, 1, 1, 1 };
GLfloat matBlack[] = { 0.2, 0.2, 0.2, 1 };
GLfloat matYellow[] = { 1, 1, 0, 1 };
GLfloat matGreen[] = { 0, 1, 0, 1 };
GLfloat matWooden[3][4] = { { 0.191250, 0.073500, 0.022500, 1.000000 },{ 0.703800, 0.270480, 0.082800, 1.000000 },{ 0.256777, 0.137622, 0.086014, 1.000000 } };
GLfloat matWax[3][4] = { { 0.105882, 0.058824, 0.113725, 1.000000 },{ 0.827451, 0.870588, 0.841176, 1.000000 },{ 0.733333, 0.733333, 0.921569, 1.000000 } };
GLfloat matBronze[3][4] = { { 0.212500, 0.127500, 0.054000, 1.000000 },{ 0.714000, 0.428400, 0.181440, 1.000000 },{ 0.393548, 0.271906, 0.166721, 1.000000 } };
GLfloat matGolden[3][4] = { { 0.347250, 0.224500, 0.064500, 1.000000 },{ 0.446150, 0.314300, 0.090300, 1.000000 },{ 0.897357, 0.723991, 0.208006, 1.000000 } };

void setLight0()
{
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_dir0);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, light_cutoff0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_spc0);
}

void setLight1(bool flag, GLfloat *pos)
{
	glLightfv(GL_LIGHT1, GL_POSITION, pos);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 10);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 8);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_amb1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_dif1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_spc1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_dir1);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, light_cutoff1);

	if (flag)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);
}

void DrawCube(GLfloat x, GLfloat y, GLfloat z, GLfloat s, GLfloat *l = NULL, GLfloat *r = NULL, GLfloat *e = NULL) {
	glPushMatrix();
	glTranslatef(x, y, z);
	if (r)
		glRotatef(r[0], r[1], r[2], r[3]);
	if (l)
		glScalef(l[0], l[1], l[2]);


	//Draw decorating edges
	if (e)
	{
		glutSolidCube(s*0.99);
		glTranslatef(-s / 2, -s / 2, -s / 2);
		glColor3f(e[0], e[1], e[2]);
		glLineWidth(e[3]);
		glBegin(GL_LINE_STRIP);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(s, 0.0, 0.0);
		glVertex3f(s, s, 0.0);
		glVertex3f(0.0, s, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, s, 0.0);
		glVertex3f(0.0, s, s);
		glVertex3f(0.0, 0.0, s);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(s, s, s);
		glVertex3f(0.0, s, s);
		glVertex3f(0.0, 0.0, s);
		glVertex3f(s, 0.0, s);
		glVertex3f(s, s, s);
		glVertex3f(s, s, 0.0);
		glVertex3f(s, 0.0, 0.0);
		glVertex3f(s, 0.0, s);
		glVertex3f(s, s, s);
		glEnd();
	}
	else glutSolidCube(s);
	glFlush();
	glPopMatrix();
}

void DrawWeb(GLfloat x, GLfloat y, GLfloat z, GLfloat s, GLfloat r = 0) {
	glPushMatrix();
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(3, 0xffff);
	glTranslatef(x, y, z);
	glRotatef(r, 0, 1, 0);
	glLineWidth(1.8);
	glutWireCone(s, 0.1, 8, 3);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex3f(-s, s, 0);
	glVertex3f(s, -s, 0);
	glVertex3f(-s, -s, 0);
	glVertex3f(s, s, 0);
	glEnd();
	glRotatef(90, 0, 1, 0);
	glLineWidth(1.8);
	glutWireCone(s, 0.1, 8, 3);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex3f(-s, s, 0);
	glVertex3f(s, -s, 0);
	glVertex3f(-s, -s, 0);
	glVertex3f(s, s, 0);
	glEnd();
	glFlush();
	glPopMatrix();
}

void DrawEXP(GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix();
	if (shinningEXP % 2)
		glMaterialfv(GL_FRONT, GL_EMISSION, matYellow);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, matGreen);
	glMaterialf(GL_FRONT, GL_SHININESS, 100);
	glColor3f(0.2, 0.8, 0.2);
	glTranslatef(x, y, z);
	glutSolidSphere(0.15, 10, 10);
	glPopMatrix();
}

void init(void) // All Setup For OpenGL Goes Here
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE);
}

void display(void) // Here's Where We Do All The Drawing
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// TODO:
	// Place light source here
	GLfloat pos[] = { -14, 3, -10, 1.0 }, pos2[] = { 14, 3, -10, 1.0 };
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	setLight0();
	setLight1(aRoomLight, pos);
	setLight1(aRoomLight, pos2);

	// TODO:
	// Draw walls and objects here


	/*Walls*/
	glColor3ub(186, 138, 69);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matWax[0]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matWax[1]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWax[2]);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glMaterialf(GL_FRONT, GL_SHININESS, 9.846150);
	glBegin(GL_QUADS);					//back wall
	glVertex3f(16, 12, -20);
	glVertex3f(-16, 12, -20);
	glVertex3f(-16, -6, -20);
	glVertex3f(16, -6, -20);
	glEnd();
	glColor3ub(225, 168, 85);
	glBegin(GL_QUADS);
	glVertex3f(13, 12, -20);
	glVertex3f(13, 12, 10);
	glVertex3f(-13, 12, 10);
	glVertex3f(-13, 12, -20);
	glEnd();
	glColor3ub(218, 163, 83);
	glBegin(GL_QUADS);
	glVertex3f(-13, 12, -20);
	glVertex3f(-13, 12, 40);
	glVertex3f(-13, -6, 40);
	glVertex3f(-13, -6, -20);
	glEnd();
	glColor3ub(218, 163, 83);
	glBegin(GL_QUADS);
	glVertex3f(13, -6, -20);
	glVertex3f(13, -6, 40);
	glVertex3f(13, 12, 40);
	glVertex3f(13, 12, -20);
	glEnd();

	/*Floor*/
	GLuint textureName;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &textureName);
	glBindTexture(GL_TEXTURE_2D, textureName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 16, 16, 0, GL_RGBA, GL_UNSIGNED_BYTE, textWall);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, textureName);

	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(6, 6); glVertex3f(-13, -6, -20);
	glTexCoord2f(0, 6); glVertex3f(-13, -6, 40);
	glTexCoord2f(0, 0); glVertex3f(13, -6, 40);
	glTexCoord2f(6, 0); glVertex3f(13, -6, -20);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	/*Quatz Stack*/
	GLfloat shelfEdge[4] = { 0.85, 0.84, 0.84, 4 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, matBronze[0]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matBronze[1]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matBronze[2]);
	glMaterialf(GL_FRONT, GL_SHININESS, 25.6);
	glColor3f(0.95, 0.94, 0.94);
	DrawCube(9.7, -3, -16, 4.2, NULL, NULL, shelfEdge);	//bottom
	glColor3f(0.85, 0.84, 0.84);
	DrawCube(9.7, 1, -16, 4.2, NULL, NULL, shelfEdge);	//medial
	glColor3f(0.85, 0.84, 0.84);
	DrawCube(9.7, 5, -16, 4.2, NULL, NULL, shelfEdge);	//medial
	glColor3f(0.86, 0.84, 0.84);
	DrawCube(9.7, 9, -16, 4.2, NULL, NULL, shelfEdge);	//top

	/*A Bed*/
	GLfloat sheetData[3] = { 3.22, 0.3, 1.2 };
	GLfloat quiltData[3] = { 2.6, 0.35, 1.2 };
	GLfloat steadData[3] = { 3.22, 0.15, 1.2 };
	glColor3f(0.8, 0.8, 0.8);
	DrawCube(7.75, -4.3, -10, 3.2, sheetData);	//sheet
	glColor3f(0.6, 0.2, 0.2);
	DrawCube(6.7, -4.3, -9.9, 3.2, quiltData);		//quilt
	glColor3f(0.34222, 0.28, 0.224444);
	DrawCube(7.75, -5, -10, 3.2, steadData);	//stead
	glColor3f(0.34222, 0.28, 0.124444);
	DrawCube(3.05, -5.6, -8.47, 0.8);			//leg A
	DrawCube(3.05, -5.6, -11.5, 0.8);			//leg B
	DrawCube(12.48, -5.6, -8.47, 0.8);			//leg C
	DrawCube(12.48, -5.6, -12, 0.8);			//leg D

	/*The Door*/
	GLfloat doorData[3] = { 2, 4, 0.3 };
	GLfloat doorBulge[3] = { 0.8, 2.4, 0.5 };
	GLfloat doorEdge[4] = { 0.341176, 0.235294, 0.164705, 4 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, matWooden[0]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matWooden[1]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWooden[2]);
	glColor3f(0.260784, 0.201960, 0.147058);
	DrawCube(-5.3, -1.4, -19, 2.2, doorData, NULL, doorEdge);
	DrawCube(-6.0, 0.5, -18, 1.5, doorBulge);
	DrawCube(-4.2, 0.5, -18, 1.5, doorBulge);
	DrawCube(-6.0, -3.5, -18, 1.5, doorBulge);
	DrawCube(-4.2, -3.5, -18, 1.5, doorBulge);
	glColor3f(1, 0.8, 0);
	glLineWidth(4);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-4.2, -1.5, -18);
	glVertex3f(-3.4, -1.5, -18);
	glVertex3f(-3.4, -1.0, -18);
	glEnd();

	/*Some Torches*/
	if (aRoomLight)
	{
		GLfloat torchData1[3] = { 0.6, 2.8, 0.6 };
		GLfloat torchData2[3] = { 0.6, 2.8, 0.6 };
		GLfloat lean1[4] = { 30, 1, 0, 0 };
		GLfloat lean2[4] = { -30, 0, 0, 1 };
		GLfloat lean3[4] = { 30, 0, 0, 1 };
		glColor3f(0.386274, 0.311765, 0.182352);
		DrawCube(-0.5, 0.4, -18.5, 0.9, torchData1, lean1);		//back
		DrawCube(-10.3, 0.4, -18.5, 0.9, torchData1, lean1);
		DrawCube(-12.5, 0.4, -8.8, 0.9, torchData2, lean2);		//left
		DrawCube(-12.5, 0.4, 2.6, 0.9, torchData2, lean2);
		DrawCube(12.5, 0.4, -8.8, 0.9, torchData2, lean3);		//right
		DrawCube(12.5, 0.4, 2.6, 0.9, torchData2, lean3);
		glMaterialfv(GL_FRONT, GL_AMBIENT, matGolden[0]);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matGolden[1]);
		glMaterialfv(GL_FRONT, GL_SPECULAR, matGolden[2]);
		glMaterialfv(GL_FRONT, GL_EMISSION, matGolden[2]);
		glMaterialf(GL_FRONT, GL_SHININESS, 3.197);
		glColor3f(1, 0, 0);
		DrawCube(-0.5, 1.3, -18, 0.6, NULL, lean1);
		DrawCube(-10.3, 1.3, -18, 0.6, NULL, lean1);
		DrawCube(-12, 1.3, -8.8, 0.6, NULL, lean2);				//left
		DrawCube(-12, 1.3, 2.6, 0.6, NULL, lean2);
		DrawCube(12, 1.3, -8.8, 0.6, NULL, lean3);				//right
		DrawCube(12, 1.3, 2.6, 0.6, NULL, lean3);
	}


	/*Some Webs*/
	glColor3f(1, 1, 1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matWhite);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matWhite);
	glMaterialfv(GL_FRONT, GL_EMISSION, matWhite);
	DrawWeb(4.4, -4, -18, 1.8);
	DrawWeb(-10.8, 9.4, -18, 1.8, 30.0);

	/*Anvil*/
	glColor3f(0, 0, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matObsidian[0]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matObsidian[1]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matObsidian[2]);
	glMaterialfv(GL_FRONT, GL_EMISSION, matObsidian[2]);
	glMaterialf(GL_FRONT, GL_SHININESS, 1.00002);
	GLfloat base[3] = { 3.5, 0.8, 3.5 };
	GLfloat inner[3] = { 3, 0.9, 3 };
	GLfloat support[3] = { 2.2, 3.5, 2.2 };
	GLfloat platform[3] = { 4, 1.5, 4 };
	DrawCube(-10, -5.6, -18, 1, base);
	DrawCube(-10, -5.4, -18, 1, inner);
	DrawCube(-10, -5.4, -18, 1, support);
	DrawCube(-10, -2.8, -18, 1, platform);

	// TODO:
	// Add animation here

	/*A Treasure Chest*/
	GLfloat chestEdge[4] = { 0.1, 0.1, 0.1, 4 };
	GLfloat lid[3] = { 1, 0.3, 1 };
	GLfloat box[3] = { 1, 0.8, 1 };
	GLfloat lidLean[4] = { 30, 0, 0,1 };
	glColor3f(0.72, 0.475555, 0.155555);
	DrawCube(-11, -4.6, -3, 3, box, NULL, chestEdge);
	glColor3f(0.73, 0.475555, 0.155555);
	if (chestOpen)
	{
		glPushMatrix();
		glTranslatef(-0.3, 0.8, 0);
		DrawCube(-11, -2.9, -3, 3, lid, lidLean, chestEdge);
		glPopMatrix();
	}
	else DrawCube(-11, -2.9, -3, 3, lid, NULL, chestEdge);

	/*Item Frame*/
	GLfloat frameData[3] = { 0.1, 1, 1 };
	GLfloat boardData[3] = { 0.15, 0.8, 0.8 };
	GLfloat zombieData[3] = { 0.4, 0.8, 0.8 };
	glColor3f(0.72, 0.475555, 0.155555);
	DrawCube(12.5, 2, -1.5, 3, frameData, NULL, NULL);
	glColor3f(0.817778, 0.253333, 0.18);
	DrawCube(12.5, 2, -1.5, 3, boardData, NULL, NULL);
	glColor3ub(56, 142, 60);
	DrawCube(12, 2, -1.3, zombie, zombieData, NULL, NULL);


	/*EXP*/
	if (dropEXP && !createCreeper)
	{
		DrawEXP(creepX, -3, creepZ);
		DrawEXP(creepX + 0.5, -3, creepZ - 1);
		DrawEXP(creepX - 1, -3, creepZ + 0.5);
	}

	/*Fantastic Creepers and here to find them*/
	if (createCreeper)
	{
		GLfloat cBodyData[3] = { 0.9, 1.6, 0.4 };
		GLfloat cFeetData[3] = { 0.5, 0.7, 0.5 };
		GLfloat cHeadRota[4] = { cHeadRotate, 0, 1, 0 };
		GLfloat cBodyRota[4] = { cBodyRotate, 0, 1, 0 };
		GLfloat cLeftFeetRota[4] = { -1 * cFeetRotate, 1, 0, 0 };//left & right, repeatedlly
		GLfloat cRightFeetRota[4] = { cFeetRotate, 1, 0, 0 };
		if (toKillACreeper)
			glColor3f(0.55, 0.15, 0.15);
		else
			glColor3f(0.198039, 0.68627451, 0.213725);
		DrawCube(0 + creepX, 1.3 + creepY, -5 + creepZ, 2.5, NULL, NULL, NULL);
		DrawCube(0 + creepX, -1.7 + creepY, -5 + creepZ, 2.5, cBodyData, cBodyRota, NULL);
		DrawCube(-1.1 + creepX, -4.5 + creepY, -5.8 + creepZ, 2.5, cFeetData, cLeftFeetRota, NULL);
		DrawCube(1.1 + creepX, -4.5 + creepY, -5.8 + creepZ, 2.5, cFeetData, cRightFeetRota, NULL);
		DrawCube(-1.1 + creepX, -4.5 + creepY, -4.5 + creepZ, 2.5, cFeetData, cLeftFeetRota, NULL);
		DrawCube(1.1 + creepX, -4.5 + creepY, -4.5 + creepZ, 2.5, cFeetData, cRightFeetRota, NULL);
		glDisable(GL_LINE_STIPPLE);

		glEnable(GL_TEXTURE_2D);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textCreep);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		if (toKillACreeper)
			glColor3f(1, 0.4, 0.6);
		else
			glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-1.25 + creepX, 0.05 + creepY, -3.6 + creepZ);
		glTexCoord2f(0, 1); glVertex3f(-1.25 + creepX, 2.55 + creepY, -3.6 + creepZ);
		glTexCoord2f(1, 1); glVertex3f(1.25 + creepX, 2.55 + creepY, -3.6 + creepZ);
		glTexCoord2f(1, 0); glVertex3f(1.25 + creepX, 0.05 + creepY, -3.6 + creepZ);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

	glutSwapBuffers();
	glFlush();
	glutPostRedisplay();
}

void reshape(int w, int h) // Resize the GL Window. w=width, h=height
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(65, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	gluLookAt(0.0, 0.6, 15.6, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y) // Handle the keyboard events here
{
	switch (key)
	{
	case '\033':
		exit(0);
	case '1':
		if (aRoomLight == false)
			aRoomLight = true;
		break;
	case '2':
		if (aRoomLight)
			aRoomLight = false;
		break;
	case '3':
		if (!createCreeper)
			createCreeper = true;
		break;
	case '4':
		toKillACreeper = true;
		break;
	case '5':
		zombieScale = true;
		break;
	default: break;
	}

}

void mouse(GLint button, GLint state, GLint x, GLint y)
{
	GLuint pickBuffer[32];
	GLint nPicks, vp[4];
	if (x >= 180 && x <= 285 && y >= 285 && y <= 370)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			chestOpen = true;
		}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			chestOpen = false;
		}
	}
}

void idle(void)
{
	int r = -1;
	srand((unsigned int)time(0));
	if (createCreeper)
		r = rand() % 6;
	switch (r)
	{
	case -1: break;
	case 0:
		if (toKillACreeper) //Flipping in the air
			break;
		creepX += 0.4;
		cBodyRotate += 10;
		break;
	case 1:
		creepZ += 0.4;
		break;
	case 2:
		creepX -= 0.4;
		cBodyRotate -= 10;
		break;
	case 3:
		creepZ -= 0.4;
		break;
	default:
		cFeetRotate = 0;
		break;
	}
	if (cFeetRotate <= -45)
		cFeetRotate = 45;
	else cFeetRotate -= 45;
	if (creepX > 8)
		creepX -= 0.6;
	if (creepX < -8)
		creepX += 0.6;
	if (creepZ > 18)
		creepZ -= 0.6;
	if (creepZ < 0)
		creepZ += 0.6;

	if (toKillACreeper && counter == 0)
	{
		creepY = 5;
		counter++;
	}
	else if (counter >= 8)
	{
		createCreeper = false;
		toKillACreeper = false;
		dropEXP = true;
		creepY = 0;
		counter = 0;
	}
	else
	{
		if (toKillACreeper)
		{
			creepY -= 0.5;
			counter++;
		}
	}
	if (zombieScale)
	{
		zombie += 0.05;
		if (zombie > 2.0)
			zombieScale = false;
	}
	shinningEXP++; //change the color

	Sleep(200);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{

	/*Initialization of GLUT Library */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	/*Create a window with title specified */
	glutInitWindowSize(900, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Assignment 1");

	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}
