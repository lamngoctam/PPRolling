#include "stdafx.h"



extern OctVoxel cube;
extern OctVoxel* label;
extern OctVoxel *newCube;
extern int cubeNum;

//function
void DrawCube(CVector3d centerPoint, int colorID);
void findingCubeCenter_rightUp(int &cubeNum);
void findingCubeCenter_leftUp(int &cubeNum);
void cubeRotation(CVector3d axisRotation);

//openGL
void RunOpenGL(int argc, char *argv[]);

bool dirRolling = false;


//main function
int CubePathPlanning(int argc, char* argv[]) {

	//initialize the Start and Goal point on grid
	cube.startPoint.Set(0.5, 0.5, 0.5);
	cube.goalPoint.Set(5.5, 3.5, 0.5);
	double s_x = cube.startPoint.x;	double s_y = cube.startPoint.y;
	double g_x = cube.goalPoint.x;	double g_y = cube.goalPoint.y;

	if ((s_x < g_x) && (s_y <= g_y)) {
		dirRolling = true;
		findingCubeCenter_rightUp(cubeNum);
	}
	else {
		dirRolling = false;
		findingCubeCenter_leftUp(cubeNum);
	}
	   	  
	//newCube[0].setSelected(true);
	
	
	RunOpenGL(argc, argv);


	delete[] newCube;

	return 0;
}


