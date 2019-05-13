#pragma once


//############################################################################
//############################################################################

#ifndef _OPENGLLIGHT_H
#define _OPENGLLIGHT_H

#include "stdafx.h"
//#include "OpenGL.h"
using namespace std;

//EnableLight
inline void SetLight() {
	//
	GLfloat light0_ambient[4] = { 1.0f, 0.2f, 0.2f, 0.5f };
	GLfloat light0_diffuse[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light0_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light0_position[4] = { -35.0f, 35.0f, 50.0f, 0.0f };


	//
	GLfloat light1_ambient[4] = { 0.2f, 1.0f, 0.2f, 1.0f };
	GLfloat light1_diffuse[4];	GLfloat light1_specular[4];	GLfloat light1_position[4];
	memmove(light1_diffuse, light1_ambient, sizeof(light1_ambient));
	memmove(light1_specular, light0_specular, sizeof(light0_specular));
	memmove(light1_position, light0_position, sizeof(light0_specular));

	//
	GLfloat light2_ambient[4] = { 0.2f, 0.2f, 1.0f, 1.0f };
	GLfloat light2_diffuse[4];	GLfloat light2_specular[4];	GLfloat light2_position[4];
	memmove(light2_diffuse, light2_ambient, sizeof(light2_ambient));
	memmove(light2_specular, light0_specular, sizeof(light0_specular));
	memmove(light2_position, light0_position, sizeof(light0_specular));

	//
	GLfloat light3_ambient[4] = { 0.0f, 0.0f, 0.7f, 1.0f };
	GLfloat light3_diffuse[4];	GLfloat light3_specular[4];	GLfloat light3_position[4];
	memmove(light3_diffuse, light3_ambient, sizeof(light3_ambient));
	memmove(light3_specular, light0_specular, sizeof(light0_specular));
	memmove(light3_position, light0_position, sizeof(light0_specular));

	//
	GLfloat light4_ambient[4] = { 1.0f, 0.6f, 0.2f, 1.0f };
	GLfloat light4_diffuse[4];	GLfloat light4_specular[4];	GLfloat light4_position[4];
	memmove(light4_diffuse, light4_ambient, sizeof(light4_ambient));
	memmove(light4_specular, light0_specular, sizeof(light0_specular));
	memmove(light4_position, light0_position, sizeof(light0_specular));

	//
	GLfloat light5_ambient[4] = { 0.8f, 0.8f, 1.0f, 1.0f };
	GLfloat light5_diffuse[4];	GLfloat light5_specular[4];	GLfloat light5_position[4];
	memmove(light5_diffuse, light5_ambient, sizeof(light5_ambient));
	memmove(light5_specular, light0_specular, sizeof(light0_specular));
	memmove(light5_position, light0_position, sizeof(light0_specular));

	//
	GLfloat light6_ambient[4] = { 2.0f, 1.0f, 0.0f, 1.0f };
	GLfloat light6_diffuse[4];	GLfloat light6_specular[4];	GLfloat light6_position[4];
	memmove(light6_diffuse, light6_ambient, sizeof(light6_ambient));
	memmove(light6_specular, light0_specular, sizeof(light0_specular));
	memmove(light6_position, light0_position, sizeof(light0_specular));

	//
	GLfloat light7_ambient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat light7_diffuse[4];	GLfloat light7_specular[4];	GLfloat light7_position[4];
	memmove(light7_diffuse, light7_ambient, sizeof(light7_ambient));
	memmove(light7_specular, light0_specular, sizeof(light0_specular));
	memmove(light7_position, light0_position, sizeof(light0_specular));


	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
	glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
	glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
	glLightfv(GL_LIGHT3, GL_AMBIENT, light3_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light3_specular);
	glLightfv(GL_LIGHT4, GL_POSITION, light4_position);
	glLightfv(GL_LIGHT4, GL_AMBIENT, light4_ambient);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, light4_diffuse);
	glLightfv(GL_LIGHT4, GL_SPECULAR, light4_specular);
	glLightfv(GL_LIGHT5, GL_POSITION, light5_position);
	glLightfv(GL_LIGHT5, GL_AMBIENT, light5_ambient);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, light5_diffuse);
	glLightfv(GL_LIGHT5, GL_SPECULAR, light5_specular);
	glLightfv(GL_LIGHT6, GL_POSITION, light6_position);
	glLightfv(GL_LIGHT6, GL_AMBIENT, light6_ambient);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, light6_diffuse);
	glLightfv(GL_LIGHT6, GL_SPECULAR, light6_specular);
	glLightfv(GL_LIGHT7, GL_POSITION, light7_position);
	glLightfv(GL_LIGHT7, GL_AMBIENT, light7_ambient);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, light7_diffuse);
	glLightfv(GL_LIGHT7, GL_SPECULAR, light7_specular);

}

