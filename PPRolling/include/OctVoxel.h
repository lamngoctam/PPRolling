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

};

class Model {

public:
	vector<CVector3d> cubeCenter;


	Model();
	~Model();
};

#endif 