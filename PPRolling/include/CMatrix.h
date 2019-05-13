#pragma once

#include <vector>
using namespace std;

class CVector;
class CMatrix;

//#################################//

//#################################//
class CVector
{
private:
	vector<double> v;

public:

	CVector();
	CVector(int m_size, double m_init = 0);
	CVector(CVector &m_v);
	CVector(vector<double> m_v);
	CVector(int m_size, double *m_v);
	CVector(CVector m_v, int m_first, int m_end);
	~CVector();
	/*****/
	void	assign(int m_size, double m_init = 0);
	void	assign(CVector m_v, int m_first, int m_end);
	/*********/
	int		size();								//y20
	void	Add(double m_element);
	void	Clear();
	void	SetZero();
	void	Print();
	/*****  *****/
	double	&operator[](const int &pos);		//y30
	CVector	&operator=(CVector &m_v);
	CVector	&operator=(vector<double> &m_v);
	CVector	operator+(CVector &m_v);
	CVector	&operator+=(CVector &m_v);
	CVector	operator-(CVector &m_v);
	CVector	&operator-=(CVector &m_v);
	CVector	operator-();
	CVector	operator*(const double k);
	friend CVector operator*(const double k, CVector m_v);
	double	operator*(CVector m_v);				//y40
	CVector	operator*(CMatrix m_mt);			//y41
	/***** ****/
	double	Norm();
	void	Normalize();

};


//#################################//
//
//#################################//
class CMatrix
{
private:
	vector<vector<double> > mt;
public:
	/**********/
	CMatrix();
	CMatrix(int m_row, int m_col, double m_init = 0);
	CMatrix(int m_rank);
	CMatrix(CMatrix &m_mt);
	CMatrix(vector<vector<double> > m_mt);
	CMatrix(int m_row, int m_col, double **m_mt);
	~CMatrix();

	/***** *****/
	void	assign(int m_row, int m_col, double m_init = 0);
	void	assign(int m_rank);
	void	assign(CMatrix m_mt);
	void	assign(vector<vector<double> > m_mt);
	void	assign(int m_row, int m_col, double **m_mt);
	/***** *****/
	int		r_size();
	int		c_size();
	double	&At(int m_r, int m_c);
	void	SetR(int m_r, CVector m_v);
	void	SetC(int m_c, CVector m_v);
	void	SetZero();
	CVector	row(int m_r);
	CVector	col(int m_c);
	void	Print();
	void	FPrint(int NameNumber = 0);
	//cs	ConstractCSMatrix(int m_r, int m_c,int nzmax);
	/**********/
	vector<double> &operator[](const int m_r);
	CMatrix	&operator=(CMatrix m_mt);
	CMatrix	&operator=(vector<vector<double> > m_mt);
	CMatrix	operator+(CMatrix m_mt);
	CMatrix &operator+=(CMatrix m_mt);
	CMatrix	operator-(CMatrix m_mt);
	CMatrix &operator-=(CMatrix m_mt);
	CMatrix	operator-();
	CMatrix	operator*(const double k);
	friend CMatrix	operator*(const double k, CMatrix m_mt);
	CVector	operator*(const CVector m_v);

	CMatrix	operator*(const CMatrix m_mt);

	/*****  *****/
	CMatrix	Remove(int m_r, int m_c);
	CMatrix	Transpose();
	double	Det();
	void	IdentifyMatrix();

	CMatrix	Inverse();
	void	Inverse(CMatrix& ma, CMatrix& mat, CVector& vec1, CVector& vec2);


	/***** LU *****/
	void	ludcmp(int *indx, double *d);				//y60
	void	lubksb(int *indx, double b[]);
	CMatrix InverseLU();


	operator double*();
	void	SetTranslate4d(double dx, double dy, double dz);
	void	SetRotate4d(double Angle, double vx, double vy, double vz);
	void	SetScale4d(double scaleX, double scaleY, double scaleZ);
	double	Det4d();													//y104(determinant)
	CMatrix	Inverse4d();
	void	Inverse4d(CMatrix &m_matrix);
	CMatrix Translate4d(double dx, double dy, double dz);
	CMatrix Rotate4d(double Angle, double vx, double vy, double vz);
	CMatrix Scale4d(double scaleX, double scaleY, double scaleZ);
};
