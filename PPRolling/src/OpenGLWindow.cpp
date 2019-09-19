#include "stdafx.h"


extern int WinID[2];
OpenGL GLSettings0;

extern OctVoxel cube;
extern OctVoxel* label;
extern int cubeNum;
extern OctVoxel *newCube;
//extern OctVoxel *newCoord; //19/9/2019

extern bool dirRolling; //rightUp or leftUp
//AntTweakBar
float BackTopColor[] = { 0.941f, 1.0f, 1.0f };
float BackBotColor[] = { 0.275f, 0.51f, 0.706f };


//keyboard
bool b_key_0 = 1;   // Bounding Box
bool z_key_0 = 1;   // Axis


//Flag link to AntweakBar
extern int ShowAxisFlag;		//Axis
extern int ShowBB;				// Bounding Box
extern int ShowGrid;
extern int ShowStartPointFlag;
extern int ShowGoalPointFlag;
extern int ShowShortestLine;
extern int ShowCubeCenterFlag;
extern int ShowAnimationFlag;


void DisplayInit();
void DisplayPostprocessor();
void OpenGLReshape0(int width, int height);
void OpenGLIdle();
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
	std::cout << hit_name[1] << "botay" << std::endl;

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

//---------------------------------------------------
//                        Voxel
//---------------------------------------------------

void DrawBoundingbox(CVector3d MaxPt, CVector3d MinPt, int colorID);
void DrawGrid();
void DrawCubeGrid();
void DrawStartEndPoint(CVector3d startPoint, CVector3d endPoint);
void DrawCube_originPoint(CVector3d originPoint, int colorID);
void DrawCube(CVector3d centerPoint, int colorID);
void checkPoint(int colorID);

void PathPlanning();
void PathPlanning2();

void cubeRotation(CVector3d axisRotation);

//18/9/2019
void Arrow(GLdouble x1, GLdouble y1, GLdouble z1, GLdouble x2, GLdouble y2, GLdouble z2, GLdouble D);
void Draw3DcoordArrow(CVector3d currentCoord, GLdouble D);
void drawAxes(GLdouble length);
void Draw3DcoordArrow2(double Xcoord, double Ycoord, double Zcoord, GLdouble D);
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

int angleRotation(0);
int numberCube(0);

void DrawCubeRolling()
{
	OctVoxel cb = newCube[numberCube];
	//only for cube rolling right-up or left-up

	for (int a = 0; a < cubeNum; a++)
	{
		if (newCube[a].getSelected())
		{
			glLineWidth(1.9f);
			if (newCube[a].getRightRolling()) {
				glPushMatrix();

				if (dirRolling == true) { 
					//for Right-Up
					glTranslatef(cb.getCoordX() - 0.5, cb.getCoordY() - 0.5, 0.0);
					glRotatef(angleRotation, cb.getDirectionX(), cb.getDirectionY(), cb.getDirectionZ());
					//glRotatef(angleRotation, 0.0, 1.0, 0.0);
					glTranslatef(-0.5, 0.5, 0.5);//const

					//draw 3D coords  --- 19/9/2019
					glColor3f(1.0, 1.5, 1.0); 
					Draw3DcoordArrow2(cb.getCoordX() - 0.5, cb.getCoordY() - 0.5, cb.getCoordZ()-0.5, 0.01);
					//std::cout << "getCoordX" << cb.getCoordX() << " --  coordX" << cb.coordX << std::endl;
				}
				else {	
					//for Left-Up
					glTranslatef(cb.getCoordX() + 0.5, cb.getCoordY() - 0.5, 0.0);
					glRotatef(-angleRotation, cb.getDirectionX(), cb.getDirectionY(), cb.getDirectionZ());
					glTranslatef(0.5, 0.5, 0.5);//const
					Draw3DcoordArrow2(cb.getCoordX() - 0.5, cb.getCoordY() - 0.5, cb.getCoordZ() - 0.5, 0.01);
				}

				//draw cube --- 5/2019
				glColor3f(0.5, 0.5, 1.0); glutSolidCube(1);
				glColor3f(1.5, 1.5, 1.5); glutWireCube(1);
				
				


				//display object from glPushMatrix();
				glPopMatrix();

				std::cout << "+++++++++++    right   ++++++++++++ " << std::endl;
				
			}
			else {
				//rolling up
				glPushMatrix();

				//glTranslatef(cubeNew[a].getCoordX() - 1.5, cubeNew[a].getCoordY() - 0.5, 0.0);
				glTranslatef(cb.getCoordX() - 1.5, cb.getCoordY() - 0.5, 0.0);
				glRotatef(-angleRotation, cb.getDirectionX(), cb.getDirectionY(), cb.getDirectionZ());
				//glRotatef(-angleRotation, 1.0, 0.0, 0.0);
				glTranslatef(1.5, -0.5, 0.5); //const

				//draw cube
				glColor3f(0.5, 0.5, 1.0); glutSolidCube(1);
				glColor3f(1.5, 1.5, 1.5); glutWireCube(1);

				//draw 3D Coords -- - 19 / 9 / 2019

				glPopMatrix();
				std::cout << "------------     up     -----------" << std::endl;
				
				
			}
		}
		
	}
	if (angleRotation >= 90)
	{
		newCube[numberCube].setSelected(false); //cb will stop
		numberCube += 1;						//move to next cb

		numberCube %= cubeNum;
		newCube[numberCube].setSelected(true);
		angleRotation = 0;

	}
	// or can do: 
	//if (angleRotation >= 90)
	//{
	//	newCube[numberCube].setSelected(false); //cb will stop
	//	numberCube += 1;						//move to next cb
	//	//numberCube %= cubeNum;
	//	if (numberCube != cubeNum) {
	//		newCube[numberCube].setSelected(true);
	//		angleRotation = 0;
	//	}
	//	else {
	//		numberCube = 0;
	//		newCube[numberCube].setSelected(true);
	//		angleRotation = 0;
	//	}
	//}
	///getchar();
}

