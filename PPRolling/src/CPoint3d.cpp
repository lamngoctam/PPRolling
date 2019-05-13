#include "..\include\CPoint3d.h"


#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include <algorithm>
#include "CPoint3d.h"
using namespace std;


//##########################################//
CPoint3d::CPoint3d()
{
	x = y = z = 0.0;
	w = 1.0;
}


CPoint3d::CPoint3d(double X, double Y, double Z, double W)
{
	x = X;	y = Y;	z = Z;	w = W;
}


CPoint3d::~CPoint3d() {}

/****** ********/


void CPoint3d::Set(double X, double Y, double Z, double W)
{
	x = X;	y = Y;	z = Z;	w = W;
}


void CPoint3d::UnitVector(double X, double Y, double Z)
{
	double norm = sqrt(X*X + Y * Y + Z * Z);
	x = X / norm;	y = Y / norm;	z = Z / norm;
}


void CPoint3d::Clear()
{
	x = 0.0;	y = 0.0;	z = 0.0;	w = 1.0;
}


void CPoint3d::Print()
{
	std::cout << "(" << x << "," << y << "," << z << "," << w << ")" << std::endl;
}
// y10
CPoint3d& CPoint3d::operator=(const CPoint3d& obj)
{
	x = obj.x;	y = obj.y;	z = obj.z;
	return *this;
}


CPoint3d CPoint3d::operator+(const CPoint3d& obj)
{
	CPoint3d tmp;
	tmp.x = x + obj.x;	tmp.y = y + obj.y;	tmp.z = z + obj.z;
	return (tmp);
}


CPoint3d& CPoint3d::operator+=(const CPoint3d& obj)
{
	x += obj.x;	y += obj.y;	z += obj.z;
	return *this;
}

CPoint3d CPoint3d::operator-(const CPoint3d& obj)
{
	CPoint3d tmp;
	tmp.x = x - obj.x;	tmp.y = y - obj.y;	tmp.z = z - obj.z;
	return (tmp);
}


CPoint3d& CPoint3d::operator-=(const CPoint3d& obj)
{
	x -= obj.x;	y -= obj.y;	z -= obj.z;
	return *this;
}


CPoint3d  CPoint3d::operator-()
{
	CPoint3d tmp;
	tmp.x = -x; tmp.y = -y; tmp.z = -z;
	return(tmp);
}


CPoint3d CPoint3d::operator*(const double a)
{
	CPoint3d tmp;
	tmp.x = a * x;	tmp.y = a * y;	tmp.z = a * z;
	return (tmp);
}

CPoint3d operator*(const double a, const CPoint3d& obj)
{
	CPoint3d tmp;
	tmp.x = a * obj.x;	tmp.y = a * obj.y;	tmp.z = a * obj.z;
	return (tmp);
}


CPoint3d::operator CVector3d()
{
	return CVector3d(x, y, z);
}

/***************************/

CPoint3d CPoint3d::Mid(CPoint3d a)
{
	CPoint3d tmp;
	tmp.x = (x + a.x) / 2.0;
	tmp.y = (y + a.y) / 2.0;
	tmp.z = (z + a.z) / 2.0;
	return (tmp);
}

CPoint3d CPoint3d::Normalize()
{
	double norm = Norm();
	CPoint3d tmp;
	if (norm != 0) {
		tmp.x = x / norm;	tmp.y = y / norm;	tmp.z = z / norm;
	}
	return (tmp);
}

void CPoint3d::Normalize(CPoint3d a)
{
	double norm = a.Norm();
	if (norm != 0) {
		x = a.x / norm;	y = a.y / norm;	z = a.z / norm;
	}
}

double CPoint3d::Norm()
{
	return (sqrt(x*x + y * y + z * z));
}

double CPoint3d::Distance(CPoint3d a)
{
	double X = x - a.x;
	double Y = y - a.y;
	double Z = z - a.z;
	return (sqrt(X*X + Y * Y + Z * Z));
}


double CPoint3d::Dot(CPoint3d a)
{
	double dot = x * a.x;
	dot += y * a.y;
	dot += z * a.z;
	return (dot);
}

CPoint3d CPoint3d::Cross(CPoint3d a)
{
	CPoint3d tmp;
	tmp.x = y * a.z - z * a.y;
	tmp.y = z * a.x - x * a.z;
	tmp.z = x * a.y - y * a.x;
	return (tmp);
}



