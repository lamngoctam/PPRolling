#include "stdafx.h"

extern OctVoxel cube;

void findingCubeCenter() {

	//cube.cubeCenter.push_back(cube.startPoint);

	double dist1 = 0.0;
	double dist2 = 0.0;

	CVector3d nextRight, nextUp;
	CVector3d newMovePoint;

	CVector3d tempPoint;
	tempPoint.Set(cube.startPoint.x, cube.startPoint.y, cube.startPoint.z);

	CVector3d tempPointContact1, tempPointContact2;

	int count = 0;
	while (tempPoint != cube.goalPoint)
	{
		nextRight.Set(tempPoint.x + 1.0, tempPoint.y, tempPoint.z);
		double distanceRight = nextRight.PointLineDistance(cube.startPoint, cube.goalPoint);
		nextUp.Set(tempPoint.x, tempPoint.y + 1.0, tempPoint.z);
		double distanceUp = nextUp.PointLineDistance(cube.startPoint, cube.goalPoint);

		if (distanceRight > distanceUp) {
			//choose Up
			newMovePoint = nextUp;
			tempPoint = newMovePoint;

			tempPointContact1.Set(nextUp.x - 0.5, nextUp.y - 0.5, nextUp.z - 0.5);
			tempPointContact2.Set(nextUp.x + 0.5, nextUp.y - 0.5, nextUp.z - 0.5);
			
			cube.edgeContactUpLeft.push_back(tempPointContact1);
			cube.edgeContactUpRight.push_back(tempPointContact2);

			tempPointContact1.Set(0.0, 0.0, 0.0);
			tempPointContact2.Set(0.0, 0.0, 0.0);
		}
		else {
			//choose Right
			newMovePoint = nextRight;
			tempPoint = newMovePoint;

			tempPointContact1.Set(nextRight.x - 0.5, nextRight.y - 0.5, nextRight.z - 0.5);
			tempPointContact2.Set(nextRight.x - 0.5, nextRight.y + 0.5, nextRight.z - 0.5);

			cube.edgeContactRightLow.push_back(tempPointContact1);
			cube.edgeContactRightHigh.push_back(tempPointContact2);

			tempPointContact1.Set(0.0, 0.0, 0.0);
			tempPointContact2.Set(0.0, 0.0, 0.0);
		}

		//glMaterialfv(GL_FRONT, GL_SPECULAR, color);
		//DrawSphere(newMovePoint, 0.1);		

		cube.cubeCenter.push_back(newMovePoint);
		count++;
	}

	// cube.cubeCenter.push_back(cube.goalPoint);

	cube.cubeCenter.erase(cube.cubeCenter.end() - 1); //do not include the goalPoint


	cout << "size of Center" << cube.cubeCenter.size() << endl;
	cout << "size of RightLow" << cube.edgeContactRightLow.size() << endl;
	cout << "size of RightHigh" << cube.edgeContactRightHigh.size() << endl;
	cout << "size of UpLeft" << cube.edgeContactUpLeft.size() << endl;
	cout << "size of UpRight" << cube.edgeContactUpRight.size() << endl;
	
}

void cubeRotation(CVector3d axisRotation) {
	double Theta = (90 * M_PI / 180);

	//move forward

	//rotation   	  
	CVector3d W_(0.0, 0.0, 0.0);

	W_.Set(axisRotation.x, axisRotation.y, axisRotation.z);

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
	//--------------------------------------------------------------------

	cout << Rod1.At(0, 0) << "-" << Rod1.At(1, 0) << "-" << Rod1.At(2, 0) << endl;
	cout << Rod1.At(0, 1) << "-" << Rod1.At(1, 1) << "-" << Rod1.At(2, 1) << endl;
	cout << Rod1.At(0, 2) <<"-"<< Rod1.At(1, 2) << "-" << Rod1.At(2, 2) << endl;

	CVector3d temp_(0.0, 0.0, 0.0);
	temp_.x = Rod1.At(0, 0)*cube.startPoint.x + Rod1.At(0, 1)*cube.startPoint.y + Rod1.At(0, 2)*cube.startPoint.z;
	temp_.y = Rod1.At(1, 0)*cube.startPoint.x + Rod1.At(1, 1)*cube.startPoint.y + Rod1.At(1, 2)*cube.startPoint.z;
	temp_.z = Rod1.At(2, 0)*cube.startPoint.x + Rod1.At(2, 1)*cube.startPoint.y + Rod1.At(2, 2)*cube.startPoint.z;
	cube.newOrigin.Set(temp_.x, temp_.y, temp_.z);

	
	//move backward


	for (int i = 0; i < cube.cubeCenter.size(); i++) {
		//cube.cubeCenter[i].Print();

	}
	cube.origin.Print();
	cube.startPoint.Print();
	cube.newOrigin.Print();

	//getchar();
}