void DisplayAnimation(void) {
	DisplayInit();GLSettings0.SetEyePosition();
	GradientBackGround(BackTopColor, BackBotColor);

	if (ShowAxisFlag)
		ConclusiveAxis();

	if (ShowGrid) {
		DrawGrid();
		//DrawCubeGrid();
	}

	if (ShowStartPointFlag) {
		DrawCube(cube.startPoint, 05);
		//DrawSphere(cube.startPoint, 0.1);
		
	}

	Draw3DcoordArrow2(cube.startPoint.x, cube.startPoint.y, cube.startPoint.z, 0.03);

	
	if (ShowGoalPointFlag) {
		DrawCube(cube.goalPoint, 70);
		DrawSphere(cube.goalPoint, 0.1);
		//DrawArrow(cube.startPoint,cube.temp1, 2, 0.05);
	}

	if (ShowShortestLine)
		DrawStartEndPoint(cube.startPoint, cube.goalPoint);

	if (ShowCubeCenterFlag) {
		for (int i = 0; i < cube.cubeCenter.size() - 1; i++) {
			glColor3f(0.5, 1.0, 0.5);
			DrawSphere(cube.cubeCenter[i], 0.1);
			//Draw3DcoordArrow(cube.cubeCenter[i], 0.03);
		}
	}
	//rolling cube
	if (ShowAnimationFlag)
		DrawCubeRolling();

	//AntTweakBar//
	TwDraw();

	DisplayPostprocessor();
	
}

void OpenGLIdle_Cube(void) {
	angleRotation += 1;
	glutPostRedisplay();
}

void time_callback_Cube(int) {
	glutPostRedisplay();
	glutTimerFunc(10, time_callback_Cube, 0);

	angleRotation += 2;

	std::cout << "cuberotation in timeCallback(): " << angleRotation << std::endl;
}

void OpenGLCallBackAnimation(void) {
	GLSettings0.PickObject = PickObject0;
	OpenGLInitialize(0, GLSettings0, 300, 150, 1000, 650, "Path Planning");

	glutDisplayFunc(DisplayAnimation);

	TwCallBack();
	glutMouseFunc(MouseButton);
	glutMotionFunc(OnMouseMotion);
	glutPassiveMotionFunc(PassiveMotion);

	//glutIdleFunc(OpenGLIdle_Cube);
	//glutKeyboardFunc(SpecialKeyRolling);			//keyboard call
	glutSpecialFunc(SpecialKey);
	glutMouseWheelFunc(OpenGLMouseWheel0);
	glutReshapeFunc(OpenGLReshape0);
	glutTimerFunc(0, time_callback_Cube, 0); //the same with SpecialKeyRolling but faster 

	OpenGLPostprocessor(GLSettings0);
	
}






