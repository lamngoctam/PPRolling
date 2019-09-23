#include "stdafx.h"

extern OctVoxel cube;
//extern OctVoxel *label;
extern OctVoxel *newCube;

//extern OctVoxel *newCoord;

void findingCubeCenter_rightUp(int &cubeNum) {

	//cube.cubeCenter.push_back(cube.startPoint);

	double dist1 = 0.0;
	double dist2 = 0.0;

	CVector3d nextRight, nextUp;
	CVector3d newMovePoint;

	CVector3d tempPoint;
	tempPoint.Set(cube.startPoint.x, cube.startPoint.y, cube.startPoint.z);

	CVector3d tempPointContact1, tempPointContact2;

	int count = 0;
	////21/05
	//int tempUpCount(0);
	//int tempRightCount(0);
	//
	//22/05
	//int  tempLableCount = 0;

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

			std::cout << "upppp" << std::endl;
		}
		else { //choose Right
			tempPoint = nextRight;
			cube.cubeCenter.push_back(nextRight); // saving cubeCenter

			cube.rotlabel.push_back(righttt);
			std::cout << "rigth" << std::endl;
		}
		count++;
	}

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

			std::cout << "right " << i << std::endl;
		}
		else {//up
			newCube[i].setRightRolling(false);

			newCube[i].directionX = 1.0;
			newCube[i].directionY = 0.0;
			newCube[i].directionZ = 0.0;

			std::cout << "up " << i << std::endl;

		}
		/*	cube.temp1[i].x = cube.cubeCenter[i].x;
			cube.temp1[i].y = cube.cubeCenter[i].y;
			cube.temp1[i].z = cube.cubeCenter[i].z;*/
			//


		std::cout << "- newCube[i].coordZ " << newCube[i].coordZ
			<< "- cube.cubeCenter[i].z " << cube.cubeCenter[i].z << std::endl;

	}

	std::cout << "cubeNum " << cubeNum << "- cube.cubeCenter.size()="
		<< cube.cubeCenter.size() << " -in findingCubeCenter" << std::endl;


	getchar();
}


void findingCubeCenter_leftUp(int &cubeNum) {

	//cube.cubeCenter.push_back(cube.startPoint);

	double dist1 = 0.0;
	double dist2 = 0.0;

	CVector3d nextLeft, nextUp;
	CVector3d newMovePoint;

	CVector3d tempPoint;
	tempPoint.Set(cube.startPoint.x, cube.startPoint.y, cube.startPoint.z);

	CVector3d tempPointContact1, tempPointContact2;

	//22/05
	int uppp = 0;
	int righttt = 1;

	while (tempPoint != cube.goalPoint)
	{
		nextLeft.Set(tempPoint.x - 1.0, tempPoint.y, tempPoint.z);
		double distanceLeft = nextLeft.PointLineDistance(cube.startPoint, cube.goalPoint);
		nextUp.Set(tempPoint.x, tempPoint.y + 1.0, tempPoint.z);
		double distanceUp = nextUp.PointLineDistance(cube.startPoint, cube.goalPoint);

		if (distanceLeft > distanceUp) { //choose Up
			tempPoint = nextUp;
			cube.cubeCenter.push_back(nextUp); // saving cubeCenter			

			cube.rotlabel.push_back(uppp);
		}
		else { //choose Right
			tempPoint = nextLeft;
			cube.cubeCenter.push_back(nextLeft); // saving cubeCenter

			cube.rotlabel.push_back(righttt);
		}
	}

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

			std::cout << "right " << i << std::endl;
		}
		else {
			newCube[i].setRightRolling(false);

			newCube[i].directionX = 1.0;
			newCube[i].directionY = 0.0;
			newCube[i].directionZ = 0.0;

			std::cout << "up " << i << std::endl;

		}
	}

}

void findingPathCube(int &cubeNum) {
	CVector3d currentPoint, upPoint, downPoint, rightPoint, leftPoint;



}

