#pragma once


class CPoint3d;
class CVector3d;

//##############################################//
//		//
//##############################################//
class CPoint3d
{
public:
	double x;
	double y;
	double z;
	double w;

public:



	CPoint3d();											//y01
	CPoint3d(double X, double Y, double Z, double W = 1.0);
	~CPoint3d();


	void Set(double X, double Y, double Z, double W = 1.0);
	void UnitVector(double X, double Y, double Z);
	void Clear();
	void Print();


	CPoint3d& operator=(const CPoint3d& obj); //y10
	CPoint3d  operator+(const CPoint3d& obj);
	CPoint3d& operator+=(const CPoint3d& obj);
	CPoint3d  operator-(const CPoint3d& obj);
	CPoint3d& operator-=(const CPoint3d& obj);
	CPoint3d  operator-();
	CPoint3d  operator*(const double a);
	friend CPoint3d operator*(const double a, const CPoint3d& obj);
	operator CVector3d();


	CPoint3d Mid(CPoint3d a);	//y20
	CPoint3d Normalize();
	void	Normalize(CPoint3d a);
	double	Norm();
	double	Distance(CPoint3d a);
	double	Dot(CPoint3d a);
	CPoint3d Cross(CPoint3d a);
	double	Angle(CPoint3d a);
	double	PointLineDistance(CPoint3d P0, CPoint3d P1);
	CPoint3d Max(CPoint3d a);
	CPoint3d Min(CPoint3d a);
	CPoint3d RotateX(double rad);
	CPoint3d RotateY(double rad);
	CPoint3d RotateZ(double rad);
};

//##############################################//
//	//
//##############################################//
class CVector3d
{
public:
	double x;
	double y;
	double z;

public:

	CVector3d();
	CVector3d(double X, double Y, double Z);
	~CVector3d();

	//
	void Set(double X, double Y, double Z);
	void UnitVector(double X, double Y, double Z);
	void Clear();
	void Print();


	//
	CVector3d& operator=(const CVector3d& obj);	//y10
	CVector3d  operator+(const CVector3d& obj);
	CVector3d& operator+=(const CVector3d& obj);
	CVector3d  operator-(const CVector3d& obj);
	CVector3d& operator-=(const CVector3d& obj);
	CVector3d  operator-();
	CVector3d  operator*(const double a);
	friend CVector3d operator*(const double a, const CVector3d& obj);
	operator CPoint3d();


	//
	CVector3d Mid(CVector3d a);		//y20
	CVector3d Normalize();
	void	Normalize(CVector3d a);
	double	Norm();
	double	Distance(CVector3d a);
	double	Dot(CVector3d a);
	CVector3d Cross(CVector3d a);
	double	Angle(CVector3d a);
	double	PointLineDistance(CVector3d P0, CVector3d P1);
	CVector3d Max(CVector3d a);
	CVector3d Max(CPoint3d a);
	CVector3d Min(CVector3d a);
	CVector3d Min(CPoint3d a);
	CVector3d RotateX(double rad);
	CVector3d RotateY(double rad);
	CVector3d RotateZ(double rad);
};
