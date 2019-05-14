#define _USE_MATH_DEFINES	

#include "stdafx.h"

#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include <gl\freeglut.h>


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

void DrawFaceCube(CVector3d* vertexW)
{

	int face[6][4] = {
		{ 0, 3, 2, 1 },		//Z
		{ 1, 2, 6, 5 },		//X
		{ 2, 3, 6, 7 },		//Y
		{ 3, 0, 4, 7 },		//X
		{ 0, 1, 5, 4 },		//Y
		{ 4, 5, 6, 7 }			//
	};

	GLdouble normal[6][3] = {
		{ 0.0, 0.0, -1.0 },		//Z
		{ 1.0, 0.0, 0.0 },	        //X
		{ 0.0, 1.0, 0.0 },		//Y
		{ -1.0, 0.0, 0.0 },		//X
		{ 0.0, -1.0, 0.0 },		//Y
		{ 0.0, 0.0, 1.0 }		//Z
	};

	glBegin(GL_QUADS);
	for (int i(0); i < 6; ++i)
	{
		glNormal3dv(normal[i]);
		for (int k(0); k < 4; ++k)
			glVertex3d(vertexW[face[i][k]].x, vertexW[face[i][k]].y, vertexW[face[i][k]].z);
	}
	glEnd();

}

void DrawFaceOctree(OctVoxel &box, int colorID)
{
	int line[6][4] =
	{ { 0, 1, 2, 3 },
	{ 4, 5, 6, 7 },
	{ 0, 4, 7, 3 },
	{ 1, 5, 4, 0 },
	{ 2, 6, 5, 1 },
	{ 3, 7, 6, 2 } };

	glColor3dv(GetColor(colorID)); // err
	//glColor3d(1.0, 0.0, 0.5);
	CVector3d vertexW[8];
	box.SetVertexWorld(vertexW);
	//box.SetVertexWorld_Rotated(Angle_.Orientation_Angle, vertexW);
	glBegin(GL_QUADS);
	for (int i(0); i < 6; ++i)
	{
		for (int k(0); k < 4; ++k)
		{
			glVertex3d(vertexW[line[i][k]].x, vertexW[line[i][k]].y, vertexW[line[i][k]].z);
		}
	}
	glEnd();
}
/*=================================================*/
/*              Draw Bounding Box                  */
/*=================================================*/

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

/*=================================================*/
/*              Draw Grid		                   */
/*=================================================*/

void DrawGrid() {
	glColor3d(0.0, 0.0, 0.0);
	glLineWidth(0.8f);
	glBegin(GL_LINES);
	for (int x(0); x <= 20; x++) {
		glVertex2i(x, 0);
		glVertex2i(x, 15);
	}
	for (int y(0); y <= 15; y++) {
		glVertex2i(0, y);
		glVertex2i(20, y);
	}
	glEnd();
}

void DrawCube(CVector3d originPoint, int colorID) {
	CVector3d MinPt, MaxPt;

	MinPt.Set(originPoint.x, originPoint.y, 0.0);
	MaxPt.Set(originPoint.x + 1.0, originPoint.y + 1.0, 1.0);

	DrawBoundingbox(MaxPt, MinPt, colorID);
}

void PathPlanning() {

	CVector3d MinPt, MaxPt;
	for (int x(0); x <= 20; x++) {
		for (int y(0); y <= 15; y++) {
			MinPt.Set(x*1.0, y*1.0, 0.0);
			MaxPt.Set(x*1.0 + 1.0, y*1.0 + 1.0, 1.0);

			DrawCube(MinPt, y * 5);
		}

	}
}

void DrawStartEndPoint() {
	CVector3d MaxPt, MinPt;

	MaxPt.Set(1.0, 1.0, 1.0);
	MinPt.Set(0.0, 0.0, 0.0);
	//DrawBoundingbox(MaxPt, MinPt, 8);
	DrawCube(MinPt, 17);

	CVector3d center;
	center.Set(0.5, 0.5, 0.5);
	DrawSphere(center, 0.1);


	MaxPt.Set(19.0, 14.0, 1.0);
	MinPt.Set(20.0, 15.0, 0.0);
	//DrawBoundingbox(MaxPt, MinPt, 8);
	DrawCube(MaxPt, 35);

	center.Set(19.5, 14.5, 0.5);
	DrawSphere(center, 0.1);

	glBegin(GL_LINE_LOOP);
	glColor3d(0.1, 0.0, 1.0);
	glVertex3d(0.5, 0.5, 0.5);//1
	glVertex3d(19.5, 14.5, 0.5);//2
	glEnd();
}

//14/5/19 Not yet
void PathPlanning2() {

	CVector3d vertex[8];
	DrawFaceCube(vertex);

}

double distancePointLine(CVector3d sPoint, CVector3d ePoint,
	CVector3d newPoint, double& distance) {

	double numerator, denominator;

	numerator = ((sPoint.y - ePoint.y)*newPoint.x
		+ (ePoint.x - sPoint.x)*newPoint.y
		+ (sPoint.x * ePoint.y - ePoint.x * sPoint.y));

	denominator = sqrt((ePoint.x - sPoint.x)*(ePoint.x - sPoint.x)
		+ (ePoint.y - sPoint.y)*(ePoint.y - sPoint.y));
	distance = numerator / denominator;

	if (distance < 0) {
		distance = -distance;
	}
	else if (distance == 0) {
		cout << "error in distance" << endl;
	}

	return distance;
	cout << "distance: " <<distance << endl;	


}

void checkPoint() {
	//moving point
	vector<CVector3d> m_Point;

	//CVector3d movePoint;

	CVector3d s_point, e_point;
	s_point.Set(0.5, 0.5, 0.5);
	DrawSphere(s_point, 0.1);

	//movePoint = s_point;

	e_point.Set(19.5, 14.5, 0.5);
	DrawSphere(e_point, 0.1);


	//	while ((movePoint.x != E_point.x) || (movePoint.y != E_point.y)
	//		|| (movePoint.z != E_point.z)){
	//		cout << " i love u" << endl;
	//	}


	//create a line from starting point to ending point
	double dist = 0.0;
	double dist1 = 0.0;
	double dist2 = 0.0;

	CVector3d nextPoint;
	nextPoint.Set(s_point.x + 1.0, s_point.y, s_point.z);
	double a = distancePointLine(s_point, e_point, nextPoint, dist1);

	cout << nextPoint.x <<" "<< nextPoint.y << " " << nextPoint.z << endl;

	nextPoint.Set(s_point.x, s_point.y + 1.0, s_point.z);
	double b = distancePointLine(s_point, e_point, nextPoint, dist2);
	cout << nextPoint.x << " " << nextPoint.y << " " << nextPoint.z << endl;

	cout << "double a= " <<a << " ---- double b= " << b << endl;
	if (a < b) {
		dist = a;
	}
	else
		dist = b;
	cout << "distance = " << dist << endl;


	
	//m_Point.push_back();
	



}


