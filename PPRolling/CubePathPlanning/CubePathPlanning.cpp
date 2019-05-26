#include "stdafx.h"

using namespace std;

extern OctVoxel cube;
extern OctVoxel* label;
extern OctVoxel *newCube;
extern int cubeNum;

//function
void DrawCube(CVector3d centerPoint, int colorID);
void findingCubeCenter(int &cubeNum);
void cubeRotation(CVector3d axisRotation);

//openGL
void RunOpenGL(int argc, char *argv[]);




//main function
int CubePathPlanning(int argc, char* argv[]) {
	   
	//initialize the Start and Goal point on grid
	cube.startPoint.Set(0.5, 0.5, 0.5);
	cube.goalPoint.Set(6.5, 5.5, 0.5);
	
	findingCubeCenter(cubeNum);
	cout << "cubeNum " << cubeNum << "- cube.cubeCenter.size() " << cube.cubeCenter.size() << endl;

	newCube[0].setSelected(true);

	
	RunOpenGL(argc, argv);

	delete[] newCube;

	return 0;
}


