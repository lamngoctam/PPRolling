//#include "..\include\OpenGLWindow.h"

//############################################################################
//
//############################################################################

#include "stdafx.h"
#include "OpenGL.h"
#include "OpenGLprimitive.h"

#include "OctVoxel.h"
using namespace std;

extern int WinID[2];
OpenGL GLSettings0;

extern OctVoxel cube;
extern OctVoxel* label;


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

bool sDirection = true;
int rotCountRight(0);
int rotCountUp(0);

int countIn(0);
int countOut(0);
void drawAnimateCubes_finalV02();

int cubeX(0);
int cubeY(0);
void SpecialKeyRolling(unsigned char key, int x, int y) {

	switch (key) {
	case 'r':
		for (int i = 0; i < cube.cubeCenter.size(); i++) {

			if ((cube.rotlabel[i] == 1)) {
				sDirection = true;
				angleRight++;
				cubeX = cube.cubeCenter[i].x;
				cubeY = cube.cubeCenter[i].y;
				glutPostRedisplay();
				cout << "------------------------------right" << i << endl;

			}
			else if ((cube.rotlabel[i] == 0)) {
				sDirection = false;
				angleUp++;
				cubeX = cube.cubeCenter[i].x;
				cubeY = cube.cubeCenter[i].y;
				glutPostRedisplay();
				cout << "-------------------------------------up" << i << endl;

			}

		}
		cout << endl;cout << endl;
		break;
	case 't':
		//	sDirection = false;
		//	{
		//		//angleUp = (angleUp - 1) % 90;
		//		angleUp++;
		//		//glutPostRedisplay();
		//		rotCountUp++;
		//	}
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
		//case GLUT_KEY_F1:    // F1: Toggle between full-screen and windowed mode
		//	fullScreenMode = !fullScreenMode;         // Toggle state
		//	if (fullScreenMode) {                     // Full-screen mode
		//		windowPosX = glutGet(GLUT_WINDOW_X); // Save parameters for restoring later
		//		windowPosY = glutGet(GLUT_WINDOW_Y);
		//		windowWidth = glutGet(GLUT_WINDOW_WIDTH);
		//		windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
		//		glutFullScreen();                      // Switch into full screen
		//	}
		//	else {                                         // Windowed mode
		//		glutReshapeWindow(windowWidth, windowHeight); // Switch into windowed mode
		//		glutPositionWindow(windowPosX, windowPosX);   // Position top-left corner
		//	}
		//	break;
			// from http://www3.ntu.edu.sg/home/ehchua/programming/opengl/cg_introduction.html#zz-6.7
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

//--------------------------------------------------
//----------- test for cube appear -----------------
//--------------------------------------------------
int countcube(0);
bool presskey = true;

void drawBox(int i) {

	glTranslatef(i + 0.5, 0.5, 0.5);
	glColor3f(0.5, 0.0, 1.5);

	glPushMatrix();

	glutWireCube(1);
	glPopMatrix();

}
void displayCube(void) {
	DisplayInit();
	GLSettings0.SetEyePosition();
	GradientBackGround(BackTopColor, BackBotColor);
	ConclusiveAxis();
	DrawGrid();

	//for (int ii(0); ii < 5; ii++ ) {
	drawBox(countcube);
	//}
	cout << "countcube " << countcube << endl;


	DisplayPostprocessor();
}
void keyCube(unsigned char key, int x, int y) {

	switch (key) {
	case 'e':
		if (presskey == true)
		{
			countcube++;
			glutPostRedisplay();

			cout << "countcube " << countcube << endl;

			if (countcube == 5) {
				countcube = 0;
			}
		}
		break;
	case '1':
		GLSettings0.m_EyeDis = 30;
		GLSettings0.m_Center = CVector3d(0.0, 0.0, 0.0);
		GLSettings0.m_Front = CVector3d(0.0, 0.0, -1.0);
		GLSettings0.m_Upper = CVector3d(0.0, 1.0, 0.0);
		break;
	}
}

//16/05/2019
void onIdle(void) {
	rot += 0.5;
	glutPostRedisplay();
}

void DisplayAnimation1(void) {
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
void DisplayAnimation2(void) {
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

//24/05/2019
void DisplayAnimation_finalV03(void) {

	DisplayInit();
	GLSettings0.SetEyePosition();
	GradientBackGround(BackTopColor, BackBotColor);
	ConclusiveAxis();
	DrawGrid();

	DrawCube(cube.startPoint, 37);
	DrawCube(cube.goalPoint, 11);
	for (int i = 0; i < cube.cubeCenter.size(); i++) {

		DrawCube(cube.cubeCenter[i], 58);

		if (sDirection == true) {
			//1	
			if (rotCountRight <= 90) {
				glPushMatrix();
				glTranslatef(1.0, 0.0, 0.0);
				glRotatef(angleRight, 0, 1, 0);
				glTranslatef(-0.5, 0.5, 0.5);
				glColor3f(0.0, 1.0, 1.0);
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
			else if (rotCountRight > 90) {
				angleRight = 0;
				rotCountUp = 0;
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
				glColor3f(1.0, 1.0, 1.0);
				glutWireCube(1);
				glPopMatrix();

				if (rotCountUp == 90) {
					angleUp = 0;
				}
			}
			else if ((rotCountUp > 90) && (rotCountUp <= 90 * 2)) {
				glPushMatrix();
				glTranslatef(0.0, 2.0, 0.0);
				glRotatef(-angleUp, 1, 0, 0);
				glTranslatef(1.5, -0.5, 0.5);
				glutWireCube(1);
				glPopMatrix();

				if (rotCountUp == 90 * 2) {
					angleUp = 0;
				}
			}
			else if (rotCountUp > 90 * 2) {
				angleRight = 0;
				rotCountRight = 0;
				sDirection = true;
			}
		}
	}
	DisplayPostprocessor();

}

//24/05/2019
void drawAnimation_finalV01_2() {
	if ((sDirection == true)) {
		//right 0; cube 0-1	
		if (rotCountRight <= 90) {
			glPushMatrix();
			glTranslatef(1.0, 0.0, 0.0);
			glRotatef(angleRight, 0, 1, 0);
			glTranslatef(-0.5, 0.5, 0.5);//const
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(1);
			glPopMatrix();

			cout << "1st " << angleRight << " " << rotCountRight << endl;
			if (rotCountRight == 90) {
				angleRight = 0;
				sDirection = false;
				rotCountUp = 0;
			}
		}
		//right 1; cube 1-2
		else if ((rotCountRight > 90) && (rotCountRight <= 90 * 2)) {
			glPushMatrix();
			glTranslatef(2.0, 1.0, 0.0);
			glRotatef(angleRight, 0, 1, 0);
			glTranslatef(-0.5, 0.5, 0.5);//const
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(1);
			glPopMatrix();
			cout << "2nd " << angleRight << " " << rotCountRight << endl;
			if (rotCountRight == 90 * 2) {
				angleRight = 0;
			}
		}
		//// right 2; cube 2-3
		else if ((rotCountRight > 90 * 2) && (rotCountRight <= 90 * 3)) {
			glPushMatrix();
			glTranslatef(3.0, 1.0, 0.0);
			glRotatef(angleRight, 0, 1, 0);
			glTranslatef(-0.5, 0.5, 0.5);//const
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(1);
			glPopMatrix();
			cout << "3rd " << angleRight << " " << rotCountRight << endl;
			if (rotCountRight == 90 * 3) {
				angleRight = 0;
				sDirection = false;
				rotCountUp = 91;
			}
		}
		//right 3; cube 3-4
		else if ((rotCountRight > 90 * 3) && (rotCountRight <= 90 * 4)) {
			glPushMatrix();
			glTranslatef(4.0, 2.0, 0.0);
			glRotatef(angleRight, 0, 1, 0);
			glTranslatef(-0.5, 0.5, 0.5); //const
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(1);
			glPopMatrix();
			cout << "4th " << angleRight << " " << rotCountRight << endl;
			if (rotCountRight == 90 * 4) {
				angleRight = 0;
				sDirection = false;
				rotCountUp = 90 * 2 + 1;

			}
		}
		//right 4; cube 4-5
		else if ((rotCountRight > 90 * 4) && (rotCountRight <= 90 * 5)) {
			glPushMatrix();
			glTranslatef(5.0, 3.0, 0.0);
			glRotatef(angleRight, 0, 1, 0);
			glTranslatef(-0.5, 0.5, 0.5); //const
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(1);
			glPopMatrix();
			cout << "5th " << angleRight << " " << rotCountRight << endl;
			if (rotCountRight == 90 * 5) {
				angleRight = 0;
				rotCountUp = 90 * 3 + 1;
				sDirection = false;
			}
		}
		else if (rotCountRight > 90 * 5) {
			angleUp = 0;
			rotCountUp = 0;
			sDirection = false;

		}
	}
	else if ((sDirection == false))
	{
		//up0 from right 0-1
		if (rotCountUp <= 90) {
			glPushMatrix();
			glTranslatef(0.0, 1.0, 0.0);
			glRotatef(-angleUp, 1, 0, 0);
			glTranslatef(1.5, -0.5, 0.5); //const
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(1);
			glPopMatrix();
			if (rotCountUp == 90) {
				angleUp = 0;
				sDirection = true;
				rotCountRight = 91;
			}
		}//up 1 from right 2-3
		else if ((rotCountUp > 90) && (rotCountUp <= 90 * 2)) {
			glPushMatrix();
			glTranslatef(2.0, 2.0, 0.0);
			glRotatef(-angleUp, 1, 0, 0);
			glTranslatef(1.5, -0.5, 0.5); //const
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(1);
			glPopMatrix();
			if (rotCountUp == 90 * 2) {
				angleUp = 0;
				sDirection = true;
				rotCountRight = 90 * 3 + 1;
			}
		}//up2 from 3-4
		else if ((rotCountUp > 90 * 2) && (rotCountUp <= 90 * 3)) {
			glPushMatrix();
			glTranslatef(3.0, 3.0, 0.0);
			glRotatef(-angleUp, 1, 0, 0);
			glTranslatef(1.5, -0.5, 0.5);  //const
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(1);
			glPopMatrix();
			if (rotCountUp == 90 * 3) {
				angleUp = 0;
				sDirection = true;
				rotCountRight = 90 * 4 + 1;
			}
		}
		else if (rotCountUp > 90 * 3) {
			angleRight = 0;
			rotCountRight = 0;
			sDirection = true;
		}
	}
}
//21/05/2019
void drawAnimation_finalV01() {
	if ((sDirection == true)) {
		//right 0; cube 0-1	
		if (rotCountRight <= 90) {
			glPushMatrix();
			glTranslatef(1.0, 0.0, 0.0);
			glRotatef(angleRight, 0, 1, 0);
			glTranslatef(-0.5, 0.5, 0.5);//const
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(1);
			glPopMatrix();

			cout << "1st " << angleRight << " " << rotCountRight << endl;
			if (rotCountRight == 90) {
				angleRight = 0;
			}
		}
		//right 1; cube 1-2
		else if ((rotCountRight > 90) && (rotCountRight <= 90 * 2)) {
			glPushMatrix();
			glTranslatef(2.0, 1.0, 0.0);
			glRotatef(angleRight, 0, 1, 0);
			glTranslatef(-0.5, 0.5, 0.5);//const
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(1);
			glPopMatrix();
			cout << "2nd " << angleRight << " " << rotCountRight << endl;
			if (rotCountRight == 90 * 2) {
				angleRight = 0;
			}
		}
		//// right 2; cube 2-3
		else if ((rotCountRight > 90 * 2) && (rotCountRight <= 90 * 3)) {
			glPushMatrix();
			glTranslatef(3.0, 1.0, 0.0);
			glRotatef(angleRight, 0, 1, 0);
			glTranslatef(-0.5, 0.5, 0.5);//const
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(1);
			glPopMatrix();
			cout << "3rd " << angleRight << " " << rotCountRight << endl;
			if (rotCountRight == 90 * 3) {
				angleRight = 0;
			}
		}
		//right 3; cube 3-4
		else if ((rotCountRight > 90 * 3) && (rotCountRight <= 90 * 4)) {
			glPushMatrix();
			glTranslatef(4.0, 2.0, 0.0);
			glRotatef(angleRight, 0, 1, 0);
			glTranslatef(-0.5, 0.5, 0.5); //const
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(1);
			glPopMatrix();
			cout << "4th " << angleRight << " " << rotCountRight << endl;
			if (rotCountRight == 90 * 4) {
				angleRight = 0;
			}
		}
		//right 4; cube 4-5
		else if ((rotCountRight > 90 * 4) && (rotCountRight <= 90 * 5)) {
			glPushMatrix();
			glTranslatef(5.0, 3.0, 0.0);
			glRotatef(angleRight, 0, 1, 0);
			glTranslatef(-0.5, 0.5, 0.5); //const
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(1);
			glPopMatrix();
			cout << "5th " << angleRight << " " << rotCountRight << endl;
			if (rotCountRight == 90 * 5) {
				angleRight = 0;
			}
		}
		else if (rotCountRight > 90 * 5) {
			angleUp = 0;
			rotCountUp = 0;
			sDirection = false;
		}
	}
	else if ((sDirection == false))
	{
		//up0 from right 0-1
		if (rotCountUp <= 90) {
			glPushMatrix();
			glTranslatef(0.0, 1.0, 0.0);
			glRotatef(-angleUp, 1, 0, 0);
			glTranslatef(1.5, -0.5, 0.5); //const
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(1);
			glPopMatrix();
			if (rotCountUp == 90) {
				angleUp = 0;
			}
		}//up 1 from right 2-3
		else if ((rotCountUp > 90) && (rotCountUp <= 90 * 2)) {
			glPushMatrix();
			glTranslatef(2.0, 2.0, 0.0);
			glRotatef(-angleUp, 1, 0, 0);
			glTranslatef(1.5, -0.5, 0.5); //const
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(1);
			glPopMatrix();
			if (rotCountUp == 90 * 2) {
				angleUp = 0;
			}
		}//up2 from 3-4
		else if ((rotCountUp > 90 * 2) && (rotCountUp <= 90 * 3)) {
			glPushMatrix();
			glTranslatef(3.0, 3.0, 0.0);
			glRotatef(-angleUp, 1, 0, 0);
			glTranslatef(1.5, -0.5, 0.5);  //const
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(1);
			glPopMatrix();
			if (rotCountUp == 90 * 3) {
				angleUp = 0;
			}
		}
		else if (rotCountUp > 90 * 3) {
			angleRight = 0;
			rotCountRight = 0;
			sDirection = true;
		}
	}
}
void DisplayAnimation_finalV01(void) {

	DisplayInit();
	GLSettings0.SetEyePosition();
	GradientBackGround(BackTopColor, BackBotColor);
	ConclusiveAxis();
	DrawGrid();

	DrawCube(cube.startPoint, 1);
	DrawCube(cube.goalPoint, 11);

	for (int i = 0; i < cube.cubeCenter.size(); i++) {
		cout << "temp " << i << endl;

		glColor3f(0.5, 1.0, 0.5);
		DrawSphere(cube.cubeCenter[i], 0.1);

		drawAnimation_finalV01_2();
		cout << "Finish to roll cube 90 !!!" << endl;
	}
	cout << "out of for loop" << endl;
	//getchar();
	DisplayPostprocessor();
}

//21/05/2019 midnight 
// for right rolling:
// xx= cube.pointRight.x - 0.5; yy = cube.pointRight.y - 0.5
// glTranslatef(xx, yy, zz);
// glRotatef(angleRight, 0, 1, 0);
// glTranslatef(-0.5, 0.5, 0.5);//const
//
// for up rolling:
// xx= cube.pointUp.x - 1.5; yy = cube.pointUp.y - 0.5
// glTranslatef(xx, yy, zz);
// glRotatef(-angleUp, 1, 0, 0);
// glTranslatef(1.5, -0.5, 0.5); //const

int xx(0);
int yy(0);

void drawAnimateCubes_finalV02() {
	for (int temp = 0; temp < cube.cubeCenter.size(); temp++) {
		//	cout << "temp" << temp << endl;
		glColor3f(0.5, 1.0, 0.5);
		DrawSphere(cube.cubeCenter[temp], 0.1);
		//right rolling
		for (int i = 0; i < cube.cubeCenter.size();i++) {
			xx = cube.cubeCenter[i].x;
			yy = cube.cubeCenter[i].y;

			if ((cube.rotlabel[i] == 1)) {
				//cout << "-----------------------------------RIGHT---" << endl;
				sDirection = true;
				if (rotCountRight <= 90) {
					glPushMatrix();
					glTranslatef(xx - 0.5, yy - 0.5, 0.0);
					glRotatef(angleRight, 0, 1, 0);
					glTranslatef(-0.5, 0.5, 0.5);//const
					glColor3f(0.5, 0.5, 1.0); glutSolidCube(1);
					glColor3f(1.5, 1.5, 1.5); glutWireCube(1);
					glPopMatrix();
				}//when stop>???????????????????????
				else if (rotCountRight > 90) {
					angleRight = 0;
					rotCountRight = 0;
					sDirection = false;

				}
				//cout << "rotCOuntRight " << rotCountRight << endl;

				cout << "coutin " << countIn << endl;

			}
			else if (cube.rotlabel[i] == 0) {
				//cout << "-----------------------------------up---" << endl;
			//else if(sDirection == false){
				sDirection = false;

				if (rotCountUp <= 90) {
					glPushMatrix();
					glTranslatef(xx - 1.5, yy - 0.5, 0.0);
					glRotatef(-angleUp, 1, 0, 0);
					glTranslatef(1.5, -0.5, 0.5); //const
					glColor3f(0.0, 0.5, 1.0); glutSolidCube(1);
					glColor3f(1.0, 0.5, 1.5); glutWireCube(1);
					glPopMatrix();
				}//when stop>??????????????????????? 
				else if (rotCountUp > 90) {
					angleUp = 0;
					rotCountUp = 0;
					sDirection = true;
				}
			}
			else {

			}
		}
	}
}



void drawAnimateCubes_finalV03() {
	if (sDirection == true) {

		glPushMatrix();
		glTranslatef(cubeX - 0.5, cubeY - 0.5, 0.0);
		glRotatef(angleRight, 0, 1, 0);
		glTranslatef(-0.5, 0.5, 0.5);//const
		glColor3f(0.5, 0.5, 1.0); glutSolidCube(1);
		glColor3f(1.5, 1.5, 1.5); glutWireCube(1);
		glPopMatrix();
	}
	else if (sDirection == false) {
		glPushMatrix();
		glTranslatef(cubeX - 1.5, cubeY - 0.5, 0.0);
		glRotatef(-angleUp, 1, 0, 0);
		glTranslatef(1.5, -0.5, 0.5); //const
		glColor3f(0.0, 0.5, 1.0); glutSolidCube(1);
		glColor3f(1.0, 0.5, 1.5); glutWireCube(1);
		glPopMatrix();
	}
}
void DisplayAnimation_finalV02(void) {

	DisplayInit();

	GLSettings0.SetEyePosition();
	GradientBackGround(BackTopColor, BackBotColor);
	ConclusiveAxis();
	DrawGrid();

	DrawCube(cube.goalPoint, 11);

	drawAnimateCubes_finalV02();

	//for (int temp = 0; temp < cube.cubeCenter.size(); temp++) {
	//	cout << "temp" << temp << endl;
	//	glColor3f(0.5, 1.0, 0.5);
	//	DrawSphere(cube.cubeCenter[temp], 0.1);
	//
	//	//drawAnimateCubes_finalV02(temp);
	//	cout << "Finish to roll cube 90 !!!" << endl;
	//
	//
	//}

	//cout << "out of for loop" << endl;

	DisplayPostprocessor();
	//getchar();

}
void time_callback_finalV03(int) {
	glutPostRedisplay();
	glutTimerFunc(10, time_callback_finalV03, 0);

	for (int i = 0; i < cube.cubeCenter.size(); i++) {

		if ((cube.rotlabel[i] == 1)) {
			sDirection = true;
			angleRight++;
			cubeX = cube.cubeCenter[i].x;
			cubeY = cube.cubeCenter[i].y;
			glutPostRedisplay();
			cout << "------------------------------right" << i << endl;

		}
		else if ((cube.rotlabel[i] == 0)) {
			sDirection = false;
			angleUp++;
			cubeX = cube.cubeCenter[i].x;
			cubeY = cube.cubeCenter[i].y;
			glutPostRedisplay();
			cout << "-------------------------------------up" << i << endl;

		}

	}
	cout << endl;
	cout << endl;


}
void time_callback(int) {
	glutPostRedisplay();
	glutTimerFunc(10, time_callback, 0);

	if (sDirection == true)
	{
		angleRight++;
		glutPostRedisplay();
		rotCountRight++;
		cout << "angle " << angleRight << " count " << rotCountRight << endl;

		countOut++;

	}
	else if (sDirection == false)
	{
		angleUp++;
		glutPostRedisplay();
		rotCountUp++;

	}

	cout << "coutOut " << countOut << endl;

}



extern int cubeNum;
extern UnitCube *cubeNew;
extern OctVoxel *newCube;

int angleRotation(0);
int numberCube(0);

void drawModel()
{
	UnitCube cb = cubeNew[numberCube];


	for (int a = 0; a < cubeNum; a++)
	{
		if (cubeNew[a].getSelected())
		{
			if (cubeNew[a].getRightRolling()) {//right
				glPushMatrix();

				//glTranslatef(cubeNew[a].getCoordX()- 0.5, cubeNew[a].getCoordY() - 0.5, 0.0);
				glTranslatef(cb.getCoordX() - 0.5, cb.getCoordY() - 0.5, 0.0);
				//glRotatef(angleRotation, cb.getDirectionX(), cb.getDirectionY(), cb.getDirectionZ());
				glRotatef(angleRotation, 0.0, 1.0, 0.0);
				glTranslatef(-0.5, 0.5, 0.5);//const

				glColor3f(0.5, 0.5, 1.0); glutSolidCube(1);
				glColor3f(1.5, 1.5, 1.5); glutWireCube(1);
				glPopMatrix();

				cout << "+++++++++++++++++++++++right " << endl;
				goto next;
			}
			else {//up
				glPushMatrix();

				//glTranslatef(cubeNew[a].getCoordX() - 1.5, cubeNew[a].getCoordY() - 0.5, 0.0);
				glTranslatef(cb.getCoordX() - 1.5, cb.getCoordY() - 0.5, 0.0);
				//glRotatef(-angleRotation, cb.getDirectionX(), cb.getDirectionY(), cb.getDirectionZ());
				glRotatef(-angleRotation, 1.0, 0.0, 0.0);
				glTranslatef(1.5, -0.5, 0.5); //const

				glColor3f(0.5, 0.5, 1.0); glutSolidCube(1);
				glColor3f(1.5, 1.5, 1.5); glutWireCube(1);
				glPopMatrix();
				cout << "----------------------------------up " << endl;

				goto next;
			}

		}
	next: {}

	}

	if (angleRotation >= 90)
	{
		cubeNew[numberCube].setSelected(false);
		numberCube += 1;
		numberCube %= cubeNum;
		cubeNew[numberCube].setSelected(true);
		angleRotation = 0;
	}
	///getchar();
}

void drawModel2()
{
	OctVoxel cb = newCube[numberCube];


	for (int a = 0; a < cubeNum; a++)
	{
		if (newCube[a].getSelected())
		{
			if (newCube[a].getRightRolling()) {//right
				glPushMatrix();

				glTranslatef(cb.getCoordX() - 0.5, cb.getCoordY() - 0.5, 0.0);
				glRotatef(angleRotation, cb.getDirectionX(), cb.getDirectionY(), cb.getDirectionZ());
				//glRotatef(angleRotation, 0.0, 1.0, 0.0);
				glTranslatef(-0.5, 0.5, 0.5);//const

				glColor3f(0.5, 0.5, 1.0); glutSolidCube(1);
				glColor3f(1.5, 1.5, 1.5); glutWireCube(1);
				glPopMatrix();

				cout << "+++++++++++++++++++++++right " << endl;
			}
			else {//up
				glPushMatrix();

				//glTranslatef(cubeNew[a].getCoordX() - 1.5, cubeNew[a].getCoordY() - 0.5, 0.0);
				glTranslatef(cb.getCoordX() - 1.5, cb.getCoordY() - 0.5, 0.0);
				glRotatef(-angleRotation, cb.getDirectionX(), cb.getDirectionY(), cb.getDirectionZ());
				//glRotatef(-angleRotation, 1.0, 0.0, 0.0);
				glTranslatef(1.5, -0.5, 0.5); //const

				glColor3f(0.5, 0.5, 1.0); glutSolidCube(1);
				glColor3f(1.5, 1.5, 1.5); glutWireCube(1);
				glPopMatrix();
				cout << "----------------------------------up " << endl;
			}
		}
	}
	if (angleRotation >= 90)
	{
		newCube[numberCube].setSelected(false);
		numberCube += 1;
		numberCube %= cubeNum;
		newCube[numberCube].setSelected(true);
		angleRotation = 0;
	}
	///getchar();
}
void DisplayAnimation_Korea(void) {
	DisplayInit();GLSettings0.SetEyePosition();	GradientBackGround(BackTopColor, BackBotColor);	ConclusiveAxis();
	DrawGrid();	DrawCube(cube.goalPoint, 11);
	for (int i = 0; i < cube.cubeCenter.size(); i++) {
		glColor3f(0.5, 1.0, 0.5);
		DrawSphere(cube.cubeCenter[i], 0.1);
	}



	drawModel2();

	DisplayPostprocessor();
}

void OpenGLIdle_Korea(void) {
	angleRotation += 1;
	glutPostRedisplay();
}

void SpecialKeyKorea(unsigned char key, int x, int y) {

	switch (key) {
	case 'r':
		angleRotation += 1;
		glutPostRedisplay();

		cout << "cuberotation " << angleRotation << endl;

		break;

	case 't':
		//cubeNew[0].setSelected(true);
		break;
	}
}

void time_callback_Korea(int) {
	glutPostRedisplay();
	glutTimerFunc(10, time_callback_Korea, 0);

	angleRotation += 5;

	cout << "cuberotation in timeCallback(): " << angleRotation << endl;
}


void OpenGLCallBackAnimation(void) {
	GLSettings0.PickObject = PickObject0;
	//OpenGLInitialize(0, GLSettings0, 0, 0, 1024, 768, "window");
	OpenGLInitialize(0, GLSettings0, 300, 150, 1000, 650, "window");

	//glutDisplayFunc(DisplayAnimation1);		//17/05
	//glutDisplayFunc(DisplayAnimation2);		//21/05
	//glutDisplayFunc(DisplayAnimation_deletecube);		//21/05
	//glutDisplayFunc(DisplayAnimation_finalV01);		//21/05
	//glutDisplayFunc(displayCube);

	glutDisplayFunc(DisplayAnimation_Korea);		    //21/05 might night

	glutMouseFunc(MouseButton);
	glutMotionFunc(OnMouseMotion);
	glutPassiveMotionFunc(PassiveMotion);

	//glutIdleFunc(OpenGLIdle_Korea);

	//glutKeyboardFunc(SpecialKeyRolling);			//keyboard call
	//glutKeyboardFunc(SpecialKeyKorea);
	glutSpecialFunc(SpecialKey);
	glutMouseWheelFunc(OpenGLMouseWheel0);
	glutReshapeFunc(OpenGLReshape0);
	//glutTimerFunc(0, time_callback, 0); //the same with SpecialKeyRolling but faster 
	//glutTimerFunc(0, time_callback_finalV03, 0); //the same with SpecialKeyRolling but faster 
	glutTimerFunc(0, time_callback_Korea, 0); //the same with SpecialKeyRolling but faster 
	OpenGLPostprocessor(GLSettings0);
}






