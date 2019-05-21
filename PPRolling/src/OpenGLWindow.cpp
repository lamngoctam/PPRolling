//#include "..\include\OpenGLWindow.h"

//############################################################################
//
//############################################################################

#include "stdafx.h"
#include "OpenGL.h"
#include "OpenGLprimitive.h"

using namespace std;

extern int WinID[2];
OpenGL GLSettings0;

extern OctVoxel cube;
//AntTweakBar
float BackTopColor[] = { 0.941f, 1.0f, 1.0f };
float BackBotColor[] = { 0.275f, 0.51f, 0.706f };


//keyboard
bool b_key_0 = 1;   // Bounding Box
bool z_key_0 = 1;   // Axis


//Flag link to AntweakBar
extern int ShowAxisFlag;		//Axis
extern int ShowBB;				// Bounding Box

void DisplayInit();
void DisplayPostprocessor();

void OpenGLReshape0(int width, int height);

void OpenGLIdle();
void onIdle(void); //16/05/2019

void OpenGLInitialize(int WindowID, OpenGL GLSettings, int InitPosiX, int InitPosiY,
	int WindowWidth, int WindowHeight, const char* WindowName);
void OpenGLPostprocessor(OpenGL GLSettings);
void PickUpInit(int x, int y);
void PickUpPostprocessor(void);
int SelectHits(GLuint hits, GLuint* buf, int hit_name[2]);
double ReturnDepth(int x, int y);

//AntTweakBar
void TwCallBack(void);
void GradientBackGround(float *tcolor, float *bcolor);

//draw Axis
void ConclusiveAxis(void);

/***************************************************/
/*													*/
/***************************************************/
//	http://e-words.jp/p/r-ascii.html
//BackSpace
//	16?	'\x08'	C++
//	 8?	'\010'	C++
void OpenGLKeyboard0(unsigned char Key, int x, int y) {

	switch (Key)
	{
	case '\x1b':	//Esc
		std::cout << "Exit OpenGL System" << std::endl;
		glutLeaveMainLoop();		//OpenGL main()
		break;
	case '\x0d':	//Enter
		break;

	case '\x20':	//Space
		break;

	case '\x7f':	//Delete
		break;

	case '\x08':	//BackSpace
		break;

	case '\t':		//TAB
		break;

	case 'a':
		break;

	case 's':
		break;

	case 'A':
		break;

	case 'p':
		b_key_0 = !b_key_0;        // Bouding Box
		break;

	case '+':
		break;

	case '-':
		break;

	case '0':
		break;

	case '5':
		break;

	case '6':
		break;

	case '4':
		break;

	case '8':
		break;

	case '2':
		break;

	case '1':	//???_???
		GLSettings0.m_EyeDis = 20;
		GLSettings0.m_Center = CVector3d(0.0, 0.0, 0.0);
		GLSettings0.m_Front = CVector3d(0.0, 0.0, -1.0);
		GLSettings0.m_Upper = CVector3d(0.0, 1.0, 0.0);
		break;

	case '@':
		break;


	case 'm':
		break;

	case 'z':
		z_key_0 = !z_key_0;  // Axis
		break;
	}

	glutPostRedisplay();
}

//
//	http://opengl.jp/glut/section07-09.html
void OpenGLSpecial0(int Key, int x, int y) {
	switch (Key)
	{

	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;

	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;

	case GLUT_KEY_PAGE_UP:
		break;
	case GLUT_KEY_PAGE_DOWN:
		break;
	}
	glutPostRedisplay();
}

