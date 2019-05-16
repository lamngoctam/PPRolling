#include "stdafx.h"

using namespace std;

extern OctVoxel cube;

//function
void DrawCube_centerPoint(CVector3d centerPoint, int colorID);
void findingCubeCenter();

void cubeRotation();

//openGL
void RunOpenGL(int argc, char *argv[]);

//main function
int CubePathPlanning(int argc, char* argv[]) {
	   
	//initialize the Start and Goal point on grid
	cube.startPoint.Set(0.5, 0.5, 0.5);
	cube.goalPoint.Set(19.5, 0.5, 0.5);
	   
	findingCubeCenter();


	cout << cube.cubeCenter.size();

	//getchar();
	RunOpenGL(argc, argv);

	return 0;
}


