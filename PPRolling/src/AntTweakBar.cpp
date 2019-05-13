//############################################################################
//Anttweakbar-widget
//	
//	http://www.antisphere.com/Wiki/tools:anttweakbar
//############################################################################
#include "../stdafx.h"
#include "OpenGL.h"
//extern
extern OpenGL GLSettings0;

//Flag?p link to OpenGLWindow0.cpp

int ShowAxisFlag = 1;			//Axis
int ShowBB = 1;                   // show Bounding Box

void TW_CALL SaveButton(void *clientData);

void TwCallBack(void) {
	//tweakbar
	TwBar *Mainbar;						// tweak bar
	TwInit(TW_OPENGL, NULL);			// AntTweakBar
	Mainbar = TwNewBar("MainTweakBar");

	//Mainbar@help size color position etc...
	TwDefine(" GLOBAL help='This example shows B-spline surface with GLUT and OpenGL.' ");
	TwDefine(" MainTweakBar size='200 200' color='0 0 139' ");

	// display  key control
	TwAddButton(Mainbar, "Info1.1", NULL, NULL, " label='INPUT DATA' ");
	TwAddVarRW(Mainbar, "ShowBoudingBoxFlag", TW_TYPE_BOOL32, &ShowBB, " label='BBox' key=b");
	//
	//__________________________________Axis___________________________________________________
	TwAddButton(Mainbar, "Info1.3", NULL, NULL, " label='Axis' ");
	TwAddVarRW(Mainbar, "ShowAxisFlag", TW_TYPE_BOOL32, &ShowAxisFlag, " label='Axis' key=z");

	   
	GLSettings0.CreateBar();	//opengl
}


/************************************************/
/*	Callback function			*/
/************************************************/
void TW_CALL SaveButton(void *clientData)
{
	//S.SaveAsOBJ("Window0.obj");
}
