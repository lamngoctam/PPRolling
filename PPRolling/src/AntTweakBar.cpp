//############################################################################
//Anttweakbar-widget
//	
//	http://www.antisphere.com/Wiki/tools:anttweakbar
//############################################################################
#include "../stdafx.h"


extern OpenGL GLSettings0;

//Flag?p link to OpenGLWindow0.cpp

int ShowAxisFlag = 1;			//Axis
int ShowBB = 1;                   // show Bounding Box
int ShowGrid = 1;
int ShowStartPointFlag = 1;
int ShowGoalPointFlag = 1;
int ShowShortestLine = 1;
int ShowCubeCenterFlag = 1;
int ShowAnimationFlag = 1;


void TW_CALL SaveButton(void *clientData);

void TwCallBack(void) {
	//tweakbar
	TwBar *Mainbar;						// tweak bar
	TwInit(TW_OPENGL, NULL);			// AntTweakBar
	Mainbar = TwNewBar("Rolling_Path_Control_Bar");

	//Mainbar@help size color position etc...
	TwDefine(" GLOBAL help='This example shows Cube Rolling with GLUT and OpenGL.' ");
	TwDefine(" MainTweakBar size='200 200' color='0 0 139' ");

	//// display  key control BoundingBox
	//TwAddButton(Mainbar, "Info1.1", NULL, NULL, " label='INPUT DATA' ");
	//TwAddVarRW(Mainbar, "ShowBoudingBoxFlag", TW_TYPE_BOOL32, &ShowBB, " label='BBox' key=b");
	//
	//__________________________________Axis___________________________________________________
	TwAddButton(Mainbar, "Info1.2", NULL, NULL, " label='Axis' ");
	TwAddVarRW(Mainbar, "ShowAxisFlag", TW_TYPE_BOOL32, &ShowAxisFlag, " label='OXYZ_axis' key=a");
	//
	//__________________________________ShowGrid_______________________________________________
	TwAddButton(Mainbar, "Info1.3", NULL, NULL, " label='Grid' ");
	TwAddVarRW(Mainbar, "ShowGrid", TW_TYPE_BOOL32, &ShowGrid, " label='Discretized Suface' key=g");//
	//
	//__________________________________ShowSEPointFlag________________________________________
	TwAddButton(Mainbar, "Info1.4", NULL, NULL, " label='Initial Cube' ");
	TwAddVarRW(Mainbar, "ShowStartPointFlag", TW_TYPE_BOOL32, &ShowStartPointFlag, " label='Start Point' key=s");//
	TwAddVarRW(Mainbar, "ShowGoalPointFlag", TW_TYPE_BOOL32, &ShowGoalPointFlag, " label='Goal Point' key=g");//
	//
	//__________________________________ShowShortestLine_____________________________________
	TwAddButton(Mainbar, "Info1.5", NULL, NULL, " label='Path' ");
	TwAddVarRW(Mainbar, "ShowShortestLine", TW_TYPE_BOOL32, &ShowShortestLine, " label='Shortest Path' key=l");//
	//
	//__________________________________ShowCubeCenterFlag_____________________________________
	TwAddButton(Mainbar, "Info1.6", NULL, NULL, " label='Points' ");
	TwAddVarRW(Mainbar, "ShowCubeCenterFlag", TW_TYPE_BOOL32, &ShowCubeCenterFlag, " label='Object Centers' key=c");//
	//
	//__________________________________ShowAnimationFlag______________________________________
	TwAddButton(Mainbar, "Info1.7", NULL, NULL, " label='Animation' ");
	TwAddVarRW(Mainbar, "ShowAnimationFlag", TW_TYPE_BOOL32, &ShowAnimationFlag, " label='Cube Rolling' key=r");

	   
	GLSettings0.CreateBar();	//opengl
}


/************************************************/
/*	Callback function			*/
/************************************************/
void TW_CALL SaveButton(void *clientData)
{
	//S.SaveAsOBJ("Window0.obj");
}