//using Rodriguess
void cubeRotation(CVector3d axisRotation) {
	double Theta = (90 * M_PI / 180);

	//move forward

	//rotation   	  
	CVector3d W_(0.0, 0.0, 0.0);
	//W_.Set(axisRotation.x, axisRotation.y, axisRotation.z);
	W_.Set(0.0, 1.0, 0.0);

	CVector3d tempOldPoint(0.0, 0.0, 0.0);
	tempOldPoint.Set(-0.5, cube.goalPoint.y, cube.goalPoint.z);

	//std::cout << "tempOldPoint" << tempOldPoint.x << " " << tempOldPoint.y << "  " << tempOldPoint.z << std::endl;

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

	std::cout << Rod1.At(0, 0) << "-" << Rod1.At(1, 0) << "-" << Rod1.At(2, 0) << std::endl;
	std::cout << Rod1.At(0, 1) << "-" << Rod1.At(1, 1) << "-" << Rod1.At(2, 1) << std::endl;
	std::cout << Rod1.At(0, 2) << "-" << Rod1.At(1, 2) << "-" << Rod1.At(2, 2) << std::endl;

	CVector3d temp_(0.0, 0.0, 0.0);
	temp_.x = Rod1.At(0, 0)*tempOldPoint.x + Rod1.At(0, 1)*tempOldPoint.y + Rod1.At(0, 2)*tempOldPoint.z;
	temp_.y = Rod1.At(1, 0)*tempOldPoint.x + Rod1.At(1, 1)*tempOldPoint.y + Rod1.At(1, 2)*tempOldPoint.z;
	temp_.z = Rod1.At(2, 0)*tempOldPoint.x + Rod1.At(2, 1)*tempOldPoint.y + Rod1.At(2, 2)*tempOldPoint.z;


	std::cout << "temp" << temp_.x << " " << temp_.y << "  " << temp_.z << std::endl;
	cube.newOrigin.Set(temp_.x + temp_.x + 0.5, temp_.y, temp_.z);
	std::cout << std::endl;

	//move backward


	for (int i = 0; i < cube.cubeCenter.size(); i++) {
		std::cout << "point[" << i << "] ";cube.cubeCenter[i].Print();
		//cube.rotlabel.push_back(i);

		//if (cube.rotRightFlag == true) {
		//	std::cout << "RightFlag[" << i << "] " << std::endl;
		//}
		//else {
		//	std::cout << "UpFlag[" << i << "] " << std::endl;
		//}
		std::cout << std::endl;
	}
	//std::cout << "cube.origin";	cube.origin.Print(); std::cout << std::endl;
	//std::cout << "cube.startPoint";	cube.startPoint.Print(); std::cout << std::endl;
	//std::cout << "cube.goalPoint";	cube.goalPoint.Print();	 std::cout << std::endl;
	//std::cout << "cube.newOrigin";	cube.newOrigin.Print();	 std::cout << std::endl;
	//std::cout << "cube.rotUpCount" << cube.rotUpCount.size() << std::endl;
	//std::cout << "cube.rotRightCount" << cube.rotRightCount.size() << std::endl;

	std::cout << std::endl;

	//getchar();
}


//-------------------  20/9/2019
//
//---------------------------------------------------

//using Rodriguess
void RodriguesFunction_rightRolling(CVector3d originPoint, CVector3d tempPoint, CVector3d &newPoint) {
	double Theta = (90 * M_PI / 180);

	//rotation   	  
	CVector3d W_(0.0, 1.0, 0.0);
	//W_.Set(axisRotation.x, axisRotation.y, axisRotation.z);
	//W_.Set(0.0, 1.0, 0.0);

	CVector3d tempOldPoint(0.0, 0.0, 0.0);
	tempOldPoint.Set(tempPoint.x - originPoint.x, tempPoint.y - originPoint.y, tempPoint.z - 0.5);
	//tempOldPoint.Set(tempPoint.x -.5, tempPoint.y -.5, tempPoint.z );

	std::cout << "originPoint (" << originPoint.x << "," << originPoint.y << "," << originPoint.z << ")" << std::endl;
	std::cout << "tempPoint (" << tempPoint.x << "," << tempPoint.y << "," << tempPoint.z << ")" << std::endl;
	std::cout << "tempOldPoint (" << tempOldPoint.x << "," << tempOldPoint.y << "," << tempOldPoint.z << ")" << std::endl;

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

	CVector3d temp_(0.0, 0.0, 0.0);
	temp_.x = Rod1.At(0, 0)*tempOldPoint.x + Rod1.At(0, 1)*tempOldPoint.y + Rod1.At(0, 2)*tempOldPoint.z;
	temp_.y = Rod1.At(1, 0)*tempOldPoint.x + Rod1.At(1, 1)*tempOldPoint.y + Rod1.At(1, 2)*tempOldPoint.z;
	temp_.z = Rod1.At(2, 0)*tempOldPoint.x + Rod1.At(2, 1)*tempOldPoint.y + Rod1.At(2, 2)*tempOldPoint.z;


	//std::cout << "temp" << temp_.x << " " << temp_.y << "  " << temp_.z << std::endl;

	newPoint.Set(temp_.x + originPoint.x + 1.0, temp_.y + originPoint.y, temp_.z + 0.5);
	// +1 is a distance from old-new coordinates after translating to (0,0,0) then rolling then translating back to old

	std::cout << "newPoint (" << newPoint.x << "," << newPoint.y << "," << newPoint.z << ")" << std::endl;


	////std::cout << std::endl;
	//
	////move backward
	//
	//
	//for (int i = 0; i < cube.cubeCenter.size(); i++) {
	//	std::cout << "point[" << i << "] ";cube.cubeCenter[i].Print();
	//	//cube.rotlabel.push_back(i);
	//
	//	//if (cube.rotRightFlag == true) {
	//	//	std::cout << "RightFlag[" << i << "] " << std::endl;
	//	//}
	//	//else {
	//	//	std::cout << "UpFlag[" << i << "] " << std::endl;
	//	//}
	//	std::cout << std::endl;
	//}
	////std::cout << "cube.origin";	cube.origin.Print(); std::cout << std::endl;
	////std::cout << "cube.startPoint";	cube.startPoint.Print(); std::cout << std::endl;
	////std::cout << "cube.goalPoint";	cube.goalPoint.Print();	 std::cout << std::endl;
	////std::cout << "cube.newOrigin";	cube.newOrigin.Print();	 std::cout << std::endl;
	////std::cout << "cube.rotUpCount" << cube.rotUpCount.size() << std::endl;
	////std::cout << "cube.rotRightCount" << cube.rotRightCount.size() << std::endl;
	//
	//std::cout << std::endl;

	//getchar();
}

