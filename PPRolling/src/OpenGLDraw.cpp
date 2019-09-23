#include "stdafx.h"


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
/*            Cube	                   */
/*=================================================*/

void DrawGrid() {
	glColor3d(0.0, 0.0, 0.0);
	glLineWidth(0.9f);
	glBegin(GL_LINES);
	for (int x(-1); x <= 7; x++) {
		glVertex2i(x, -1);
		glVertex2i(x, 5);
	}
	for (int y(-1); y <= 5; y++) {
		glVertex2i(-1, y);
		glVertex2i(7, y);
	}
	glEnd();
}

void DrawCubeGrid() {
	// Draw a white grid "floor" for the tetrahedron to sit on.
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	for (GLfloat i = -2.5; i <= 2.5; i += 0.25) {
		glVertex3f(i, 2.5, 0); glVertex3f(i, -2.5, 0);
		glVertex3f(2.5, i, 0); glVertex3f(-2.5, i, 0);
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
	MaxPt.Set(originPoint.x + 1.0, originPoint.y + 1.0, originPoint.z + 1.0);

	DrawBoundingbox(MaxPt, MinPt, colorID);
}

void DrawCube(CVector3d centerPoint, int colorID) {
	CVector3d MinPt, MaxPt;

	MinPt.Set(centerPoint.x - 0.5, centerPoint.y - 0.5, centerPoint.z - 0.49);
	MaxPt.Set(centerPoint.x + 0.5, centerPoint.y + 0.5, centerPoint.z + 0.5);

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
		//std::cout << "error in distance: " << distance << std::endl;
		return distance;
	}
	//return distance;
	//std::cout << "distance!!!!!!!!!: " << distance << std::endl;
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

//18-9-2019

//link: https://stackoverflow.com/questions/19332668/drawing-the-axis-with-its-arrow-using-opengl-in-visual-studio-2010-and-c

#define RADPERDEG 0.0174533
//draw tw0 points
void Arrow(GLdouble x1, GLdouble y1, GLdouble z1, GLdouble x2, GLdouble y2, GLdouble z2, GLdouble D)
{
	double x = x2 - x1;
	double y = y2 - y1;
	double z = z2 - z1;
	double L = sqrt(x*x + y * y + z * z);

	GLUquadricObj *quadObj;

	glPushMatrix();

	glTranslated(x1, y1, z1);

	if ((x != 0.) || (y != 0.)) {
		glRotated(atan2(y, x) / RADPERDEG, 0., 0., 1.);
		glRotated(atan2(sqrt(x*x + y * y), z) / RADPERDEG, 0., 1., 0.);
	}
	else if (z < 0) {
		glRotated(180, 1., 0., 0.);
	}

	glTranslatef(0, 0, L - 4 * D);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluCylinder(quadObj, 2 * D, 0.0, 4 * D, 32, 1);
	gluDeleteQuadric(quadObj);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluDisk(quadObj, 0.0, 2 * D, 32, 1);
	gluDeleteQuadric(quadObj);

	glTranslatef(0, 0, -L + 4 * D);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluCylinder(quadObj, D, D, L - 4 * D, 32, 1);
	gluDeleteQuadric(quadObj);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluDisk(quadObj, 0.0, D, 32, 1);
	gluDeleteQuadric(quadObj);

	glPopMatrix();

}

void drawAxes(GLdouble length)
{
	glPushMatrix();
	glTranslatef(-length, 0, 0);
	Arrow(0, 0, 0, 2 * length, 0, 0, 0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -length, 0);
	Arrow(0, 0, 0, 0, 2 * length, 0, 0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -length);
	Arrow(0, 0, 0, 0, 0, 2 * length, 0.2);
	glPopMatrix();
}

//20/9/2019
void DrawSeparatedArrows(GLdouble currentCenterX, GLdouble currentCenterY, GLdouble currentCenterZ) {

	glColor3f(1.0, 0.0, 0.0);Arrow(currentCenterX, currentCenterY, currentCenterZ, currentCenterX + 0.5, currentCenterY, currentCenterZ, 0.02);
	glColor3f(0.0, 0.5, 0.5);Arrow(currentCenterX, currentCenterY, currentCenterZ, currentCenterX, currentCenterY + .5, currentCenterZ, 0.02);
	glColor3f(0.5, 0.0, 1.0);Arrow(currentCenterX, currentCenterY, currentCenterZ, currentCenterX, currentCenterY, currentCenterZ + 0.5, 0.02);

}

void RotationCoordSystem(
	CVector3d origin, CVector3d OXpoint, CVector3d OYpoint, CVector3d OZpoint,
	bool rightRolling,
	CVector3d &neworigin, CVector3d &newOXpoint, CVector3d &newOYpoint, CVector3d &newOZpoint);
//from cubePath.cpp

void DrawSeparatedArrows2(bool rightRolling, CVector3d currentOrigin,
	CVector3d initial_OXarrow, CVector3d initial_OYarrow, CVector3d initial_OZarrow,
	CVector3d &neworigin, CVector3d &newOXpoint, CVector3d &newOYpoint, CVector3d &newOZpoint)
{

	//Call Rodrigues Function to get the roated arrow coordinates
	RotationCoordSystem(currentOrigin, initial_OXarrow, initial_OYarrow, initial_OZarrow,
		rightRolling, neworigin, newOXpoint, newOYpoint, newOZpoint);

	GLdouble xnew = neworigin.x;
	GLdouble ynew = neworigin.y;
	GLdouble znew = neworigin.z;

	GLdouble x1_new = newOXpoint.x;
	GLdouble y1_new = newOXpoint.y;
	GLdouble z1_new = newOXpoint.z;

	GLdouble x2_new = newOYpoint.x;
	GLdouble y2_new = newOYpoint.y;
	GLdouble z2_new = newOYpoint.z;

	GLdouble x3_new = newOZpoint.x;
	GLdouble y3_new = newOZpoint.y;
	GLdouble z3_new = newOZpoint.z;

	glColor3f(1.0, 0.0, 0.0);Arrow(xnew, ynew, znew, x1_new, y1_new, z1_new, 0.02);
	glColor3f(0.0, 0.5, 0.5);Arrow(xnew, ynew, znew, x2_new, y2_new, z2_new, 0.02);
	glColor3f(0.5, 0.0, 1.0);Arrow(xnew, ynew, znew, x3_new, y3_new, z3_new, 0.02);

	std::cout << "oldOrigin_X " << currentOrigin.x << " oldOrigin_Y " << currentOrigin.y << " oldOrigin__Z " << currentOrigin.z << std::endl;
	std::cout << "newOrigin_X " << xnew << " newOrigin_Y " << ynew << " newOrigin_Z " << znew << std::endl;

	std::cout << "X-new(" << x1_new << "," << y1_new << "," << z1_new << ")" << std::endl;
	std::cout << "Y-new(" << x2_new << "," << y2_new << "," << z2_new << ")" << std::endl;
	std::cout << "Z-new(" << x3_new << "," << y3_new << "," << z3_new << ")" << std::endl;



	//getchar();
}

//=============================



//19/9/2019
void DrawOXarrow(CVector3d currentCoord, GLdouble D) {
	GLdouble x1 = currentCoord.x;
	GLdouble y1 = currentCoord.y;
	GLdouble z1 = currentCoord.z;

	GLdouble x2 = currentCoord.x + 0.5;
	GLdouble y2 = currentCoord.y;
	GLdouble z2 = currentCoord.z;

	double x = x2 - x1;
	double y = y2 - y1;
	double z = z2 - z1;
	double L = sqrt(x*x + y * y + z * z);

	GLUquadricObj *quadObj;

	glPushMatrix();

	glTranslated(x1, y1, z1);

	if ((x != 0.) || (y != 0.)) {
		glRotated(atan2(y, x) / RADPERDEG, 0., 0., 1.);
		glRotated(atan2(sqrt(x*x + y * y), z) / RADPERDEG, 0., 1., 0.);
	}
	else if (z < 0) {
		glRotated(180, 1., 0., 0.);
	}

	glTranslatef(0, 0, L - 4 * D);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluCylinder(quadObj, 2 * D, 0.0, 4 * D, 32, 1);
	gluDeleteQuadric(quadObj);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluDisk(quadObj, 0.0, 2 * D, 32, 1);
	gluDeleteQuadric(quadObj);

	glTranslatef(0, 0, -L + 4 * D);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluCylinder(quadObj, D, D, L - 4 * D, 32, 1);
	gluDeleteQuadric(quadObj);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluDisk(quadObj, 0.0, D, 32, 1);
	gluDeleteQuadric(quadObj);

	glPopMatrix();
}
void DrawOYarrow(CVector3d currentCoord, GLdouble D) {
	GLdouble x1 = currentCoord.x;
	GLdouble y1 = currentCoord.y;
	GLdouble z1 = currentCoord.z;

	GLdouble x2 = currentCoord.x;
	GLdouble y2 = currentCoord.y + 0.5;
	GLdouble z2 = currentCoord.z;

	double x = x2 - x1;
	double y = y2 - y1;
	double z = z2 - z1;
	double L = sqrt(x*x + y * y + z * z);

	GLUquadricObj *quadObj;

	glPushMatrix();

	glTranslated(x1, y1, z1);

	if ((x != 0.) || (y != 0.)) {
		glRotated(atan2(y, x) / RADPERDEG, 0., 0., 1.);
		glRotated(atan2(sqrt(x*x + y * y), z) / RADPERDEG, 0., 1., 0.);
	}
	else if (z < 0) {
		glRotated(180, 1., 0., 0.);
	}

	glTranslatef(0, 0, L - 4 * D);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluCylinder(quadObj, 2 * D, 0.0, 4 * D, 32, 1);
	gluDeleteQuadric(quadObj);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluDisk(quadObj, 0.0, 2 * D, 32, 1);
	gluDeleteQuadric(quadObj);

	glTranslatef(0, 0, -L + 4 * D);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluCylinder(quadObj, D, D, L - 4 * D, 32, 1);
	gluDeleteQuadric(quadObj);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluDisk(quadObj, 0.0, D, 32, 1);
	gluDeleteQuadric(quadObj);

	glPopMatrix();
}
void DrawOZarrow(CVector3d currentCoord, GLdouble D) {
	GLdouble x1 = currentCoord.x;
	GLdouble y1 = currentCoord.y;
	GLdouble z1 = currentCoord.z;

	GLdouble x2 = currentCoord.x;
	GLdouble y2 = currentCoord.y;
	GLdouble z2 = currentCoord.z + 0.5;

	double x = x2 - x1;
	double y = y2 - y1;
	double z = z2 - z1;
	double L = sqrt(x*x + y * y + z * z);

	GLUquadricObj *quadObj;

	glPushMatrix();

	glTranslated(x1, y1, z1);

	if ((x != 0.) || (y != 0.)) {
		glRotated(atan2(y, x) / RADPERDEG, 0., 0., 1.);
		glRotated(atan2(sqrt(x*x + y * y), z) / RADPERDEG, 0., 1., 0.);
	}
	else if (z < 0) {
		glRotated(180, 1., 0., 0.);
	}

	glTranslatef(0, 0, L - 4 * D);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluCylinder(quadObj, 2 * D, 0.0, 4 * D, 32, 1);
	gluDeleteQuadric(quadObj);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluDisk(quadObj, 0.0, 2 * D, 32, 1);
	gluDeleteQuadric(quadObj);

	glTranslatef(0, 0, -L + 4 * D);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluCylinder(quadObj, D, D, L - 4 * D, 32, 1);
	gluDeleteQuadric(quadObj);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluDisk(quadObj, 0.0, D, 32, 1);
	gluDeleteQuadric(quadObj);

	glPopMatrix();
}
void Draw3DcoordArrow(CVector3d current3DCoord, GLdouble D)
{
	DrawOXarrow(current3DCoord, D);
	DrawOYarrow(current3DCoord, D - 0.02);
	DrawOZarrow(current3DCoord, D + 0.02);
}

void Draw3DcoordArrow2(double Xcoord, double Ycoord, double Zcoord, GLdouble D)
{
	CVector3d temp;
	temp.x = Xcoord;
	temp.y = Ycoord;
	temp.z = Zcoord;

	DrawOXarrow(temp, D);
	DrawOYarrow(temp, D - 0.02);
	DrawOZarrow(temp, D + 0.02);
}

//23/9/2019
void DrawRollingOXYZ() {
	bool rightRolling = true;
	CVector3d OXArrow(1.0, 0.5, 0.5);
	CVector3d OYArrow(0.5, 1.0, 0.5);
	CVector3d OZArrow(0.5, 0.5, 1.0);

	CVector3d  nextOrigin;
	CVector3d nextOXArrow;
	CVector3d nextOYArrow;
	CVector3d nextOZArrow;

	DrawSeparatedArrows2(rightRolling, cube.startPoint, OXArrow, OYArrow, OZArrow,
		nextOrigin, nextOXArrow, nextOYArrow, nextOZArrow); //from OpenGLDraw.cpp


	CVector3d  nextOrigin2;
	CVector3d nextOXArrow2;
	CVector3d nextOYArrow2;
	CVector3d nextOZArrow2;
	rightRolling = true;
	DrawSeparatedArrows2(rightRolling, nextOrigin, nextOXArrow, nextOYArrow, nextOZArrow,
		nextOrigin2, nextOXArrow2, nextOYArrow2, nextOZArrow2);

	//	std::cout << "nextOrigin2, nextOXArrow2,nextOYArrow2, nextOZArrow2" <<
	//		nextOrigin2.x << " " << nextOrigin2.y << " " << nextOrigin2.z << ")--(" 
	//		<< nextOXArrow2.x <<" "<< nextOXArrow2.y<<"-"<< nextOXArrow2.z <<")---("
	//		<< nextOYArrow2.x <<" "<< nextOYArrow2.y<<"-"<< nextOYArrow2.z << ")--("
	//		<< nextOZArrow2.x <<" "<< nextOZArrow2.y<<"-"<< nextOZArrow2.z << ")"<<std::endl;


	CVector3d  nextOrigin3;
	CVector3d nextOXArrow3;
	CVector3d nextOYArrow3;
	CVector3d nextOZArrow3;
	rightRolling = true;
	DrawSeparatedArrows2(rightRolling, nextOrigin2, nextOXArrow2, nextOYArrow2, nextOZArrow2,
		nextOrigin3, nextOXArrow3, nextOYArrow3, nextOZArrow3);

	CVector3d  nextOrigin4;
	CVector3d nextOXArrow4;
	CVector3d nextOYArrow4;
	CVector3d nextOZArrow4;
	rightRolling = true;
	DrawSeparatedArrows2(rightRolling, nextOrigin3, nextOXArrow3, nextOYArrow3, nextOZArrow3,
		nextOrigin4, nextOXArrow4, nextOYArrow4, nextOZArrow4);


	CVector3d  nextOrigin5;
	CVector3d nextOXArrow5;
	CVector3d nextOYArrow5;
	CVector3d nextOZArrow5;
	rightRolling = true;
	DrawSeparatedArrows2(rightRolling, nextOrigin4, nextOXArrow4, nextOYArrow4, nextOZArrow4,
		nextOrigin5, nextOXArrow5, nextOYArrow5, nextOZArrow5);

	CVector3d  nextOrigin6;
	CVector3d nextOXArrow6;
	CVector3d nextOYArrow6;
	CVector3d nextOZArrow6;
	rightRolling = true;
	DrawSeparatedArrows2(rightRolling, nextOrigin5, nextOXArrow5, nextOYArrow5, nextOZArrow5,
		nextOrigin6, nextOXArrow6, nextOYArrow6, nextOZArrow6);
	CVector3d  nextOrigin7;
	CVector3d nextOXArrow7;
	CVector3d nextOYArrow7;
	CVector3d nextOZArrow7;
	rightRolling = false;
	DrawSeparatedArrows2(rightRolling, nextOrigin6, nextOXArrow6, nextOYArrow6, nextOZArrow6,
		nextOrigin7, nextOXArrow7, nextOYArrow7, nextOZArrow7);

	CVector3d  nextOrigin8;
	CVector3d nextOXArrow8;
	CVector3d nextOYArrow8;
	CVector3d nextOZArrow8;
	rightRolling = true;
	DrawSeparatedArrows2(rightRolling, nextOrigin7, nextOXArrow7, nextOYArrow7, nextOZArrow7,
		nextOrigin6, nextOXArrow8, nextOYArrow8, nextOZArrow8);
}

/*=================================================*/
/*            Tetrahedron		                   */
/*=================================================*/

void drawTriangleGrid() {
	int i;

	for (int i(0); i < 40; i++) {
		glPushMatrix();

		if (i < 20) { glTranslatef(0, i, 0); }
		if (i >= 20) { glTranslatef(i - 20, 0, 0); glRotatef(-30, 0, 0, -1); }

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glLineWidth(1);
		glVertex3f(0, -0.1, 0);
		glVertex3f(19, -0.1, 0);
		glEnd();

		glPopMatrix();
	}
}