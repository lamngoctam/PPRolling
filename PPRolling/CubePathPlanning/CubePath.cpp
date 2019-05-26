#include "stdafx.h"

extern OctVoxel cube;
extern OctVoxel* label;
extern UnitCube *cubeNew;
extern OctVoxel *newCube;

void findingCubeCenter(int &cubeNum) {

	//cube.cubeCenter.push_back(cube.startPoint);

	double dist1 = 0.0;
	double dist2 = 0.0;

	CVector3d nextRight, nextUp;
	CVector3d newMovePoint;

	CVector3d tempPoint;
	tempPoint.Set(cube.startPoint.x, cube.startPoint.y, cube.startPoint.z);

	CVector3d tempPointContact1, tempPointContact2;

	int count = 0;
	//21/05
	int tempUpCount(0);
	int tempRightCount(0);

	//22/05
	int  tempLableCount = 0;
	int uppp = 0;
	int righttt = 1;

	while (tempPoint != cube.goalPoint)
	{
		nextRight.Set(tempPoint.x + 1.0, tempPoint.y, tempPoint.z);
		double distanceRight = nextRight.PointLineDistance(cube.startPoint, cube.goalPoint);
		nextUp.Set(tempPoint.x, tempPoint.y + 1.0, tempPoint.z);
		double distanceUp = nextUp.PointLineDistance(cube.startPoint, cube.goalPoint);

		if (distanceRight > distanceUp) { //choose Up
			tempPoint = nextUp;
			cube.cubeCenter.push_back(nextUp); // saving cubeCenter			

			cube.rotlabel.push_back(uppp);
		}			
		else { //choose Right
			tempPoint = nextRight;
			cube.cubeCenter.push_back(nextRight); // saving cubeCenter
			
			cube.rotlabel.push_back(righttt);
		}
		count++;
	}

	cout << "start" << endl;
	cubeNum = cube.cubeCenter.size();
	newCube = new OctVoxel[cubeNum];

	for (int i = 0; i < cube.cubeCenter.size(); i++) {
		newCube[i].coordX = cube.cubeCenter[i].x;
		newCube[i].coordY = cube.cubeCenter[i].y;
		newCube[i].coordZ = cube.cubeCenter[i].z;
		if (cube.rotlabel[i] == 1) { //right
			newCube[i].setRightRolling(true);
			newCube[i].directionX = 0.0;
			newCube[i].directionY = 1.0;
			newCube[i].directionZ = 0.0;

			cout << "right " << i << endl;
		}
		else {
			newCube[i].setRightRolling(false);
			newCube[i].directionX = 1.0;
			newCube[i].directionY = 0.0;
			newCube[i].directionZ = 0.0;

			cout << "up " << i << endl;

		}
	}

	cout << "endl" << endl;
	//getchar();

	// cube.cubeCenter.push_back(cube.goalPoint);
	//cube.cubeCenter.erase(cube.cubeCenter.end() - 1); //do not include the goalPoint
	//cube.rotRightCount.erase(cube.rotRightCount.end() - 1); //do not include rolling to the goalPoint

	//cubeNum = cube.cubeCenter.size();
	//cubeNew = new UnitCube[cubeNum];

	//
	//
	//int rightNum(0);
	//int UpNum(0);
	//for (int i = 0; i < cube.cubeCenter.size(); i++) {
	//	cubeNew[i].coordX = cube.cubeCenter[i].x;
	//	cubeNew[i].coordY = cube.cubeCenter[i].y;
	//	cubeNew[i].coordZ = cube.cubeCenter[i].z;

	//}
	//for (int i = 0; i < cube.cubeCenter.size(); i++) {
	//	if (cube.rotlabel[i] == 1) { //right
	//		cubeNew[i].setRightRolling(true);

	//		cubeNew[i].directionX = 0.0;
	//		cubeNew[i].directionY = 1.0;
	//		cubeNew[i].directionZ = 0.0;

	//		rightNum++;
	//	}
	//	else if (cube.rotlabel[i] == 0) {//up
	//		cubeNew[i].setRightRolling(false);

	//		cubeNew[i].directionX = 1.0;
	//		cubeNew[i].directionY = 0.0;
	//		cubeNew[i].directionZ = 0.0;

	//		UpNum++;
	//	}
	//}
	

	cout << "cubeNum " << cubeNum << "- cube.cubeCenter.size() " << cube.cubeCenter.size() << endl;
}

