#define _USE_MATH_DEFINES	

#include "stdafx.h"

#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include <gl\freeglut.h>

#include "OpenGL.h"
#include "OpenGLprimitive.h"

using namespace std;
extern OctVoxel cube;
extern OpenGL GLSettings0;


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

void DrawStartEndPoint(CVector3d startPoint, CVector3d endPoint) {
	glBegin(GL_LINE_LOOP);
	glColor3d(0.1, 0.0, 1.0);
	glVertex3d(startPoint.x, startPoint.y, startPoint.z);//1
	glVertex3d(endPoint.x, endPoint.y, endPoint.z);//2
	glEnd();
}

void DrawCube_originPoint(CVector3d originPoint, int colorID) {
	CVector3d MinPt, MaxPt;

	MinPt.Set(originPoint.x, originPoint.y, originPoint.z);
	MaxPt.Set(originPoint.x + 1.0, originPoint.y + 1.0, originPoint.z+1.0);
		
	DrawBoundingbox(MaxPt, MinPt, colorID);
}

void DrawCube(CVector3d centerPoint, int colorID) {
	CVector3d MinPt, MaxPt;

	MinPt.Set(centerPoint.x - 0.5, centerPoint.y - 0.5, centerPoint.z - 0.5);
	MaxPt.Set(centerPoint.x + 0.5, centerPoint.y + 0.5, centerPoint.z +  0.5);
	
	DrawBoundingbox(MaxPt, MinPt, colorID);
}


void PathPlanning() {

	CVector3d MinPt, MaxPt;
	for (int x(0); x <= 20; x++) {
		for (int y(0); y <= 15; y++) {
			MinPt.Set(x*1.0, y*1.0, 0.0);
			MaxPt.Set(x*1.0 + 1.0, y*1.0 + 1.0, 1.0);

			DrawCube_originPoint(MinPt, y * 5);
		}

	}
}
//14/5/19 Not yet
void PathPlanning2() {

	CVector3d vertex[8];
	DrawFaceCube(vertex);

}

//-------------------------------------------------------------
//create a line from starting point to ending point
//then calculate the distance
double distancePointLine(CVector3d sPoint, CVector3d ePoint, CVector3d newPoint, double& distance)
{
	double numerator, denominator;

	numerator = ((sPoint.y - ePoint.y)*newPoint.x
		+ (ePoint.x - sPoint.x)*newPoint.y
		+ ((sPoint.x * ePoint.y) - (ePoint.x * sPoint.y)));

	denominator = sqrt((ePoint.x - sPoint.x)*(ePoint.x - sPoint.x)
		+ (ePoint.y - sPoint.y)*(ePoint.y - sPoint.y));
	distance = numerator / denominator;

	if (distance < 0) {
		distance = -distance;
		return distance;
	}
	else if (distance >= 0) {
		//exit(1);
		//cout << "error in distance: " << distance << endl;
		return distance;
	}
	//return distance;
	//cout << "distance!!!!!!!!!: " << distance << endl;
}

void checkPoint(int colorID) {
	GLfloat white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat yellow[4] = { 0.8f, 0.8f, 0.0f, 1.0f };
	GLfloat shininess = 50;
	GLfloat light0_position[4] = { (float)GLSettings0.m_Eye.x, (float)GLSettings0.m_Eye.y, (float)GLSettings0.m_Eye.z, 1.0f };

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);

	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	CColor temp(GetColor(colorID));
	GLfloat color[4] = { (float)temp.r, (float)temp.g, (float)temp.b, 0.5f };
	GLfloat color_[4] = { 1.0f, 0.2f, 0.2f, 0.5f };

	/*cube.cubeCenter.push_back(cube.startPoint);

	double dist1 = 0.0;
	double dist2 = 0.0;

	CVector3d nextPoint1, nextPoint2;
	CVector3d newMovePoint;

	CVector3d tempPoint;
	tempPoint.Set(cube.startPoint.x, cube.startPoint.y, cube.startPoint.z);

	while (tempPoint != cube.goalPoint)
	{
		nextPoint1.Set(tempPoint.x + 1.0, tempPoint.y, tempPoint.z);
		double distance1 = nextPoint1.PointLineDistance(cube.startPoint, cube.goalPoint);
		nextPoint2.Set(tempPoint.x, tempPoint.y + 1.0, tempPoint.z);
		double distance2 = nextPoint2.PointLineDistance(cube.startPoint, cube.goalPoint);

		if (distance1 > distance2) {
			newMovePoint = nextPoint2;
		}else {
			newMovePoint = nextPoint1;
		}

		glMaterialfv(GL_FRONT, GL_SPECULAR, color);
		DrawSphere(newMovePoint, 0.1);

		tempPoint = newMovePoint;

		cube.cubeCenter.push_back(newMovePoint);
	}

	cube.cubeCenter.push_back(cube.goalPoint);*/

	for (int i(0); i < cube.cubeCenter.size(); i++) {
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
		WireCuboid(cube.cubeCenter[i], 1.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
		SolidCuboid(cube.cubeCenter[i], 1.0);

		//DrawSphere(cube.cubeCenter[i], 0.1);
	}


	glDisable(GL_LIGHTING);
}

