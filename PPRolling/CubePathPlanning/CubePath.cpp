#include "stdafx.h"

extern OctVoxel cube;

void findingCubeCenter() {

	//cube.cubeCenter.push_back(cube.startPoint);

	double dist1 = 0.0;
	double dist2 = 0.0;

	CVector3d nextPoint1, nextPoint2;
	CVector3d newMovePoint;

	CVector3d tempPoint;
	tempPoint.Set(cube.startPoint.x, cube.startPoint.y, cube.startPoint.z);

	int count = 0;
	while (tempPoint != cube.goalPoint)
	{
		nextPoint1.Set(tempPoint.x + 1.0, tempPoint.y, tempPoint.z);
		double distance1 = nextPoint1.PointLineDistance(cube.startPoint, cube.goalPoint);
		nextPoint2.Set(tempPoint.x, tempPoint.y + 1.0, tempPoint.z);
		double distance2 = nextPoint2.PointLineDistance(cube.startPoint, cube.goalPoint);

		if (distance1 > distance2) {
			newMovePoint = nextPoint2;
		}
		else {
			newMovePoint = nextPoint1;
		}

		//glMaterialfv(GL_FRONT, GL_SPECULAR, color);
		//DrawSphere(newMovePoint, 0.1);

		tempPoint = newMovePoint;

		cube.cubeCenter.push_back(newMovePoint);
		count++;
	}

	// cube.cubeCenter.push_back(cube.goalPoint);

	cube.cubeCenter.erase(cube.cubeCenter.end()-1);
}

void cubeRotation() {
	for (int i = 0; i < cube.cubeCenter.size(); i++) {
		//cube.cubeCenter[i].Print();

	}

}