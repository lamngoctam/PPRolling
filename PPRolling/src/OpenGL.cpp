//############################################################################
// OpenGl with tracking, moving mouse and eye position
//############################################################################
#include "stdafx.h"
//#include "OpenGL.h"


using namespace std;

////[AntTweakBar]///
extern float BackTopColor[3];
extern float BackBotColor[3];

//OpenGLMouse)
//MouseFunction
void OpenGL::Tracking(int Button, int State, int x, int y) {
	//
	if (State == GLUT_DOWN)
	{
		m_State = GLUT_DOWN;	//
		m_Button = Button;		//
		m_mouseLastX = x;		//
		m_mouseLastY = y;		//

		//?
		if (Button == GLUT_LEFT_BUTTON)
		{
			//
			(*PickObject)(x, y, Button);	//
		}
	}
	//
	else if (State == GLUT_UP)
	{
		m_State = GLUT_UP;		//
		m_Button = NONE;		//
	}
	glutPostRedisplay();
}


//(OpenGLMotion)
void OpenGL::MovingMouse(int x, int y) {
	m_mouseCurrentX = x;	//
	m_mouseCurrentY = y;	//

	//?
	if (m_State == GLUT_DOWN && m_Button == GLUT_LEFT_BUTTON)
	{
		double dx = (x - m_mouseLastX)*0.0003*m_EyeDis;
		double dy = (m_mouseLastY - y)*0.0003*m_EyeDis;	//
		*ObjectPosition = *ObjectPosition + dx * m_Right + dy * m_Upper;
	}

	//
	if (m_State == GLUT_DOWN && m_Button == GLUT_MIDDLE_BUTTON)
	{
		double dx = -(x - m_mouseLastX)*0.0003*m_EyeDis;
		double dy = -(m_mouseLastY - y)*0.0003*m_EyeDis;	//
		m_Eye = m_Eye + dx * m_Right + dy * m_Upper;
		m_Center = m_Center + dx * m_Right + dy * m_Upper;

		glutPostRedisplay();
	}

	//
	if (m_State == GLUT_DOWN && m_Button == GLUT_RIGHT_BUTTON)
	{
		double dt = -(x - m_mouseLastX)*0.01;	//
		double dp = -(m_mouseLastY - y)*0.01;	//
		m_Right = cos(dt)*m_Right + sin(dt)*m_Front;
		m_Upper = cos(dp)*m_Upper + sin(dp)*m_Front;
		m_Front = m_Upper.Cross(m_Right);
		m_Front = m_Front.Normalize();
		glutPostRedisplay();
	}

	m_mouseLastX = x;
	m_mouseLastY = y;
}

//
void OpenGL::DoMouseWheel(int direction) {
	m_EyeDis -= (double)direction*0.2*m_EyeDis;
	glutPostRedisplay();
}

//
void OpenGL::SetEyePosition() {
	SetEyes();

	gluLookAt(m_Eye.x, m_Eye.y, m_Eye.z,
		m_Center.x, m_Center.y, m_Center.z,
		m_Upper.x, m_Upper.y, m_Upper.z);
}

////[AntTweakBar]////
void OpenGL::CreateBar() {
	PropertyBar = TwNewBar("Property");	//

	//PropertyBar‚help size color position etc...
	TwDefine(" Property label='Property TweakBar' position='16 580' help='Use this bar to edit the lights and view port in the scene.' ");
	TwDefine(" Property size='200 180' color='139 139 139' ");

	//
	TwAddVarRW(PropertyBar, "Zoom", TW_TYPE_DOUBLE, &m_EyeDis,
		" min=0 max=50 step=0.1 keyIncr=z keyDecr=Z help='Scale the object (1=original size).' ");

	//
	TwAddVarRW(PropertyBar, "color0", TW_TYPE_COLOR3F, &BackTopColor,
		" group='Back ground color' label='Top color' help='Color of the first cube.' ");
	TwAddVarRW(PropertyBar, "color1", TW_TYPE_COLOR3F, &BackBotColor,
		" group='Back ground color' label='Bottom color' help='Color of the last cube. Cube colors are interpolated between the Start and End colors.' ");

}
