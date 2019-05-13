#include "stdafx.h"


void OctVoxel::SetOrigin(CVector3d ori) {
	this->origin = ori;
}

void OctVoxel::SetVertexWorld(CVector3d* vertW)
//
{
	//8 vertices world coordinates of the voxel (x,y,z)
	CVector3d x(length, 0.0, 0.0);
	CVector3d y(0.0, length, 0.0);
	CVector3d z(0.0, 0.0, height);

	vertW[0] = this->origin;
	vertW[1] = this->origin + x;
	vertW[2] = this->origin + x + y;
	vertW[3] = this->origin + y;
	vertW[4] = this->origin + z;
	vertW[5] = this->origin + z + x;
	vertW[6] = this->origin + z + x + y;
	vertW[7] = this->origin + z + y;

}