int PickUp0(int x, int y, int hit_name[2], int Button) {
	GLint hits;
	GLuint selectBuf[BUFSIZE];
	glSelectBuffer(BUFSIZE, selectBuf);

	PickUpInit(x, y);
	GLSettings0.SetEyePosition();
	/************************************/
	/*				*/
	/************************************/
	//if(p_key_0){	//Teapots
	//	glPushName(0);	//hit_name[0]
	//	DrawVertices(Vertices);	//
	//	glPopName();
	//}

	//if(t_key_0){	//Doughnuts
	//	glPushName(1);	//hit_name[0]
	//	DrawTorus(Doughnuts);	
	//	glPopName();
	//}

	/************************************/
	/*			*/
	/************************************/
	PickUpPostprocessor();

	hits = glRenderMode(GL_RENDER);


	return SelectHits(hits, selectBuf, hit_name);
}

void PickObject0(int x, int y, int Button) {
	int hit_name[2];
	//hit_name[0]	
	//hit_name[1]	

	//hit_name[0]==PICLEDMODEL1?Ahit_name[1]==2

	if (PickUp0(x, y, hit_name, Button) == -1)
	{

		GLSettings0.ObjectPosition = &GLSettings0.ObjectTemp;
		return;
	}


	GLSettings0.m_ObjectDepth = ReturnDepth(x, y);


	/************************************/
	/*		*/
	/************************************/
	//if( hit_name[0]==0 ){	
	//	std::cout <<"******";
	//	GLSettings0.ObjectPosition = &Vertices[hit_name[1]];	
	//}
	//else if( hit_name[0]==1 ){	
	//	std::cout <<"Doughnuts";
	//	GLSettings0.ObjectPosition = &Doughnuts[hit_name[1]];
	//}
	/************************************/
	/*			*/
	/************************************/
	std::cout << hit_name[1] << "botay" << endl;

}


//AntTweakBar
void OpenGLMouse0(int Button, int State, int x, int y) {

	if (State == GLUT_DOWN)
	{
		GLSettings0.m_Moving = 0;
		GLSettings0.m_State = GLUT_DOWN;
		GLSettings0.m_Button = Button;
		GLSettings0.m_mouseLastX = x;
		GLSettings0.m_mouseLastY = y;


		if (Button == GLUT_LEFT_BUTTON)
		{

			PickObject0(x, y, Button);
		}
	}

	else if (State == GLUT_UP)
	{
		GLSettings0.m_State = GLUT_UP;
		GLSettings0.m_Button = NONE;
	}
	glutPostRedisplay();
}

void OpenGLMotion0(int x, int y) {
	GLSettings0.MovingMouse(x, y);
}

void OpenGLMouseWheel0(int wheel_number, int direction, int x, int y) {
	GLSettings0.DoMouseWheel(direction);
};

void OpenGLReshape0(int width, int height) {
	GLSettings0.m_Aspect = static_cast<double>(width) / static_cast<double>(height);
	GLSettings0.m_WindowWidth = width;
	GLSettings0.m_WindowHeight = height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(10.0, GLSettings0.m_Aspect, 0.01, -1.0);
	glMatrixMode(GL_MODELVIEW);

	//[AntTweakBar]//
	TwWindowSize(width, height);
}


/****************************************************/
/*				AntTweakBar					        */
/****************************************************/
void OnMouseMotion(int mouseX, int mouseY)  // your callback function called by GLUT when mouse has moved
{
	// - Directly redirect GLUT mouse motion events to AntTweakBar
	if (!TwEventMouseMotionGLUT(mouseX, mouseY))  // send event to AntTweakBar
	{ // event has not been handled by AntTweakBar
		GLSettings0.m_Moving = 1;
		GLSettings0.MovingMouse(mouseX, mouseY);
	}
}

void MouseButton(int Button, int State, int x, int y) // your callback function called by GLUT when mouse has moved
{
	if (!TwEventMouseMotionGLUT(x, y))  // send event to AntTweakBar
	{ // event has not been handled by AntTweakBar
		OpenGLMouse0(Button, State, x, y);
	}
	else
	{
		// - Directly redirect GLUT mouse button events to AntTweakBar
		TwEventMouseButtonGLUT(Button, State, x, y);
	}
}

