
//############################################################################

#include "../stdafx.h"
#include "OpenGL.h"
#include "OpenGLprimitive.h"
//#include "OpenGLWindow0.h"

using namespace std;

extern int WinID[2];
OpenGL GLSettings1;


void DisplayInit();
void DisplayPostprocessor();
void OpenGLIdle();
void OpenGLReshape1(int width, int height);
void OpenGLInitialize(int WindowID, OpenGL GLSettings, int InitPosiX, int InitPosiY, int WindowWidth, int WindowHeight, char* WindowName);
void OpenGLPostprocessor(OpenGL GLSettings);
void PickUpInit(int x, int y);
void PickUpPostprocessor(void);
int SelectHits(GLuint hits, GLuint* buf, int hit_name[2]);
double ReturnDepth(int x, int y);

//
void ConclusiveAxis(void);
void GradientBackGround(float *tcolor, float *bcolor);

float BackTopColor1[] = { 0.941f, 1.0f, 1.0f };
float BackBotColor1[] = { 0.275f, 0.51f, 0.706f };

void OpenGLDisplay1(void) {
	DisplayInit();	
	GLSettings1.SetEyePosition();

	GradientBackGround(BackTopColor1, BackBotColor1);		//from OpenGLDraw.cpp
	ConclusiveAxis();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1, 1, 1); glVertex3f(0, 2, 0);
	glColor3f(1, 0, 0); glVertex3f(-1, 0, 1);
	glColor3f(0, 1, 0); glVertex3f(1, 0, 1);
	glColor3f(0, 0, 1); glVertex3f(0, 0, -1.4);
	glColor3f(1, 1, 1); glVertex3f(0, 2, 0);
	glColor3f(1, 0, 0); glVertex3f(-1, 0, 1);
	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
	glColor3f(0, 1, 0); glVertex3f(0.6, -0.75, 0);
	glColor3f(0, 0, 1); glVertex3f(0, 0.75, 0);
	glEnd();
	//-----------------------------------------------------//
	   	  
	DisplayPostprocessor();
}


/***************************************************/

void OpenGLKeyboard1(unsigned char Key, int x, int y) {

	switch (Key) {
	case '\x1b':	//Esc
		std::cout << "Exit OpenGL System" << std::endl;
		glutLeaveMainLoop();
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

		//case '+':	//À•WŽ²
		//	SpinImageNum = SpinImageNum+1;
		//	break;
		//
		//case '-':	//À•WŽ²
		//	if(SpinImageNum > 0)
		//		SpinImageNum = (SpinImageNum-1);
		//	break;	

	case '+':	//À•WŽ²2
		break;

	case '-':	//À•WŽ²
	
		break;

	case '2':	//ƒ¿‚ÆƒÀ‚Ì‚Q|‚cpoints‰æ‘œ
	;
		break;

	case '3':	//spint image
		
		break;
	case '4':	//spint image
		break;
	case 'm':
		break;
	case 'n':
		break;
	case 'v':
		break;
	case 'b':
		break;
	case 'p':
		break;

	case 'x':
		break;
	case 'u':
		break;

	case 'd':
		break;

	case '1':	
		GLSettings1.m_EyeDis = 20;
		GLSettings1.m_Center.Clear();
		GLSettings1.m_Front.Set(0.0, 0.0, -1.0);
		GLSettings1.m_Upper.Set(0.0, 1.0, 0.0);
		break;

	case '@':	
		break;
	}

	glutPostRedisplay();
}


/***************************************************/
/***************************************************/
void OpenGLSpecial1(int Key, int x, int y) {
	switch (Key) {

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

/***************************************************/
/***************************************************/
int PickUp1(int x, int y, int hit_name[2], int Button) {
	GLint hits;
	GLuint selectBuf[BUFSIZE];
	glSelectBuffer(BUFSIZE, selectBuf);

	PickUpInit(x, y);
	GLSettings1.SetEyePosition();

	PickUpPostprocessor();

	hits = glRenderMode(GL_RENDER);

	return SelectHits(hits, selectBuf, hit_name);
}

/***************************************************/

void PickObject1(int x, int y, int Button) {
	int hit_name[2];

	if (PickUp1(x, y, hit_name, Button) == -1) {
		GLSettings1.ObjectPosition = new CVector3d;
		return;
	}
	GLSettings1.m_ObjectDepth = ReturnDepth(x, y);

	if (GLSettings1.m_ObjectDepth > -1.0 && GLSettings1.m_ObjectDepth < 1.0) {

	}
}

/***************************************************/
void OpenGLMouse1(int Button, int State, int x, int y) {
	GLSettings1.Tracking(Button, State, x, y);
}
/***************************************************/
void OpenGLMotion1(int x, int y) {
	GLSettings1.MovingMouse(x, y);
}

/***************************************************/
void OpenGLMouseWheel1(int wheel_number, int direction, int x, int y) {
	GLSettings1.DoMouseWheel(direction);
};

/***************************************************/
void OpenGLReshape1(int width, int height) {
	GLSettings1.m_Aspect = static_cast<double>(width) / static_cast<double>(height);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(10.0, GLSettings1.m_Aspect, 0.01, -1.0);
	glMatrixMode(GL_MODELVIEW);
}



/***************************************************/

void OpenGLCallBack1(void) {
	GLSettings1.PickObject = PickObject1;
	OpenGLInitialize(1, GLSettings1, 0, 0, 600, 600, "Window1");
	glutDisplayFunc(OpenGLDisplay1);
	glutReshapeFunc(OpenGLReshape1);
	glutMouseFunc(OpenGLMouse1);
	glutMotionFunc(OpenGLMotion1);
	glutMouseWheelFunc(OpenGLMouseWheel1);
	glutKeyboardFunc(OpenGLKeyboard1);
	glutSpecialFunc(OpenGLSpecial1);
	glutIdleFunc(OpenGLIdle);
	OpenGLPostprocessor(GLSettings1);
}