double CPoint3d::Angle(CPoint3d a)
{
	double deg, den;
	den = Norm()*a.Norm();
	if (den < 1.0e-15) {
		std::cout << "error" << std::endl;
		return 0;
	}
	deg = Dot(a) / den;
	if (deg > 1.0)	deg = 1.0;
	if (deg < -1.0)	deg = -1.0;

	deg = acos(deg);
	deg = 180.0*(deg / M_PI);

	return deg;
}

double CPoint3d::PointLineDistance(CPoint3d P0, CPoint3d P1)
{
	CPoint3d A = P1 - P0;
	CPoint3d B(x - P0.x, y - P0.y, z - P0.z);
	return ((A.Cross(B)).Norm() / P0.Distance(P1));
}

CPoint3d CPoint3d::Max(CPoint3d a)
{
	CPoint3d tmp;
	tmp.x = max(x, a.x);
	tmp.y = max(y, a.y);
	tmp.z = max(z, a.z);
	return (tmp);
}

CPoint3d CPoint3d::Min(CPoint3d a)
{
	CPoint3d tmp;
	tmp.x = min(x, a.x);
	tmp.y = min(y, a.y);
	tmp.z = min(z, a.z);
	return (tmp);
}

CPoint3d CPoint3d::RotateX(double rad)
{
	CPoint3d tmp;
	tmp.x = x;
	tmp.y = (y*cos(rad)) - (z*sin(rad));
	tmp.z = (y*sin(rad)) + (z*cos(rad));
	return (tmp);
}

CPoint3d CPoint3d::RotateY(double rad)
{
	CPoint3d tmp;
	tmp.x = (z*sin(rad)) + (x*cos(rad));
	tmp.y = y;
	tmp.z = (z*cos(rad)) - (x*sin(rad));
	return (tmp);
}

CPoint3d CPoint3d::RotateZ(double rad)
{
	CPoint3d tmp;
	tmp.x = (x*cos(rad)) - (y*sin(rad));
	tmp.y = (x*sin(rad)) + (y*cos(rad));
	tmp.z = z;
	return (tmp);
}


//######################################//
//######################################//

CVector3d::CVector3d()
{
	x = y = z = 0.0;
}

CVector3d::CVector3d(double X, double Y, double Z)
{
	x = X;	y = Y;	z = Z;
}

CVector3d::~CVector3d() {}


void CVector3d::Set(double X, double Y, double Z)
{
	x = X;	y = Y;	z = Z;
}

void CVector3d::UnitVector(double X, double Y, double Z)
{
	double norm = sqrt(X*X + Y * Y + Z * Z);
	x = X / norm;	y = Y / norm;	z = Z / norm;
}

void CVector3d::Clear()
{
	x = 0.0;	y = 0.0;	z = 0.0;
}

void CVector3d::Print()
{
	std::cout << "(" << x << "," << y << "," << z << ")" << std::endl;
}


CVector3d& CVector3d::operator=(const CVector3d& obj)
{
	x = obj.x;	y = obj.y;	z = obj.z;
	return *this;
}

CVector3d CVector3d::operator+(const CVector3d& obj)
{
	CVector3d tmp;
	tmp.x = x + obj.x;	tmp.y = y + obj.y;	tmp.z = z + obj.z;
	return (tmp);
}

CVector3d& CVector3d::operator+=(const CVector3d& obj)
{
	x += obj.x;	y += obj.y;	z += obj.z;
	return *this;
}

CVector3d CVector3d::operator-(const CVector3d& obj)
{
	CVector3d tmp;
	tmp.x = x - obj.x;	tmp.y = y - obj.y;	tmp.z = z - obj.z;
	return (tmp);
}

CVector3d& CVector3d::operator-=(const CVector3d& obj)
{
	x -= obj.x;	y -= obj.y;	z -= obj.z;
	return *this;
}

CVector3d  CVector3d::operator-()
{
	CVector3d tmp;
	tmp.x = -x; tmp.y = -y; tmp.z = -z;
	return(tmp);
}

