#include "stdafx.h"

using namespace std;

extern OctVoxel cube;
extern OctVoxel* label;

//function
void DrawCube(CVector3d centerPoint, int colorID);
void findingCubeCenter();
void cubeRotation(CVector3d axisRotation);

//openGL
void RunOpenGL(int argc, char *argv[]);

//main function
int CubePathPlanning(int argc, char* argv[]) {
	   
	//initialize the Start and Goal point on grid
	cube.startPoint.Set(0.5, 0.5, 0.5);
	cube.goalPoint.Set(5.5, 3.5, 0.5);
	//cube.origin.Set(0.0, 0.0, 0.0);
	//
	findingCubeCenter();
	cout << cube.cubeCenter.size();

	cube.rotAxis.Set(0.0, 1.0, 0.0);
	cubeRotation(cube.rotAxis);
	//cout << "WTF" << endl;
	//getchar();
	RunOpenGL(argc, argv);

	return 0;
}