void PassiveMotion(int x, int y) {
	if (TwEventMouseMotionGLUT(x, y))  // send event to AntTweakBar
		// - Directly redirect GLUT mouse "passive" motion events to AntTweakBar (same as MouseMotion)
		TwEventMouseMotionGLUT(x, y);
}

void KeyboardFunc(unsigned char Key, int x, int y) {
	if (!TwEventMouseMotionGLUT(x, y))  // send event to AntTweakBar
	{ // event has not been handled by AntTweakBar
		OpenGLKeyboard0(Key, x, y);
	}
	else
	{
		// - Directly redirect GLUT key events to AntTweakBar
		TwEventKeyboardGLUT(Key, x, y);
	}
}

void SpecialKey(int glutKey, int x, int y) {
	if (!TwEventMouseMotionGLUT(x, y))  // send event to AntTweakBar
	{ // event has not been handled by AntTweakBar
		OpenGLSpecial0(glutKey, x, y);
	}
	else
	{
		// - Directly redirect GLUT special key events to AntTweakBar
		TwEventSpecialGLUT(glutKey, x, y);
	}
}

//-------------------------------------//   
//
//          test for animation
//
//-------------------------------------//


double rot = 0;		//16/05/2019
int angle = 0;		//17/05/2019

int angleRight = 0;		//21/05/2019
int angleUp = 0;		//21/05/2019


bool sDirection (true);
int rotCountRight(0);
int rotCountUp(0);

void SpecialKeyRolling(unsigned char key, int x, int y) {

	switch (key) {
	case 'r':
		if(sDirection == true)
		{
			//angleRight = (angleRight - 1) % 90;
			angleRight++;
			glutPostRedisplay();
			rotCountRight++;
		}
		else if (sDirection == false)
		{
			//angleUp = (angleUp - 1) % 90;
			angleUp++;
			glutPostRedisplay();
			rotCountUp++;
		}
		break;
	case 't':
		sDirection = false;
		{
			//angleUp = (angleUp - 1) % 90;
			angleUp++;
			glutPostRedisplay();
			rotCountUp++;
		}
		break;

	case GLUT_KEY_UP:
		cube.count_y = cube.count_y + 1;
		cout << y << endl;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		cube.count_x = cube.count_x + 1;
		cout << x << endl;
		glutPostRedisplay();
		break;

	}
}

//-----------------------------------------------------------------------
// Voxel
void DrawBoundingbox(CVector3d MaxPt, CVector3d MinPt, int colorID);
void DrawGrid();
void DrawStartEndPoint(CVector3d startPoint, CVector3d endPoint);
void DrawCube_originPoint(CVector3d originPoint, int colorID);
void DrawCube(CVector3d centerPoint, int colorID);
void checkPoint(int colorID);

void PathPlanning();
void PathPlanning2();

void cubeRotation(CVector3d axisRotation);

/***************************************************/
//			OpenGLDisplay0
/***************************************************/
void OpenGLDisplay0(void) {
	DisplayInit();
	GLSettings0.SetEyePosition();

	//AntTweakBar
	GradientBackGround(BackTopColor, BackBotColor);		//from OpenGLDraw.cpp
	//TwDraw();
	//glGetString(GL_VERSION);

	if (ShowAxisFlag)
		ConclusiveAxis();

	//14/5/2019
	DrawGrid();
	//DrawStartEndPoint(cube.startPoint, cube.goalPoint);

	//15/5/2019
	//checkPoint(5);

	//16/5/19
	//draw center of starting & endingPoint
	//DrawSphere(cube.startPoint, 0.1);
	//DrawSphere(cube.goalPoint, 0.1);

	//draw starting & ending cube
	DrawCube(cube.startPoint, 15);
	DrawCube(cube.goalPoint, 72);
	DrawCube(cube.newOrigin, 20);

	DisplayPostprocessor();



}