CVector3d CVector3d::operator*(const double a)
{
	CVector3d tmp;
	tmp.x = a * x;	tmp.y = a * y;	tmp.z = a * z;
	return (tmp);
}
CVector3d operator*(const double a, const CVector3d& obj)
{
	CVector3d tmp;
	tmp.x = a * obj.x;	tmp.y = a * obj.y;	tmp.z = a * obj.z;
	return (tmp);
}

CVector3d::operator CPoint3d()
{
	return CPoint3d(x, y, z);
}


CVector3d CVector3d::Mid(CVector3d a)
{
	CVector3d tmp;
	tmp.x = (x + a.x) / 2.0;
	tmp.y = (y + a.y) / 2.0;
	tmp.z = (z + a.z) / 2.0;
	return (tmp);
}

CVector3d CVector3d::Normalize()
{
	double norm = Norm();
	CVector3d tmp;
	tmp.x = x / norm;	tmp.y = y / norm;	tmp.z = z / norm;
	return (tmp);
}

void CVector3d::Normalize(CVector3d a)
{
	double norm = a.Norm();
	x = a.x / norm;	y = a.y / norm;	z = a.z / norm;

}

double CVector3d::Norm()
{
	return (sqrt(x*x + y * y + z * z));
}

double CVector3d::Distance(CVector3d a)
{
	double X = x - a.x;
	double Y = y - a.y;
	double Z = z - a.z;
	return (sqrt(X*X + Y * Y + Z * Z));
}


double CVector3d::Dot(CVector3d a)
{
	double dot = x * a.x;
	dot += y * a.y;
	dot += z * a.z;
	return (dot);
}

CVector3d CVector3d::Cross(CVector3d a)
{
	CVector3d tmp;
	tmp.x = y * a.z - z * a.y;
	tmp.y = z * a.x - x * a.z;
	tmp.z = x * a.y - y * a.x;
	return (tmp);
}


double CVector3d::Angle(CVector3d a)
{
	double deg, den;
	den = Norm()*a.Norm();
	if (den < 1.0e-15) {
		std::cout << "error" << std::endl;
		return 0;
	}
	deg = Dot(a) / den;
	if (deg > 1.0)	deg = 1.0;
	if (deg < -1.0)	deg = -1.0;

	deg = acos(deg);
	deg = 180.0*(deg / M_PI);

	return deg;
}

double CVector3d::PointLineDistance(CVector3d P0, CVector3d P1)
{
	CVector3d A = P1 - P0;
	CVector3d B(x - P0.x, y - P0.y, z - P0.z);
	return ((A.Cross(B)).Norm() / P0.Distance(P1));
}

CVector3d CVector3d::Max(CVector3d a)
{
	CVector3d tmp;
	tmp.x = max(x, a.x);
	tmp.y = max(y, a.y);
	tmp.z = max(z, a.z);
	return (tmp);
}

CVector3d CVector3d::Max(CPoint3d a)
{
	CVector3d tmp;
	tmp.x = max(x, a.x);
	tmp.y = max(y, a.y);
	tmp.z = max(z, a.z);
	return (tmp);
}

CVector3d CVector3d::Min(CVector3d a)
{
	CVector3d tmp;
	tmp.x = min(x, a.x);
	tmp.y = min(y, a.y);
	tmp.z = min(z, a.z);
	return (tmp);
}

CVector3d CVector3d::Min(CPoint3d a)
{
	CVector3d tmp;
	tmp.x = min(x, a.x);
	tmp.y = min(y, a.y);
	tmp.z = min(z, a.z);
	return (tmp);
}

CVector3d CVector3d::RotateX(double rad)
{
	CVector3d tmp;
	tmp.x = x;
	tmp.y = (y*cos(rad)) - (z*sin(rad));
	tmp.z = (y*sin(rad)) + (z*cos(rad));
	return (tmp);
}

CVector3d CVector3d::RotateY(double rad)
{
	CVector3d tmp;
	tmp.x = (z*sin(rad)) + (x*cos(rad));
	tmp.y = y;
	tmp.z = (z*cos(rad)) - (x*sin(rad));
	return (tmp);
}

CVector3d CVector3d::RotateZ(double rad)
{
	CVector3d tmp;
	tmp.x = (x*cos(rad)) - (y*sin(rad));
	tmp.y = (x*sin(rad)) + (y*cos(rad));
	tmp.z = z;
	return (tmp);
}