//
inline void EnableLight(int value) {
	//
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	switch (value)
	{
	case 0:
		glEnable(GL_LIGHT0);
		break;
	case 1:
		glEnable(GL_LIGHT1);
		break;
	case 2:
		glEnable(GL_LIGHT2);
		break;
	case 3:
		glEnable(GL_LIGHT3);
		break;
	case 4:
		glEnable(GL_LIGHT4);
		break;
	case 5:
		glEnable(GL_LIGHT5);
		break;
	case 6:
		glEnable(GL_LIGHT6);
		break;
	case 7:
		glEnable(GL_LIGHT7);
		break;
	}
}

//
inline void DisableLight(void) {
	//
	glDisable(GL_LIGHT0);	glDisable(GL_LIGHT1);	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);	glDisable(GL_LIGHT4);	glDisable(GL_LIGHT5);
	glDisable(GL_LIGHT6);	glDisable(GL_LIGHT7);

	//
	glDisable(GL_LIGHTING);
	glDisable(GL_NORMALIZE);
}


//
inline void DrawString(const char *string, CVector3d V, void *font, GLint alignment) {
	glRasterPos3d(V.x, V.y, V.z);
	for (; *string; *string++)
	{
		gl2psTextOpt(string, "Times-Roman", 32, alignment, 0.0f);	//GL2PS-EPS
		glutBitmapCharacter(font, *string);	//OpenGL
	}
}


//
//
inline void DrawCylinder(GLdouble d, GLdouble s) {
	int m = 1, n = 12;
	double u0, u1, v0;

	for (int i = 0; i < m; ++i)
	{
		u0 = (double)i*s / (double)m;
		u1 = (double)(i + 1)*s / (double)m;
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= n; ++j)
		{
			v0 = (double)j*2.0*M_PI / (double)n;
			glNormal3d(cos(v0), sin(v0), 0.0);
			glVertex3d(d*cos(v0), d*sin(v0), u0);
			glVertex3d(d*cos(v0), d*sin(v0), u1);
		}
		glEnd();
	}

}

//
inline void DrawCircle(GLdouble d, int n) {
	int i;
	double t;
	glBegin(GL_TRIANGLE_STRIP);
	for (i = 0; i <= n; ++i)
	{
		t = (double)i*2.0*M_PI / (double)n;
		glNormal3d(0.0, 0.0, 1.0);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(d*cos(t), d*sin(t), 0.0);
	}
	glEnd();
}

//
inline void DrawSphere(CVector3d A, double radius) {
	int n = 12;
	glPushMatrix();
	glTranslated(A.x, A.y, A.z);
	glutSolidSphere(radius, n, n);
	glPopMatrix();
}

//
//
inline void DrawPipe(CVector3d A, CVector3d B, double radius) {
	CVector3d C = B - A;
	double h = C.Norm();
	double r;
	if (h > 0.0)
	{
		r = acos(C.z / h);
		glPushMatrix();
		glTranslated(A.x, A.y, A.z);
		glRotated(r * 180.0 / M_PI, -C.y, C.x, 0.0);
		DrawCylinder(radius, h);
		glPopMatrix();
	}
}


//
inline void DrawCone(double r, double h, int n) {
	double t0;

	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= n; ++i)
	{
		t0 = (double)i*2.0*M_PI / (double)n;
		glNormal3d(cos(t0), sin(t0), r / h);
		glVertex3d(0.0, 0.0, h);
		glNormal3d(cos(t0), sin(t0), r / h);
		glVertex3d(r*cos(t0), r*sin(t0), 0.0);
	}
	glEnd();

	glPushMatrix();
	glRotated(180, 1.0, 0.0, 0.0);
	DrawCircle(r, n);
	glPopMatrix();
}


//
inline void DrawArrowOpt(CVector3d V, CVector3d T, double h, double radius, double cr, double ch, int n) {
	T.Normalize();
	double coner = cr * radius;
	double coneh = ch * coner;

	//
	if (0.5*h < coneh)
	{
		coneh = 0.5*h;
		coner = coneh / ch;
		radius = coner / cr;
	}
	if (h != 0.0)
	{
		double angle = acos(T.z) * 180.0 / M_PI;
		glPushMatrix();
		glTranslated(V.x, V.y, V.z);
		glRotated(angle, -T.y, T.x, 0.0);
		DrawCylinder(radius, h - coneh);

		glTranslated(0.0, 0.0, h - coneh);
		DrawCone(coner, coneh, n);
		glPopMatrix();
	}

}

//
inline void DrawArrow(CVector3d V, CVector3d T, double h, double radius) {
	DrawArrowOpt(V, T, h, radius, 2.5, 1.618*2.0, 12);
	//1.618
}


#endif
