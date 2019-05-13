//#########################################################
// Call OpenGLCallBack0(); function from OpenGLWindow.cpp
//#########################################################

#include "stdafx.h"
#include "OpenGL.h"
#include "OpenGLprimitive.h"

using namespace std;
extern OpenGL GLSettings0;


//#pragma warning(disable : 4996)//about scanf

int WinID[2]; //EID

//void OpenGLDisplay0(void);
void OpenGLCallBack0(void);

//void OpenGLDisplay1(void);
//void OpenGLCallBack1(void);

/***************************************************/
/*			OpenGL								   */
/***************************************************/
void DisplayInit() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ZERO);

	SetLight();

	glPushMatrix();
}


void DisplayPostprocessor() {
	glDepthMask(TRUE);
	glDisable(GL_BLEND);

	glPopMatrix();
	glutSwapBuffers();
}


/***************************************************/
/*			OpenGL								   */
/***************************************************/

void PickUpInit(int x, int y) {
	GLint viewport[4];
	double current_aspect;
	glGetIntegerv(GL_VIEWPORT, viewport);

	(void)glRenderMode(GL_SELECT);

	glInitNames();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();


	gluPickMatrix(x, viewport[3] - y, 25.0, 25.0, viewport);

	current_aspect = (double)viewport[2] / (double)viewport[3];

	gluPerspective(10.0, current_aspect, 0.01, -1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
}


void PickUpPostprocessor(void) {
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


int SelectHits(GLuint hits, GLuint* buf, int hit_name[2]) {
	hit_name[0] = -1;
	hit_name[1] = -1;

	double depth_min = 10.0;
	double depth_1 = 1.0;
	double depth_2 = 1.0;
	GLuint depth_name;
	GLuint *ptr;

	if (hits <= 0)
	{
		return -1;
	}

	ptr = buf;


	for (unsigned int i = 0; i < hits; ++i)
	{
		depth_name = *ptr;

		++ptr;
		depth_1 = *ptr / 0x7fffffff;

		++ptr;
		depth_2 = *ptr / 0x7fffffff;


		if (depth_min > depth_1)
		{
			depth_min = depth_1;


			for (unsigned int j = 0; j < depth_name; ++j)
			{
				++ptr;
				hit_name[j] = (int)(*ptr);
			}
		}
		else
		{
			for (unsigned int j = 0; j < depth_name; ++j)
			{
				++ptr;
			}
		}
		++ptr;
	}
	return hit_name[0];
}



double ReturnDepth(int x, int y) {
	double z;
	GLint viewport[4];

	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadPixels(x, viewport[3] - y, 1, 1,
		GL_DEPTH_COMPONENT,
		GL_FLOAT,
		&z);
	return z;
}

/***************************************************/
/*					                               */
/***************************************************/
void OpenGLIdle(void) {
	glutPostRedisplay();
}

/***************************************************/
/*			           OpenGL					   */
/***************************************************/
void OpenGLInitialize(int WindowID, OpenGL GLSettings, int InitPosiX, 
	int InitPosiY, int WindowWidth, int WindowHeight, const char* WindowName) {

	GLSettings.m_WindowHeight = WindowHeight;
	GLSettings.m_WindowWidth = WindowWidth;
	glutInitWindowPosition(InitPosiX, InitPosiY);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WindowWidth, WindowHeight);
	WinID[WindowID] = glutCreateWindow(WindowName);
}

/***************************************************/
/*			OpenGL								   */
/***************************************************/
void OpenGLPostprocessor(OpenGL GLSettings) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-GLSettings.m_WindowWidth, GLSettings.m_WindowWidth, -GLSettings.m_WindowHeight, GLSettings.m_WindowHeight);

	glMatrixMode(GL_MODELVIEW);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
}


/***************************************************/
/*			OpenGL								   */
/***************************************************/
void RunOpenGL(int argc, char *argv[]) {

	glutInit(&argc, argv);
	OpenGLCallBack0();

	glutMainLoop();					//from freeglut_std.h library
}