/*=================================================*/
//				OpenGlCallBack0
/*=================================================*/
void OpenGLCallBack0(void) {

	GLSettings0.PickObject = PickObject0;
	OpenGLInitialize(0, GLSettings0, 0, 0, 1024, 768, "window");

	glutDisplayFunc(OpenGLDisplay0);		//display call back function

	//TwCallBack(); //AntTweakBar

	glutMouseFunc(MouseButton);
	glutMotionFunc(OnMouseMotion);
	glutPassiveMotionFunc(PassiveMotion);
	glutKeyboardFunc(KeyboardFunc);				//keyboard call
	glutSpecialFunc(SpecialKey);
	glutMouseWheelFunc(OpenGLMouseWheel0);

	glutIdleFunc(OpenGLIdle);

	TwGLUTModifiersFunc(glutGetModifiers);
	glutReshapeFunc(OpenGLReshape0);

	OpenGLPostprocessor(GLSettings0);
}

/*=================================================*/
//				For Animation
/*=================================================*/

//16/05/2019
void onIdle(void) {
	rot += 0.5;
	glutPostRedisplay();
}

void DisplayAnimation_(void) {
	DisplayInit();

	GLSettings0.SetEyePosition();

	//AntTweakBar
	GradientBackGround(BackTopColor, BackBotColor);
	ConclusiveAxis();
	DrawGrid();

	glColor3f(0.0, 1.0, 1.0);
	//glutWireCube(1.0);
	glFlush();

	//DrawCube_originPoint(cube.origin, 9);

	DrawCube(cube.startPoint, 37);
	DrawCube(cube.goalPoint, 11);
	//
	//DrawCube(cube.newOrigin, 9);
	for (int i = 0; i < cube.cubeCenter.size(); i++) {

		//DrawCube(cube.cubeCenter[i], 58);
	}

	for (int i = 0; i < cube.edgeContactUpLeft.size(); i++) {
		//DrawCube_originPoint(cube.edgeContactUpLeft[i], 9);
	}

	checkPoint(5);
	///********************************/

	DisplayPostprocessor();
}

//21/05 OK for rolling with all cube, can not delete the old cube
void DisplayAnimation(void) {
	//DrawGrid();
	//
	//for (int i(0); i < cube.cubeCenter.size(); i++) {
		//angle = 0;
		//while (angle < 90) {

	DisplayInit();
	GLSettings0.SetEyePosition();
	GradientBackGround(BackTopColor, BackBotColor);
	ConclusiveAxis();
	DrawGrid();

	//1	
	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef(-angle, 0, 1, 0);
	glTranslatef(-0.5, 0.5, 0.5);
	glutWireCube(1);
	glPopMatrix();

	//2
	glPushMatrix();
	glTranslatef(2.0, 0.0, 0.0);
	glRotatef(-angle, 0, 1, 0);
	glTranslatef(-0.5, 0.5, 0.5);
	glutWireCube(1);
	glPopMatrix();

	//3
	glPushMatrix();
	glTranslatef(0.0, 1.0, 0.0);
	glRotatef(angle, 1, 0, 0);
	glTranslatef(2.5, -0.5, 0.5);
	glutWireCube(1);
	glPopMatrix();




	//	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
		//SolidCuboid(cube.cubeCenter[i], 1.0);


		//DrawGrid();
		//
		//glColor3f(0.0, 1.0, 1.0);
		//glutWireCube(1.0);
		//glFlush();
		//
		////DrawCube_originPoint(cube.origin, 9);
		//
		//DrawCube(cube.startPoint, 37);
		//DrawCube(cube.goalPoint, 11);
		////
		////DrawCube(cube.newOrigin, 9);
		//for (int i = 0; i < cube.cubeCenter.size(); i++) {
		//	
		//	//DrawCube(cube.cubeCenter[i], 58);
		//}
		//
		//for (int i = 0; i < cube.edgeContactUpLeft.size(); i++) {
		//	//DrawCube_originPoint(cube.edgeContactUpLeft[i], 9);
		//}
		//
		//checkPoint(5);

	DisplayPostprocessor();

	//angle += 0.5;
	//
	//glutPostRedisplay();
//}
//}

}




