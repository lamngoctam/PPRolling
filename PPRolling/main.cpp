#include "stdafx.h"

using namespace std;

OctVoxel cube;
void RunOpenGL(int argc, char *argv[]);

int main(int argc, char *argv[]) {

	cube.startPoint.Set(0.5, 0.5, 0.5);
	cube.goalPoint.Set(14.5, 13.5, 0.5);
	
	RunOpenGL(argc, argv);

	return 0;
}
