#include "stdafx.h"
UnitCube::UnitCube() {
	this->totalCube = 0;
}
UnitCube::UnitCube(double cX, double cY, double cZ, double dX, double dY, double dZ)
{
	coordX = cX;
	coordY = cY;
	coordZ = cZ;

	directionX = dX;
	directionY = dY;
	directionZ = dZ;

	selected = false;
}

double UnitCube::getCoordX()
{
	return coordX;
}
double UnitCube::getCoordY()
{
	return coordY;
}
double UnitCube::getCoordZ()
{
	return coordZ;
}
double UnitCube::getDirectionX()
{
	return directionX;
}
double UnitCube::getDirectionY()
{
	return directionY;
}
double UnitCube::getDirectionZ()
{
	return directionZ;
}
bool UnitCube::getSelected()
{
	return selected;
}
void UnitCube::setSelected(bool what)
{
	selected = what;
}