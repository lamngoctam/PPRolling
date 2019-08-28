#pragma once

#ifndef _OCTREE_H_
#define _OCTREE_H_

class OctVoxel {
public:
	//for animation
	int countt;
	float count_x, count_y;
	double angle;
	CVector3d rotAxis;
	CVector3d newOrigin;

	int lableNum;
	std::vector<int> rotlabel;
	
	std::vector<int> rotUpCount;
	std::vector<int> rotRightCount;

	bool rotRightFlag;
	bool rotUpFlag;

	void SetRotationRight(bool);
	void SetRotationUp(bool);

	bool SetRotationRight(void);
	bool SetRotationUp(void);

	//26/05/2019
	//for newCube
	double coordX;
	double coordY;
	double coordZ;

	double directionX;
	double directionY;
	double directionZ;
	double getCoordX();
	double getCoordY();
	double getCoordZ();
	double getDirectionX();
	double getDirectionY();
	double getDirectionZ();

	bool selected;
	bool rightRolling;
	int totalCube;
	std::vector<CVector3d> cubeCoord; //not using
	bool getSelected();
	void setSelected(bool what);

	bool getRightRolling();
	void setRightRolling(bool what);

	//edges contact for cube
	std::vector<CVector3d> edgeContactRightLow;
	std::vector<CVector3d> edgeContactRightHigh;
	std::vector<CVector3d> edgeContactUpLeft;
	std::vector<CVector3d> edgeContactUpRight;

	//for voxel
	OctVoxel();
	CVector3d origin;
	double length;
	double height;

	void SetOrigin(CVector3d ori);
	void SetVertexWorld(CVector3d* vertW);

	std::vector<CVector3d> cubeCenter;
	std::vector<CVector3d> cubeOrigin;
	CVector3d startPoint, goalPoint;
	//
	
};

class Model {

public:
	std::vector<CVector3d> cubeCenter;


	Model();
	~Model();
};



#endif 