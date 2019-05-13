#define _USE_MATH_DEFINES	

#include "stdafx.h"

#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include <gl\freeglut.h>

#include "..\Dependencies\freeglut\include\GL\freeglut_ext.h"
#include "..\Dependencies\freeglut\include\GL\freeglut_std.h"


using namespace std;



//[AntTweakBar]//
void GradientBackGround(float *tcolor, float *bcolor) {
	// 
	DisableLight();
	glMatrixMode(GL_MODELVIEW);  // ModelView?s
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION); // Projection?s
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);    // DepthTest
	glBegin(GL_QUADS);
	glColor3fv(bcolor);
	glVertex3d(-1, -1, 0);
	glVertex3d(1, -1, 0);
	glColor3fv(tcolor);
	glVertex3d(1, 1, 0);
	glVertex3d(-1, 1, 0);
	glEnd();
	glEnable(GL_DEPTH_TEST);     // DepthTest
	glMatrixMode(GL_PROJECTION); // Projection?s
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);  // ModelView?s
	glPopMatrix();
}
//#################################################
//	From OpenGLprimitive.h
//#################################################
void ConclusiveAxis(void) {
	glLineWidth(1.0);
	double radius = 0.01;
	double stringspace = 0.05;

	CVector3d O(0.0, 0.0, 0.0);	CVector3d X(1.0, 0.0, 0.0);
	CVector3d Y(0.0, 1.0, 0.0);	CVector3d Z(0.0, 0.0, 1.0);

	CVector3d Os(stringspace, stringspace, stringspace);
	CVector3d Xs(-2.0*stringspace, stringspace, stringspace);
	CVector3d Ys(-2.0*stringspace, -2.0*stringspace, stringspace);
	CVector3d Zs(-2.0*stringspace, -2.0*stringspace, stringspace);
	glColor3d(0.0, 0.0, 0.0);
	DrawString("O", (O + Os), GLUT_BITMAP_TIMES_ROMAN_24, GL2PS_TEXT_BL);

	//x
	EnableLight(7);
	DrawArrow(-1.0*X, X, 2.0, radius);
	DisableLight();
	glColor3d(0.0, 0.0, 0.0);
	DrawString("X", (X + Xs), GLUT_BITMAP_TIMES_ROMAN_24, GL2PS_TEXT_BL);


	//y
	EnableLight(7);
	DrawArrow((-1.0*Y), Y, 2.0, radius);
	DisableLight();
	glColor3d(0.0, 0.0, 0.0);
	DrawString("Y", (Y + Ys), GLUT_BITMAP_TIMES_ROMAN_24, GL2PS_TEXT_BL);


	//z
	EnableLight(7);
	DrawArrow((-1.0*Z), Z, 2.0, radius);
	DisableLight();
	glColor3d(0.0, 0.0, 0.0);
	DrawString("Z", (Z + Zs), GLUT_BITMAP_TIMES_ROMAN_24, GL2PS_TEXT_BR);
}

//############################################
//         draw bounding box
void DrawWireOctree(OctVoxel box, int colorID) {
	int line[12][2] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },
						{ 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 },
						{ 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 } };

	glLineWidth(3);
	glColor3dv(GetColor(colorID));
	CVector3d vertexW[8];
	box.SetVertexWorld(vertexW);

	for (int i = 0; i < 12; i++) {
		glBegin(GL_LINES);
		glVertex3d(vertexW[line[i][0]].x, vertexW[line[i][0]].y, vertexW[line[i][0]].z);
		glVertex3d(vertexW[line[i][1]].x, vertexW[line[i][1]].y, vertexW[line[i][1]].z);
		glEnd();

	}

}

/*                                                 */
/*              Draw Bounding Box                  */
/*                                                 */

void DrawBoundingbox(CVector3d MaxPt, CVector3d MinPt, int colorID) {

	glLineWidth(3.0);
	//glColor3f(0.3f, 0.3f, 0.3f);

	glColor3dv(GetColor(colorID));

	glBegin(GL_LINE_LOOP);
	glVertex3d(MinPt.x, MaxPt.y, MaxPt.z);//1
	glVertex3d(MaxPt.x, MaxPt.y, MaxPt.z);//2
	glVertex3d(MaxPt.x, MaxPt.y, MinPt.z);//3
	glVertex3d(MinPt.x, MaxPt.y, MinPt.z);//4
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3d(MinPt.x, MinPt.y, MinPt.z);//8
	glVertex3d(MaxPt.x, MinPt.y, MinPt.z);//7
	glVertex3d(MaxPt.x, MinPt.y, MaxPt.z);//6
	glVertex3d(MinPt.x, MinPt.y, MaxPt.z);//5
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3d(MinPt.x, MaxPt.y, MaxPt.z);//1
	glVertex3d(MinPt.x, MaxPt.y, MinPt.z);//4
	glVertex3d(MinPt.x, MinPt.y, MinPt.z);//8
	glVertex3d(MinPt.x, MinPt.y, MaxPt.z);//5
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3d(MinPt.x, MaxPt.y, MaxPt.z);//1
	glVertex3d(MinPt.x, MinPt.y, MaxPt.z);//5
	glVertex3d(MaxPt.x, MinPt.y, MaxPt.z);//6
	glVertex3d(MaxPt.x, MaxPt.y, MaxPt.z);//2
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3d(MaxPt.x, MaxPt.y, MinPt.z);//3
	glVertex3d(MaxPt.x, MaxPt.y, MaxPt.z);//2
	glVertex3d(MaxPt.x, MinPt.y, MaxPt.z);//6
	glVertex3d(MaxPt.x, MinPt.y, MinPt.z);//7
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3d(MinPt.x, MaxPt.y, MinPt.z);//4
	glVertex3d(MaxPt.x, MaxPt.y, MinPt.z);//3
	glVertex3d(MaxPt.x, MinPt.y, MinPt.z);//7
	glVertex3d(MinPt.x, MinPt.y, MinPt.z);//8
	glEnd();
}