void DisplayAnimation_deletecube(void) {

	DisplayInit();
	GLSettings0.SetEyePosition();
	GradientBackGround(BackTopColor, BackBotColor);
	ConclusiveAxis();
	DrawGrid();

	if (sDirection) {
		//1	
		if (rotCountRight <= 90) {
			glPushMatrix();
			glTranslatef(1.0, 0.0, 0.0);
			glRotatef(angleRight, 0, 1, 0);
			glTranslatef(-0.5, 0.5, 0.5);
			glutWireCube(1);
			glPopMatrix();

			cout << angleRight << " " << rotCountRight << endl;
			if (rotCountRight == 90) {
				angleRight = 0;
			}
		}
		//2
		//else if ((rotCountRight >90) && (rotCountRight <= 90*2)) {
		//	glPushMatrix();
		//	glTranslatef(2.0, 0.0, 0.0);
		//	glRotatef(angleRight, 0, 1, 0);
		//	glTranslatef(-0.5, 0.5, 0.5);
		//	glutWireCube(1);
		//	glPopMatrix();
		//	cout << "2nd " <<angleRight << " " << rotCountRight << endl;
		//	if (rotCountRight == 90 * 2) {
		//		angleRight = 0;
		//	}
		//}
		////3
		//else if ((rotCountRight > 90 * 2) && (rotCountRight <= 90 * 3)) {
		//	glPushMatrix();
		//	glTranslatef(3.0, 0.0, 0.0);
		//	glRotatef(angleRight, 0, 1, 0);
		//	glTranslatef(-0.5, 0.5, 0.5);
		//	glutWireCube(1);
		//	glPopMatrix();
		//	cout << "2nd " << angleRight << " " << rotCountRight << endl;
		//	if (rotCountRight == 90 * 3) {
		//		angleRight = 0;
		//	}
		//}
		else if (rotCountRight > 90 ){
			//angleRight = 0;
			//rotCountRight = 0;
			sDirection = false;
		}
	}
	else if (sDirection == false)
	{
		//3
		if (rotCountUp <= 90) {
			glPushMatrix();
			glTranslatef(0.0, 1.0, 0.0);
			glRotatef(-angleUp, 1, 0, 0);
			glTranslatef(1.5, -0.5, 0.5);
			glutWireCube(1);
			glPopMatrix();

			if (rotCountUp == 90) {
				angleUp = 0;
			}
		}
		else if (rotCountUp > 90) {
			//angleRight = 0;
			//rotCountRight = 0;
			sDirection = true;
		}
	}

	else {

	}
	DisplayPostprocessor();

}

void OpenGLCallBackAnimation(void) {
	GLSettings0.PickObject = PickObject0;
	OpenGLInitialize(0, GLSettings0, 0, 0, 1024, 768, "window");

	//glutDisplayFunc(DisplayAnimation_);		//17/05
	//glutDisplayFunc(DisplayAnimation);		//18/05
	glutDisplayFunc(DisplayAnimation_deletecube);		//18/05

	//TwCallBack(); //AntTweakBar

	glutMouseFunc(MouseButton);
	glutMotionFunc(OnMouseMotion);
	glutPassiveMotionFunc(PassiveMotion);

	//glutKeyboardFunc(KeyboardFunc);				//keyboard call
	glutKeyboardFunc(SpecialKeyRolling);				//keyboard call

	glutSpecialFunc(SpecialKey);
	glutMouseWheelFunc(OpenGLMouseWheel0);

	//glutIdleFunc(onIdle); // call glutPostRedisplay();

	//TwGLUTModifiersFunc(glutGetModifiers);
	glutReshapeFunc(OpenGLReshape0);

	OpenGLPostprocessor(GLSettings0);
}