void cubeRotation(CVector3d axisRotation) {
	double Theta = (90 * M_PI / 180);

	//move forward

	//rotation   	  
	CVector3d W_(0.0, 0.0, 0.0);
	//W_.Set(axisRotation.x, axisRotation.y, axisRotation.z);
	W_.Set(0.0, 1.0, 0.0);

	CVector3d tempOldPoint(0.0, 0.0, 0.0);
	tempOldPoint.Set(-0.5, cube.goalPoint.y, cube.goalPoint.z);

	//cout << "tempOldPoint" << tempOldPoint.x << " " << tempOldPoint.y << "  " << tempOldPoint.z << endl;

	CMatrix Rod1(3, 3);
	Rod1.SetZero();

	Rod1.At(0, 0) = cos(Theta) + W_.x*W_.x*(1 - cos(Theta));
	Rod1.At(1, 0) = W_.z*sin(Theta) + W_.x*W_.y*(1 - cos(Theta));
	Rod1.At(2, 0) = -W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));

	Rod1.At(0, 1) = W_.x*W_.y*(1 - cos(Theta)) - W_.z*sin(Theta);
	Rod1.At(1, 1) = cos(Theta) + W_.y*W_.y*(1 - cos(Theta));
	Rod1.At(2, 1) = W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));

	Rod1.At(0, 2) = W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));
	Rod1.At(1, 2) = -W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));
	Rod1.At(2, 2) = cos(Theta) + W_.z*W_.z*(1 - cos(Theta));

	//Rod1.At(0, 0) = cos(Theta) + W_.x*W_.x*(1 - cos(Theta));
	//Rod1.At(1, 0) = -W_.z*sin(Theta) + W_.x*W_.y*(1 - cos(Theta));
	//Rod1.At(2, 0) = W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));
	//
	//Rod1.At(0, 1) = W_.x*W_.y*(1 - cos(Theta)) + W_.z*sin(Theta);
	//Rod1.At(1, 1) = cos(Theta) + W_.y*W_.y*(1 - cos(Theta));
	//Rod1.At(2, 1) = -W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));
	//
	//Rod1.At(0, 2) = -W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));
	//Rod1.At(1, 2) = W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));
	//Rod1.At(2, 2) = cos(Theta) + W_.z*W_.z*(1 - cos(Theta));
	//--------------------------------------------------------------------

	cout << Rod1.At(0, 0) << "-" << Rod1.At(1, 0) << "-" << Rod1.At(2, 0) << endl;
	cout << Rod1.At(0, 1) << "-" << Rod1.At(1, 1) << "-" << Rod1.At(2, 1) << endl;
	cout << Rod1.At(0, 2) << "-" << Rod1.At(1, 2) << "-" << Rod1.At(2, 2) << endl;

	CVector3d temp_(0.0, 0.0, 0.0);
	temp_.x = Rod1.At(0, 0)*tempOldPoint.x + Rod1.At(0, 1)*tempOldPoint.y + Rod1.At(0, 2)*tempOldPoint.z;
	temp_.y = Rod1.At(1, 0)*tempOldPoint.x + Rod1.At(1, 1)*tempOldPoint.y + Rod1.At(1, 2)*tempOldPoint.z;
	temp_.z = Rod1.At(2, 0)*tempOldPoint.x + Rod1.At(2, 1)*tempOldPoint.y + Rod1.At(2, 2)*tempOldPoint.z;


	cout << "temp" << temp_.x << " " << temp_.y << "  " << temp_.z << endl;
	cube.newOrigin.Set(temp_.x + temp_.x + 0.5, temp_.y, temp_.z);
	cout << endl;

	//move backward


	for (int i = 0; i < cube.cubeCenter.size(); i++) {
		cout << "point[" << i << "] ";cube.cubeCenter[i].Print();
		//cube.rotlabel.push_back(i);

		//if (cube.rotRightFlag == true) {
		//	cout << "RightFlag[" << i << "] " << endl;
		//}
		//else {
		//	cout << "UpFlag[" << i << "] " << endl;
		//}
		cout << endl;
	}
	//cout << "cube.origin";	cube.origin.Print(); cout << endl;
	//cout << "cube.startPoint";	cube.startPoint.Print(); cout << endl;
	//cout << "cube.goalPoint";	cube.goalPoint.Print();	 cout << endl;
	//cout << "cube.newOrigin";	cube.newOrigin.Print();	 cout << endl;
	//cout << "cube.rotUpCount" << cube.rotUpCount.size() << endl;
	//cout << "cube.rotRightCount" << cube.rotRightCount.size() << endl;

	cout << endl;

	//getchar();
}