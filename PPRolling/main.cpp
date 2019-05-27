#include "func.h"


int main(int argc, char *argv[]) {
	cout << "Hello World" << endl;

	//for cube
	CubePathPlanning(argc, argv);

	//cout << "end of cube path planning" << endl;
	//for triangle
	TetrahedronPathPlanning(argc, argv);
	cout << "end of Tetrahedron Path Planning" << endl;
//
	
	return 0;
}

