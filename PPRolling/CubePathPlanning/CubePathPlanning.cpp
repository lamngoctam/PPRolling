#include "stdafx.h"

using namespace std;

extern OctVoxel cube;
extern OctVoxel* label;

//function
void DrawCube(CVector3d centerPoint, int colorID);
void findingCubeCenter(int &cubeNum);
void cubeRotation(CVector3d axisRotation);

//openGL
void RunOpenGL(int argc, char *argv[]);

UnitCube *cubeNew;
int cubeNum(0);


//main function
int CubePathPlanning(int argc, char* argv[]) {
	   
	//initialize the Start and Goal point on grid
	cube.startPoint.Set(0.5, 0.5, 0.5);
	cube.goalPoint.Set(5.5, 3.5, 0.5);
	
	findingCubeCenter(cubeNum);
	cout << "cubeNum " << cubeNum << "- cube.cubeCenter.size() " << cube.cubeCenter.size() << endl;

	cubeNew[0].setSelected(true);


	RunOpenGL(argc, argv);

	return 0;
}