//using Rodriguess
void RodriguesFunction_upRolling(CVector3d originPoint, CVector3d tempPoint, CVector3d &newPoint) {
	double Theta = (90 * M_PI / 180);

	//rotation   	  
	CVector3d W_(0.0, 0.0, 0.0);
	//W_.Set(axisRotation.x, axisRotation.y, axisRotation.z);
	W_.Set(-1.0, 0.0, 0.0);

	CVector3d tempOldPoint(0.0, 0.0, 0.0);
	tempOldPoint.Set(tempPoint.x - originPoint.x, tempPoint.y - originPoint.y, tempPoint.z - 0.5);

	//std::cout << "tempOldPoint" << tempOldPoint.x << " " << tempOldPoint.y << "  " << tempOldPoint.z << std::endl;

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

	//std::cout << Rod1.At(0, 0) << "-" << Rod1.At(1, 0) << "-" << Rod1.At(2, 0) << std::endl;
		//std::cout << Rod1.At(0, 1) << "-" << Rod1.At(1, 1) << "-" << Rod1.At(2, 1) << std::endl;
		//std::cout << Rod1.At(0, 2) << "-" << Rod1.At(1, 2) << "-" << Rod1.At(2, 2) << std::endl;

	CVector3d temp_(0.0, 0.0, 0.0);
	temp_.x = Rod1.At(0, 0)*tempOldPoint.x + Rod1.At(0, 1)*tempOldPoint.y + Rod1.At(0, 2)*tempOldPoint.z;
	temp_.y = Rod1.At(1, 0)*tempOldPoint.x + Rod1.At(1, 1)*tempOldPoint.y + Rod1.At(1, 2)*tempOldPoint.z;
	temp_.z = Rod1.At(2, 0)*tempOldPoint.x + Rod1.At(2, 1)*tempOldPoint.y + Rod1.At(2, 2)*tempOldPoint.z;


	//std::cout << "temp" << temp_.x << " " << temp_.y << "  " << temp_.z << std::endl;

	newPoint.Set(temp_.x + originPoint.x, temp_.y + originPoint.y + 1.0, temp_.z + 0.5);
	// +1 is a distance from old-new coordinates after translating to (0,0,0) then rolling then translating back to old

	////std::cout << std::endl;
	//
	////move backward
	//
	//
	//for (int i = 0; i < cube.cubeCenter.size(); i++) {
	//	std::cout << "point[" << i << "] ";cube.cubeCenter[i].Print();
	//	//cube.rotlabel.push_back(i);
	//
	//	//if (cube.rotRightFlag == true) {
	//	//	std::cout << "RightFlag[" << i << "] " << std::endl;
	//	//}
	//	//else {
	//	//	std::cout << "UpFlag[" << i << "] " << std::endl;
	//	//}
	//	std::cout << std::endl;
	//}
	////std::cout << "cube.origin";	cube.origin.Print(); std::cout << std::endl;
	////std::cout << "cube.startPoint";	cube.startPoint.Print(); std::cout << std::endl;
	////std::cout << "cube.goalPoint";	cube.goalPoint.Print();	 std::cout << std::endl;
	////std::cout << "cube.newOrigin";	cube.newOrigin.Print();	 std::cout << std::endl;
	////std::cout << "cube.rotUpCount" << cube.rotUpCount.size() << std::endl;
	////std::cout << "cube.rotRightCount" << cube.rotRightCount.size() << std::endl;
	//
	//std::cout << std::endl;

	//getchar();
}

void RotationCoordSystem(
	CVector3d origin, CVector3d OXpoint, CVector3d OYpoint, CVector3d OZpoint,
	bool rightRolling,
	CVector3d &neworigin, CVector3d &newOXpoint, CVector3d &newOYpoint, CVector3d &newOZpoint) {

	if (rightRolling == true) {
		RodriguesFunction_rightRolling(origin, origin, neworigin);
		RodriguesFunction_rightRolling(origin, OXpoint, newOXpoint);
		RodriguesFunction_rightRolling(origin, OYpoint, newOYpoint);
		RodriguesFunction_rightRolling(origin, OZpoint, newOZpoint);
	}
	else {
		RodriguesFunction_upRolling(origin, origin, neworigin);
		RodriguesFunction_upRolling(origin, OXpoint, newOXpoint);
		RodriguesFunction_upRolling(origin, OYpoint, newOYpoint);
		RodriguesFunction_upRolling(origin, OZpoint, newOZpoint);
	}

	neworigin.Print();
}


