#pragma once

#ifndef _OCTREE_H_
#define _OCTREE_H_


#include "stdafx.h"
#include "Color3D.h"


class OctVoxel {
public:

	CVector3d origin;
	double length;
	double height;

	void SetOrigin(CVector3d ori);
	void SetVertexWorld(CVector3d* vertW);

};

#endif 