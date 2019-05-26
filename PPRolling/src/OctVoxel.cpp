#include "stdafx.h"

OctVoxel::OctVoxel() {
	this->countt = 0;
	this->count_x = 0;
	this->count_y = 0;
	this->angle = 90.0;
	this->length = 1.0;
	this->lableNum = 0;

	this->rotRightFlag = false;
	this->rotUpFlag = false;

	this->selected = false;;
	this->rightRolling = false;
	this->totalCube = 0;
}

void OctVoxel::SetRotationRight(bool num) {
	this->rotRightFlag = num;
}
	
void OctVoxel::SetRotationUp(bool num) {
	this->rotUpFlag = num;
}

bool OctVoxel::SetRotationRight(void) {
	return(this->rotRightFlag);
}
bool OctVoxel::SetRotationUp(void) {
	return(this->rotUpFlag);
}



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


double OctVoxel::getCoordX()
{
	return coordX;
}
double OctVoxel::getCoordY()
{
	return coordY;
}
double OctVoxel::getCoordZ()
{
	return coordZ;
}
double OctVoxel::getDirectionX()
{
	return directionX;
}
double OctVoxel::getDirectionY()
{
	return directionY;
}
double OctVoxel::getDirectionZ()
{
	return directionZ;
}
bool OctVoxel::getSelected() {
	return selected;
}
void OctVoxel::setSelected(bool what) {
	this->selected = what;
}
	
bool OctVoxel::getRightRolling() {
	return rightRolling;
}
void OctVoxel::setRightRolling(bool what) {
	this->rightRolling = what;
}