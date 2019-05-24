#pragma once

#ifndef _OCTREE_H_
#define _OCTREE_H_


#include "stdafx.h"
#include "Color3D.h"


class OctVoxel {
public:
	//for animation
	int countt;
	float count_x, count_y;
	double angle;
	CVector3d rotAxis;
	CVector3d newOrigin;

	int lableNum;
	vector<int> rotlabel;
	
	vector<int> rotUpCount;
	vector<int> rotRightCount;

	bool rotRightFlag;
	bool rotUpFlag;

	void SetRotationRight(bool);
	void SetRotationUp(bool);

	bool SetRotationRight(void);
	bool SetRotationUp(void);


	//edges contact for cube
	vector<CVector3d> edgeContactRightLow;
	vector<CVector3d> edgeContactRightHigh;
	vector<CVector3d> edgeContactUpLeft;
	vector<CVector3d> edgeContactUpRight;

	//for voxel
	OctVoxel();
	CVector3d origin;
	double length;
	double height;

	void SetOrigin(CVector3d ori);
	void SetVertexWorld(CVector3d* vertW);

	vector<CVector3d> cubeCenter;
	vector<CVector3d> cubeOrigin;
	CVector3d startPoint, goalPoint;



	//
	
};

class Model {

public:
	vector<CVector3d> cubeCenter;


	Model();
	~Model();
};


class UnitCube
{
private:
	
	double coordX;
	double coordY;
	double coordZ;

	double directionX;
	double directionY;
	double directionZ;
	bool selected;

public:
	int totalCube;
	UnitCube(double cX, double cY, double cZ, double dX, double dY, double dZ);
	UnitCube();

	double getCoordX();
	double getCoordY();
	double getCoordZ();
	double getDirectionX();
	double getDirectionY();
	double getDirectionZ();
	bool getSelected();
	void setSelected(bool what);


};

#endif 