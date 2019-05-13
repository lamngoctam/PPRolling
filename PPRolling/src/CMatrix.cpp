

#include "Linear3d.h"

#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

//######################################//
//	CVector//
//######################################//
/****** *****/

//y01
CVector::CVector() {}

//y02
CVector::CVector(int m_size, double m_init)
{
	v.assign(m_size, m_init);
}

//y03
CVector::CVector(CVector &m_v)
{
	v.assign(m_v.v.begin(), m_v.v.end());
}

//y04
CVector::CVector(vector<double> m_v)
{
	v.assign(m_v.begin(), m_v.end());
}

CVector::CVector(int m_size, double *m_v)
{
	v.assign(m_size, 0);
	for (int i = 0; i < m_size; i++)	v[i] = m_v[i];
}


CVector::CVector(CVector m_v, int m_first, int m_end)
{
	v.assign(m_end - m_first + 1, 0);
	for (int i = m_first;i <= m_end;i++) v[i - m_first] = m_v.v[i];
}

CVector::~CVector() { v.clear(); }

/******************************/

void CVector::assign(int m_size, double m_init)
{
	v.assign(m_size, m_init);
}

//
void CVector::assign(CVector m_v, int m_first, int m_end)
{
	v.assign(m_end - m_first + 1, 0);
	for (int i = m_first;i <= m_end;i++) v[i - m_first] = m_v.v[i];
}

/*****************************/

int CVector::size()
{
	return ((int)v.size());
}


void CVector::Add(double m_element)
{
	v.push_back(m_element);
}


void CVector::Clear()
{
	v.clear();
}


void CVector::SetZero()
{
	for (int i = 0;i < (int)v.size();i++) v[i] = 0;
}

void CVector::Print()
{
	cout << "v[" << v.size() << "]= (";
	for (int i = 0;i < (int)v.size();i++) cout << v[i] << ", ";
	cout << ")" << endl;
}

/*****************************/

//z[]vec.v[10]vec[10]
double& CVector::operator[](const int &pos)
{
	return (v[pos]);
}


CVector& CVector::operator=(CVector &m_v)
{
	for (int i = 0;i < (int)m_v.v.size();i++) {
		v[i] = m_v.v[i];
	}
	return *this;
}

CVector& CVector::operator=(vector<double> &m_v)
{
	for (int i = 0;i < (int)m_v.size();i++) {
		v[i] = m_v[i];
	}
	return *this;
}


CVector CVector::operator+(CVector &m_v)
{
	CVector tmp;
	tmp.v.assign(v.size(), 0);
	for (int i = 0;i < (int)v.size();i++) tmp.v[i] = v[i] + m_v.v[i];
	return (tmp);
}


CVector& CVector::operator+=(CVector &m_v)
{
	for (int i = 0;i < (int)v.size();i++) v[i] += m_v.v[i];
	return *this;
}


CVector CVector::operator-(CVector &m_v)
{
	CVector tmp;
	tmp.v.assign(v.size(), 0);
	for (int i = 0;i < (int)v.size();i++) tmp.v[i] = v[i] - m_v.v[i];
	return (tmp);
}


CVector& CVector::operator-=(CVector &m_v)
{
	for (int i = 0;i < (int)v.size();i++) v[i] -= m_v.v[i];
	return *this;
}

CVector CVector::operator-()
{
	CVector tmp(v.size());
	for (int i = 0;i < (int)v.size();i++) tmp.v[i] = -v[i];
	return (tmp);
}


CVector CVector::operator*(const double k)
{
	CVector tmp(v.size());
	for (int i = 0;i < (int)v.size();i++) tmp.v[i] = k * v[i];
	return tmp;
}

CVector operator*(const double k, CVector m_v)
{
	CVector tmp(m_v.v.size());
	for (int i = 0;i < (int)tmp.v.size();i++) tmp.v[i] = k * m_v.v[i];
	return (tmp);
}

double CVector::operator*(CVector m_v)
{
	double md = 0.0;
	for (int i = 0;i < (int)v.size();i++) md += v[i] * m_v.v[i];
	return (md);
}

//matrix[][] * vector[]
//
//CVector	CVector::operator*(CMatrix m_mt)
//{
//	CVector tmp;
//	tmp.assign(m_mt.c_size());
//	for (int j = 0;j < m_mt.c_size();j++) tmp[j] = (*this)* m_mt.col(j);
//	return tmp;
//}

/*****************  ***************/

double CVector::Norm()
{
	double md;
	md = 0;
	for (int i = 0;i < (int)v.size();i++) md += v[i] * v[i];
	return sqrt(md);
}

void CVector::Normalize()
{
	double md = 0.0;
	for (int i = 0;i < (int)v.size();i++) md += pow(v[i], 2);
	for (int i = 0;i < (int)v.size();i++) v[i] = v[i] / sqrt(md);
}


//######################################//
//	
//######################################//
/****** *****/


CMatrix::CMatrix() {}

CMatrix::CMatrix(int m_row, int m_col, double m_init)
{
	vector<double> tmp(m_col, m_init);
	mt.assign(m_row, tmp);
}


CMatrix::CMatrix(int m_rank)
{
	vector<double> tmp(m_rank, 0);
	mt.assign(m_rank, tmp);
}

CMatrix::CMatrix(CMatrix &m_mt)
{
	vector<double> tmp((*m_mt.mt.begin()).size(), 0);
	mt.assign(m_mt.mt.size(), tmp);
	int i, j;
	for (i = 0;i < (int)m_mt.mt.size();i++) {
		for (j = 0;j < (int)(*m_mt.mt.begin()).size();j++) {
			mt[i][j] = m_mt.mt[i][j];
		}
	}
}
CMatrix::CMatrix(vector<vector<double> > m_mt)
{
	vector<double> tmp((*m_mt.begin()).size(), 0);
	mt.assign(m_mt.size(), tmp);
	int i, j;
	for (i = 0;i < (int)m_mt.size();i++) {
		for (j = 0;j < (int)(*m_mt.begin()).size();j++) {
			mt[i][j] = m_mt[i][j];
		}
	}
}

CMatrix::CMatrix(int m_row, int m_col, double **m_mt)
{
	vector<double> tmp(m_col, 0);
	mt.assign(m_row, tmp);
	int i, j;
	for (i = 0; i < m_row; i++) {
		for (j = 0; j < m_col; j++) {
			mt[i][j] = m_mt[i][j];
		}
	}
}


CMatrix::~CMatrix() { mt.clear(); }

/*************** ***************/

void CMatrix::assign(int m_row, int m_col, double m_init)
{
	vector<double> tmp(m_col, m_init);
	mt.assign(m_row, tmp);
}


void CMatrix::assign(int m_rank)
{
	vector<double> tmp(m_rank, 0);
	mt.assign(m_rank, tmp);
}


void CMatrix::assign(CMatrix m_mt)
{
	vector<double> tmp((*m_mt.mt.begin()).size(), 0);
	mt.assign(m_mt.mt.size(), tmp);
	int i, j;
	for (i = 0;i < (int)m_mt.mt.size();i++) {
		for (j = 0;j < (int)(*m_mt.mt.begin()).size();j++) {
			mt[i][j] = m_mt.mt[i][j];
		}
	}
}

void CMatrix::assign(vector<vector<double> > m_mt)
{
	vector<double> tmp((*m_mt.begin()).size(), 0);
	mt.assign(m_mt.size(), tmp);
	int i, j;
	for (i = 0;i < (int)m_mt.size();i++) {
		for (j = 0;j < (int)(*m_mt.begin()).size();j++) {
			mt[i][j] = m_mt[i][j];
		}
	}
}


void CMatrix::assign(int m_row, int m_col, double **m_mt)
{
	vector<double> tmp(m_col, 0);
	mt.assign(m_row, tmp);
	int i, j;
	for (i = 0; i < m_row; i++) {
		for (j = 0; j < m_col; j++) {
			mt[i][j] = m_mt[i][j];
		}
	}
}

/*************** ***************/

int CMatrix::r_size()
{
	return((int)mt.size());
}


int CMatrix::c_size()
{
	return((int)(*mt.begin()).size());
}

double	&CMatrix::At(int m_r, int m_c)
{
	return(mt[m_r][m_c]);
}

//y18
void CMatrix::SetR(int m_r, CVector m_v)
{
	for (int j = 0;j < c_size();j++) mt[m_r][j] = m_v[j];
}

//
void CMatrix::SetC(int m_c, CVector m_v)
{
	for (int i = 0; i < r_size(); i++) mt[i][m_c] = m_v[i];
}


void CMatrix::SetZero()
{
	for (int i = 0; i < r_size(); i++) {
		for (int j = 0; j < c_size(); j++) {
			mt[i][j] = 0.0;
		}
	}
}


CVector	CMatrix::row(int m_r)
{
	CVector tmp(mt[m_r]);
	return (tmp);
}


CVector	CMatrix::col(int m_c)
{
	CVector tmp(r_size());
	for (int i = 0;i < r_size();i++) tmp[i] = mt[i][m_c];
	return (tmp);
}


void CMatrix::Print()
{
	int i, j;
	for (i = 0; i < r_size(); i++) {
		for (j = 0; j < c_size(); j++) {
			cout << mt[i][j] << " ";
		}
		cout << endl;
	}
}


void CMatrix::FPrint(int NameNumber)
{
	int i, j;
	char str[32];
	char str1[32] = "../Matrix";
	char str2[] = ".csv";
	sprintf(str, "%s%d%s", str1, NameNumber, str2);

	ofstream fout(str);

	for (i = 0; i < r_size(); i++) {
		for (j = 0; j < c_size(); j++) {
			fout << mt[i][j] << ",";
		}
		fout << endl;
	}
	fout.close();
}


//cs *CMatrix::ConstractCSMatrix(int m_r, int m_c,int nzmax)
//{
//	cs *tmp;
//	int TotalM = 0;
//	int i,j,k=1;
//	tmp = cs_spalloc(m_r, m_c, nzmax, 1, 0);//csparse
//	tmp->p[0] = 0;
//
//	//
//	for(i=0; i<m_r; i++){
//		for(j=0; j<m_c; j++){
//			if(mt[i][j] > MACHINE_ERROR){
//				tmp->i[TotalM] = j;
//				tmp->x[TotalM] = mt[i][j];
//				TotalM++;
//			}
//		}
//		tmp->p[k] = TotalM;
//		k++;
//	}
//	return (tmp);
//	cs_free(tmp);
//}

/************** ***************/


vector<double> &CMatrix::operator[](int m_r)
{
	return (mt[m_r]);
}


CMatrix& CMatrix::operator=(CMatrix m_mt)
{
	int i, j;
	for (i = 0;i < (int)mt.size();i++)
		for (j = 0;j < (int)(*mt.begin()).size();j++) mt[i][j] = m_mt.mt[i][j];
	return *this;
}


CMatrix& CMatrix::operator=(vector<vector<double> > m_mt)
{
	int i, j;
	for (i = 0;i < (int)mt.size();i++) {
		for (j = 0;j < (int)(*mt.begin()).size();j++) {
			mt[i][j] = m_mt[i][j];
		}
	}
	return *this;
}


CMatrix	CMatrix::operator+(CMatrix m_mt)
{
	int i, j;
	CMatrix tmp(r_size(), c_size());
	for (i = 0;i < r_size();i++) {
		for (j = 0;j < c_size();j++) {
			tmp.mt[i][j] = mt[i][j] + m_mt.mt[i][j];
		}
	}
	return (tmp);
}

CMatrix& CMatrix::operator+=(CMatrix m_mt)
{
	int i, j;
	for (i = 0;i < r_size();i++) {
		for (j = 0;j < c_size();j++) {
			mt[i][j] += m_mt.mt[i][j];
		}
	}
	return *this;
}


CMatrix	CMatrix::operator-(CMatrix m_mt)
{
	int i, j;
	CMatrix tmp(r_size(), c_size());
	for (i = 0;i < r_size();i++) {
		for (j = 0;j < c_size();j++) {
			tmp.mt[i][j] = mt[i][j] - m_mt.mt[i][j];
		}
	}
	return (tmp);
}


CMatrix& CMatrix::operator-=(CMatrix m_mt)
{
	int i, j;
	for (i = 0;i < r_size();i++) {
		for (j = 0;j < c_size();j++) {
			mt[i][j] -= m_mt.mt[i][j];
		}
	}
	return *this;
}

CMatrix	CMatrix::operator-()
{
	int i, j;
	CMatrix tmp(r_size(), c_size());
	for (i = 0;i < r_size();i++) {
		for (j = 0;j < c_size();j++) {
			tmp.mt[i][j] = -mt[i][j];
		}
	}
	return (tmp);
}


CMatrix	CMatrix::operator*(double k)
{
	int i, j;
	CMatrix tmp(r_size(), c_size());
	for (i = 0;i < r_size();i++) {
		for (j = 0;j < c_size();j++) {
			tmp.mt[i][j] = k * mt[i][j];
		}
	}
	return (tmp);
}

CMatrix	operator*(double k, CMatrix m_mt)
{
	int i, j;
	CMatrix tmp(m_mt.r_size(), m_mt.c_size());
	for (i = 0;i < m_mt.r_size();i++) {
		for (j = 0;j < m_mt.c_size();j++) {
			tmp.mt[i][j] = k * m_mt.mt[i][j];
		}
	}
	return (tmp);
}


CVector	CMatrix::operator*(CVector m_v)
{
	CVector tmp;
	tmp.assign(r_size());
	for (int i = 0;i < r_size();i++) tmp[i] = (*this).row(i)*m_v;
	return (tmp);
}


//CMatrix	CMatrix::operator*(CMatrix m_mt)
//{
//	CMatrix tmp;
//	int i, j;
//	tmp.assign(r_size(), m_mt.c_size());
//	for (i = 0;i < r_size();i++) {
//		for (j = 0;j < m_mt.c_size();j++) {
//			tmp.mt[i][j] = (*this).row(i)*m_mt.col(j);
//		}
//	}
//	return tmp;
//}

/*************** ***************/


CMatrix	CMatrix::Remove(int m_r, int m_c)
{
	CMatrix tmp(r_size() - 1, c_size() - 1);
	int i, j;
	for (i = 0;i < m_r;i++)
		for (j = 0;j < m_c;j++) tmp.mt[i][j] = mt[i][j];
	for (i = m_r;i < r_size() - 1;i++)
		for (j = 0;j < m_c;j++) tmp.mt[i][j] = mt[i + 1][j];
	for (i = 0;i < m_r;i++)
		for (j = m_c;j < c_size() - 1;j++) tmp.mt[i][j] = mt[i][j + 1];
	for (i = m_r;i < r_size() - 1;i++)
		for (j = m_c;j < c_size() - 1;j++) tmp.mt[i][j] = mt[i + 1][j + 1];
	return (tmp);
}

//(transpose matrix)
CMatrix	CMatrix::Transpose()
{
	CMatrix tmp(c_size(), r_size());
	int i, j;
	for (i = 0;i < c_size();i++)
		for (j = 0;j < r_size();j++) tmp.mt[i][j] = mt[j][i];
	return (tmp);

}

//(determinant)
double	CMatrix::Det()
{
	double d;
	if (r_size() == 1) d = mt[0][0];
	else
	{
		int j;
		d = 0;
		for (j = 0;j < r_size();j++)
			d += pow(-1.0, j)*mt[0][j] * (*this).Remove(0, j).Det();
	}
	return d;
}

//
void CMatrix::IdentifyMatrix()
{
	SetZero();
	int n = min(r_size(), c_size());
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			if (i == j) {
				mt[i][j] = 1;
			}
		}
	}
}


//
////(inverse matrix)
//CMatrix	CMatrix::Inverse()
//{
//	CMatrix ma, mat(mt), m_zero(r_size());
//	CVector vec1(r_size()), vec2(r_size());
//	ma.assign(r_size());
//	ma.IdentifyMatrix();
//
//	int i, j;
//	for (i = 0;i < r_size() - 1;i++)
//	{
//		if (mat[i][i] == 0)
//		{
//			for (j = i + 1;j < r_size();j++)
//			{
//				if (mat[j][i] != 0)
//				{
//					vec1 = mat.row(i); vec2 = mat.row(j);
//					mat.SetR(i, vec2); mat.SetR(j, vec1);
//					vec1 = ma.row(i); vec2 = ma.row(j);
//					ma.SetR(i, vec2); ma.SetR(j, vec1);
//					break;
//				}
//			}
//			if (j == r_size()) return m_zero;
//		}
//
//		for (j = i + 1;j < r_size();j++)
//		{
//			vec1 = (-mat[j][i] / mat[i][i])*mat.row(i) + mat.row(j);
//			vec2 = (-mat[j][i] / mat[i][i])*ma.row(i) + ma.row(j);
//			mat.SetR(j, vec1);
//			ma.SetR(j, vec2);
//		}
//	}
//
//	if (mat[r_size() - 1][r_size() - 1] == 0) return m_zero;
//	else
//	{
//		for (i = r_size() - 1;i > 0;i--)
//		{
//			for (j = i - 1;j >= 0;j--)
//			{
//				vec1 = (-mat[j][i] / mat[i][i])*mat.row(i) + mat.row(j);
//				vec2 = (-mat[j][i] / mat[i][i])*ma.row(i) + ma.row(j);
//				mat.SetR(j, vec1);
//				ma.SetR(j, vec2);
//			}
//		}
//	}
//
//	for (i = 0;i < r_size();i++)
//	{
//		for (j = 0;j < r_size();j++) { ma.mt[i][j] = ma.mt[i][j] / mat.mt[i][i]; }
//	}
//	return ma;
//}
//
////speed up
//void CMatrix::Inverse(CMatrix& ma, CMatrix& mat, CVector& vec1, CVector& vec2)
//{
//	ma.IdentifyMatrix();
//	mat = mt;
//
//	int i, j;
//	for (i = 0;i < r_size() - 1;i++)
//	{
//		if (mat[i][i] == 0)
//		{
//			for (j = i + 1;j < r_size();j++)
//			{
//				if (mat[j][i] != 0)
//				{
//					vec1 = mat.row(i); vec2 = mat.row(j);
//					mat.SetR(i, vec2); mat.SetR(j, vec1);
//					vec1 = ma.row(i); vec2 = ma.row(j);
//					ma.SetR(i, vec2); ma.SetR(j, vec1);
//					break;
//				}
//			}
//			if (j == r_size()) return;
//		}
//
//		for (j = i + 1;j < r_size();j++)
//		{
//			vec1 = (-mat[j][i] / mat[i][i])*mat.row(i) + mat.row(j);
//			vec2 = (-mat[j][i] / mat[i][i])*ma.row(i) + ma.row(j);
//			mat.SetR(j, vec1);
//			ma.SetR(j, vec2);
//		}
//	}
//
//	if (mat[r_size() - 1][r_size() - 1] == 0) return;
//	else
//	{
//		for (i = r_size() - 1;i > 0;i--)
//		{
//			for (j = i - 1;j >= 0;j--)
//			{
//				vec1 = (-mat[j][i] / mat[i][i])*mat.row(i) + mat.row(j);
//				vec2 = (-mat[j][i] / mat[i][i])*ma.row(i) + ma.row(j);
//				mat.SetR(j, vec1);
//				ma.SetR(j, vec2);
//			}
//		}
//	}
//
//	for (i = 0;i < r_size();i++)
//	{
//		for (j = 0;j < r_size();j++) { ma.mt[i][j] = ma.mt[i][j] / mat.mt[i][i]; }
//	}
//}
//

//LU
void CMatrix::ludcmp(int *indx, double *d)
{
	//input a[n~n],n,
	//output a(ln),indx[],d()
	int n = r_size();
	int i, imax, j, k;
	double big, dum, sum, temp;
	double *vv;

	vv = new double[n];
	*d = 1.0;

	for (i = 0; i < n; i++) {
		big = 0.0;

		for (j = 0; j < n; j++) {
			if ((temp = fabs(mt[i][j])) > big) {
				big = temp;
			}
		}

		if (big == 0.0) {
			cout << "error" << endl;
			break;
		}

		vv[i] = 1.0 / big;
	}

	for (j = 0; j < n; j++) {
		for (i = 0; i < j; i++) {
			sum = mt[i][j];
			for (k = 0; k < i; k++) {
				sum -= mt[i][k] * mt[k][j];
			}
			mt[i][j] = sum;
		}

		big = 0.0;

		for (i = j; i < n; i++) {
			sum = mt[i][j];
			for (k = 0; k < j; k++) {
				sum -= mt[i][k] * mt[k][j];
			}

			mt[i][j] = sum;

			if ((dum = vv[i] * fabs(sum)) >= big) {
				big = dum;
				imax = i;
			}
		}
		if (j != imax) {
			for (k = 0; k < n; k++) {
				dum = mt[imax][k];
				mt[imax][k] = mt[j][k];
				mt[j][k] = dum;
			}

			*d = -(*d);
			vv[imax] = vv[j];
		}

		indx[j] = imax;

		if (mt[j][j] == 0.0) {
			mt[j][j] = MACHINE_ERROR;
		}

		if (j != n - 1) {
			dum = 1.0 / (mt[j][j]);
			for (i = j + 1; i < n; i++) {
				mt[i][j] *= dum;
			}
		}
	}
	delete[] vv;
}

//A * x = B 
void CMatrix::lubksb(int *indx, double b[])
{
	// A * x = B ludcmp
	//ndx[1,...,n]ludcmp
	//	input	b[](),indxludcmp
	//	output	x[]()
	int n = r_size();
	int i, ii = 0, ip, j;
	double sum;

	for (i = 0; i < n; i++) {
		ip = indx[i];
		sum = b[ip];
		b[ip] = b[i];

		if (ii != 0) {
			for (j = ii - 1; j < i; j++) {
				sum -= mt[i][j] * b[j];
			}

		}
		else if (sum != 0) {
			ii = i + 1;

		}
		b[i] = sum;
	}

	for (i = n - 1; i >= 0; i--) {
		sum = b[i];
		for (j = i + 1; j < n; j++) {
			sum -= mt[i][j] * b[j];
		}
		b[i] = sum / mt[i][i];
	}
}

CMatrix CMatrix::InverseLU()
{
	int i, j;
	int *indx = new int[r_size()];
	double d, *col;
	col = new double[r_size()];
	CMatrix tmp(r_size(), c_size());
	ludcmp(indx, &d);

	for (j = 0; j < r_size(); j++) {
		for (i = 0; i < r_size(); i++)	col[i] = 0.0;
		col[j] = 1.0;
		lubksb(indx, col);
		for (i = 0; i < r_size(); i++)	tmp.mt[i][j] = col[i];
	}
	return (tmp);
}


/**********  **********/


CMatrix::operator double*()
{
	double *tmp;
	int i, j, k = 0;
	tmp = new double[16];
	for (j = 0; j < 4; j++) {
		for (i = 0; i < 4; i++)
		{
			tmp[k] = mt[i][j];
			k++;
		}
	}
	return (tmp);
	delete[] tmp;
}


void CMatrix::SetTranslate4d(double dx, double dy, double dz)
{
	mt[0][0] = 1; mt[0][1] = 0; mt[0][2] = 0; mt[0][3] = dx;
	mt[1][0] = 0; mt[1][1] = 1; mt[1][2] = 0; mt[1][3] = dy;
	mt[2][0] = 0; mt[2][1] = 0; mt[2][2] = 1; mt[2][3] = dz;
	mt[3][0] = 0; mt[3][1] = 0; mt[3][2] = 0; mt[3][3] = 1;
}

void CMatrix::SetRotate4d(double Angle, double vx, double vy, double vz)
{
	double v[3];
	v[0] = vx / sqrt(vx*vx + vy * vy + vz * vz);
	v[1] = vy / sqrt(vx*vx + vy * vy + vz * vz);
	v[2] = vz / sqrt(vx*vx + vy * vy + vz * vz);

	mt[0][0] = v[0] * v[0] * (1 - cos(Angle)) + cos(Angle);
	mt[0][1] = v[0] * v[1] * (1 - cos(Angle)) - v[2] * sin(Angle);
	mt[0][2] = v[0] * v[2] * (1 - cos(Angle)) + v[1] * sin(Angle);

	mt[1][0] = v[0] * v[1] * (1 - cos(Angle)) + v[2] * sin(Angle);
	mt[1][1] = v[1] * v[1] * (1 - cos(Angle)) + cos(Angle);
	mt[1][2] = v[2] * v[1] * (1 - cos(Angle)) - v[0] * sin(Angle);

	mt[2][0] = v[0] * v[2] * (1 - cos(Angle)) - v[1] * sin(Angle);
	mt[2][1] = v[1] * v[2] * (1 - cos(Angle)) + v[0] * sin(Angle);
	mt[2][2] = v[2] * v[2] * (1 - cos(Angle)) + cos(Angle);

	mt[0][3] = 0; mt[1][3] = 0; mt[2][3] = 0;
	mt[3][0] = 0; mt[3][1] = 0; mt[3][2] = 0; mt[3][3] = 1;
}


void CMatrix::SetScale4d(double scaleX, double scaleY, double scaleZ)
{
	mt[0][0] = scaleX; mt[0][1] = 0;	  mt[0][2] = 0;      mt[0][3] = 0;
	mt[1][0] = 0;		 mt[1][1] = scaleY; mt[1][2] = 0;      mt[1][3] = 0;
	mt[2][0] = 0;		 mt[2][1] = 0;      mt[2][2] = scaleZ; mt[2][3] = 0;
	mt[3][0] = 0;		 mt[3][1] = 0;      mt[3][2] = 0;      mt[3][3] = 1;
}

//(determinant)												
double	CMatrix::Det4d()
{
	return(mt[0][0] * mt[1][1] * mt[2][2] * mt[3][3] - mt[0][0] * mt[1][1] * mt[2][3] * mt[3][2] - mt[0][0] * mt[2][1] * mt[1][2] * mt[3][3] + mt[0][0] * mt[2][1] * mt[1][3] * mt[3][2] + mt[0][0] * mt[3][1] * mt[1][2] * mt[2][3] - mt[0][0] * mt[3][1] * mt[1][3] * mt[2][2] - mt[1][0] * mt[0][1] * mt[2][2] * mt[3][3] + mt[1][0] * mt[0][1] * mt[2][3] * mt[3][2] + mt[1][0] * mt[2][1] * mt[0][2] * mt[3][3] - mt[1][0] * mt[2][1] * mt[0][3] * mt[3][2] - mt[1][0] * mt[3][1] * mt[0][2] * mt[2][3] + mt[1][0] * mt[3][1] * mt[0][3] * mt[2][2] + mt[2][0] * mt[0][1] * mt[1][2] * mt[3][3] - mt[2][0] * mt[0][1] * mt[1][3] * mt[3][2] - mt[2][0] * mt[1][1] * mt[0][2] * mt[3][3] + mt[2][0] * mt[1][1] * mt[0][3] * mt[3][2] + mt[2][0] * mt[3][1] * mt[0][2] * mt[1][3] - mt[2][0] * mt[3][1] * mt[0][3] * mt[1][2] - mt[3][0] * mt[0][1] * mt[1][2] * mt[2][3] + mt[3][0] * mt[0][1] * mt[1][3] * mt[2][2] + mt[3][0] * mt[1][1] * mt[0][2] * mt[2][3] - mt[3][0] * mt[1][1] * mt[0][3] * mt[2][2] - mt[3][0] * mt[2][1] * mt[0][2] * mt[1][3] + mt[3][0] * mt[2][1] * mt[0][3] * mt[1][2]);
}


CMatrix	CMatrix::Inverse4d()
{
	CMatrix tmp(4);
	double  determinant = Det4d();

	tmp.mt[0][0] = (mt[1][1] * mt[2][2] * mt[3][3] - mt[1][1] * mt[2][3] * mt[3][2] - mt[2][1] * mt[1][2] * mt[3][3] + mt[2][1] * mt[1][3] * mt[3][2] + mt[3][1] * mt[1][2] * mt[2][3] - mt[3][1] * mt[1][3] * mt[2][2]) / determinant;
	tmp.mt[0][1] = (-mt[0][1] * mt[2][2] * mt[3][3] + mt[0][1] * mt[2][3] * mt[3][2] + mt[2][1] * mt[0][2] * mt[3][3] - mt[2][1] * mt[0][3] * mt[3][2] - mt[3][1] * mt[0][2] * mt[2][3] + mt[3][1] * mt[0][3] * mt[2][2]) / determinant;
	tmp.mt[0][2] = (mt[0][1] * mt[1][2] * mt[3][3] - mt[0][1] * mt[1][3] * mt[3][2] - mt[1][1] * mt[0][2] * mt[3][3] + mt[1][1] * mt[0][3] * mt[3][2] + mt[3][1] * mt[0][2] * mt[1][3] - mt[3][1] * mt[0][3] * mt[1][2]) / determinant;
	tmp.mt[0][3] = (-mt[0][1] * mt[1][2] * mt[2][3] + mt[0][1] * mt[1][3] * mt[2][2] + mt[1][1] * mt[0][2] * mt[2][3] - mt[1][1] * mt[0][3] * mt[2][2] - mt[2][1] * mt[0][2] * mt[1][3] + mt[2][1] * mt[0][3] * mt[1][2]) / determinant;
	tmp.mt[1][0] = (-mt[1][0] * mt[2][2] * mt[3][3] + mt[1][0] * mt[2][3] * mt[3][2] + mt[2][0] * mt[1][2] * mt[3][3] - mt[2][0] * mt[1][3] * mt[3][2] - mt[3][0] * mt[1][2] * mt[2][3] + mt[3][0] * mt[1][3] * mt[2][2]) / determinant;
	tmp.mt[1][1] = (mt[0][0] * mt[2][2] * mt[3][3] - mt[0][0] * mt[2][3] * mt[3][2] - mt[2][0] * mt[0][2] * mt[3][3] + mt[2][0] * mt[0][3] * mt[3][2] + mt[3][0] * mt[0][2] * mt[2][3] - mt[3][0] * mt[0][3] * mt[2][2]) / determinant;
	tmp.mt[1][2] = (-mt[0][0] * mt[1][2] * mt[3][3] + mt[0][0] * mt[1][3] * mt[3][2] + mt[1][0] * mt[0][2] * mt[3][3] - mt[1][0] * mt[0][3] * mt[3][2] - mt[3][0] * mt[0][2] * mt[1][3] + mt[3][0] * mt[0][3] * mt[1][2]) / determinant;
	tmp.mt[1][3] = (mt[0][0] * mt[1][2] * mt[2][3] - mt[0][0] * mt[1][3] * mt[2][2] - mt[1][0] * mt[0][2] * mt[2][3] + mt[1][0] * mt[0][3] * mt[2][2] + mt[2][0] * mt[0][2] * mt[1][3] - mt[2][0] * mt[0][3] * mt[1][2]) / determinant;
	tmp.mt[2][0] = (mt[1][0] * mt[2][1] * mt[3][3] - mt[1][0] * mt[2][3] * mt[3][1] - mt[2][0] * mt[1][1] * mt[3][3] + mt[2][0] * mt[1][3] * mt[3][1] + mt[3][0] * mt[1][1] * mt[2][3] - mt[3][0] * mt[1][3] * mt[2][1]) / determinant;
	tmp.mt[2][1] = (-mt[0][0] * mt[2][1] * mt[3][3] + mt[0][0] * mt[2][3] * mt[3][1] + mt[2][0] * mt[0][1] * mt[3][3] - mt[2][0] * mt[0][3] * mt[3][1] - mt[3][0] * mt[0][1] * mt[2][3] + mt[3][0] * mt[0][3] * mt[2][1]) / determinant;
	tmp.mt[2][2] = (mt[0][0] * mt[1][1] * mt[3][3] - mt[0][0] * mt[1][3] * mt[3][1] - mt[1][0] * mt[0][1] * mt[3][3] + mt[1][0] * mt[0][3] * mt[3][1] + mt[3][0] * mt[0][1] * mt[1][3] - mt[3][0] * mt[0][3] * mt[1][1]) / determinant;
	tmp.mt[2][3] = (-mt[0][0] * mt[1][1] * mt[2][3] + mt[0][0] * mt[1][3] * mt[2][1] + mt[1][0] * mt[0][1] * mt[2][3] - mt[1][0] * mt[0][3] * mt[2][1] - mt[2][0] * mt[0][1] * mt[1][3] + mt[2][0] * mt[0][3] * mt[1][1]) / determinant;
	tmp.mt[3][0] = (-mt[1][0] * mt[2][1] * mt[3][2] + mt[1][0] * mt[2][2] * mt[3][1] + mt[2][0] * mt[1][1] * mt[3][2] - mt[2][0] * mt[1][2] * mt[3][1] - mt[3][0] * mt[1][1] * mt[2][2] + mt[3][0] * mt[1][2] * mt[2][1]) / determinant;
	tmp.mt[3][1] = (mt[0][0] * mt[2][1] * mt[3][2] - mt[0][0] * mt[2][2] * mt[3][1] - mt[2][0] * mt[0][1] * mt[3][2] + mt[2][0] * mt[0][2] * mt[3][1] + mt[3][0] * mt[0][1] * mt[2][2] - mt[3][0] * mt[0][2] * mt[2][1]) / determinant;
	tmp.mt[3][2] = (-mt[0][0] * mt[1][1] * mt[3][2] + mt[0][0] * mt[1][2] * mt[3][1] + mt[1][0] * mt[0][1] * mt[3][2] - mt[1][0] * mt[0][2] * mt[3][1] - mt[3][0] * mt[0][1] * mt[1][2] + mt[3][0] * mt[0][2] * mt[1][1]) / determinant;
	tmp.mt[3][3] = (mt[0][0] * mt[1][1] * mt[2][2] - mt[0][0] * mt[1][2] * mt[2][1] - mt[1][0] * mt[0][1] * mt[2][2] + mt[1][0] * mt[0][2] * mt[2][1] + mt[2][0] * mt[0][1] * mt[1][2] - mt[2][0] * mt[0][2] * mt[1][1]) / determinant;

	return (tmp);
}

void CMatrix::Inverse4d(CMatrix &m_matrix)
{
	double  determinant = Det4d();

	m_matrix.mt[0][0] = (mt[1][1] * mt[2][2] * mt[3][3] - mt[1][1] * mt[2][3] * mt[3][2] - mt[2][1] * mt[1][2] * mt[3][3] + mt[2][1] * mt[1][3] * mt[3][2] + mt[3][1] * mt[1][2] * mt[2][3] - mt[3][1] * mt[1][3] * mt[2][2]) / determinant;
	m_matrix.mt[0][1] = (-mt[0][1] * mt[2][2] * mt[3][3] + mt[0][1] * mt[2][3] * mt[3][2] + mt[2][1] * mt[0][2] * mt[3][3] - mt[2][1] * mt[0][3] * mt[3][2] - mt[3][1] * mt[0][2] * mt[2][3] + mt[3][1] * mt[0][3] * mt[2][2]) / determinant;
	m_matrix.mt[0][2] = (mt[0][1] * mt[1][2] * mt[3][3] - mt[0][1] * mt[1][3] * mt[3][2] - mt[1][1] * mt[0][2] * mt[3][3] + mt[1][1] * mt[0][3] * mt[3][2] + mt[3][1] * mt[0][2] * mt[1][3] - mt[3][1] * mt[0][3] * mt[1][2]) / determinant;
	m_matrix.mt[0][3] = (-mt[0][1] * mt[1][2] * mt[2][3] + mt[0][1] * mt[1][3] * mt[2][2] + mt[1][1] * mt[0][2] * mt[2][3] - mt[1][1] * mt[0][3] * mt[2][2] - mt[2][1] * mt[0][2] * mt[1][3] + mt[2][1] * mt[0][3] * mt[1][2]) / determinant;
	m_matrix.mt[1][0] = (-mt[1][0] * mt[2][2] * mt[3][3] + mt[1][0] * mt[2][3] * mt[3][2] + mt[2][0] * mt[1][2] * mt[3][3] - mt[2][0] * mt[1][3] * mt[3][2] - mt[3][0] * mt[1][2] * mt[2][3] + mt[3][0] * mt[1][3] * mt[2][2]) / determinant;
	m_matrix.mt[1][1] = (mt[0][0] * mt[2][2] * mt[3][3] - mt[0][0] * mt[2][3] * mt[3][2] - mt[2][0] * mt[0][2] * mt[3][3] + mt[2][0] * mt[0][3] * mt[3][2] + mt[3][0] * mt[0][2] * mt[2][3] - mt[3][0] * mt[0][3] * mt[2][2]) / determinant;
	m_matrix.mt[1][2] = (-mt[0][0] * mt[1][2] * mt[3][3] + mt[0][0] * mt[1][3] * mt[3][2] + mt[1][0] * mt[0][2] * mt[3][3] - mt[1][0] * mt[0][3] * mt[3][2] - mt[3][0] * mt[0][2] * mt[1][3] + mt[3][0] * mt[0][3] * mt[1][2]) / determinant;
	m_matrix.mt[1][3] = (mt[0][0] * mt[1][2] * mt[2][3] - mt[0][0] * mt[1][3] * mt[2][2] - mt[1][0] * mt[0][2] * mt[2][3] + mt[1][0] * mt[0][3] * mt[2][2] + mt[2][0] * mt[0][2] * mt[1][3] - mt[2][0] * mt[0][3] * mt[1][2]) / determinant;
	m_matrix.mt[2][0] = (mt[1][0] * mt[2][1] * mt[3][3] - mt[1][0] * mt[2][3] * mt[3][1] - mt[2][0] * mt[1][1] * mt[3][3] + mt[2][0] * mt[1][3] * mt[3][1] + mt[3][0] * mt[1][1] * mt[2][3] - mt[3][0] * mt[1][3] * mt[2][1]) / determinant;
	m_matrix.mt[2][1] = (-mt[0][0] * mt[2][1] * mt[3][3] + mt[0][0] * mt[2][3] * mt[3][1] + mt[2][0] * mt[0][1] * mt[3][3] - mt[2][0] * mt[0][3] * mt[3][1] - mt[3][0] * mt[0][1] * mt[2][3] + mt[3][0] * mt[0][3] * mt[2][1]) / determinant;
	m_matrix.mt[2][2] = (mt[0][0] * mt[1][1] * mt[3][3] - mt[0][0] * mt[1][3] * mt[3][1] - mt[1][0] * mt[0][1] * mt[3][3] + mt[1][0] * mt[0][3] * mt[3][1] + mt[3][0] * mt[0][1] * mt[1][3] - mt[3][0] * mt[0][3] * mt[1][1]) / determinant;
	m_matrix.mt[2][3] = (-mt[0][0] * mt[1][1] * mt[2][3] + mt[0][0] * mt[1][3] * mt[2][1] + mt[1][0] * mt[0][1] * mt[2][3] - mt[1][0] * mt[0][3] * mt[2][1] - mt[2][0] * mt[0][1] * mt[1][3] + mt[2][0] * mt[0][3] * mt[1][1]) / determinant;
	m_matrix.mt[3][0] = (-mt[1][0] * mt[2][1] * mt[3][2] + mt[1][0] * mt[2][2] * mt[3][1] + mt[2][0] * mt[1][1] * mt[3][2] - mt[2][0] * mt[1][2] * mt[3][1] - mt[3][0] * mt[1][1] * mt[2][2] + mt[3][0] * mt[1][2] * mt[2][1]) / determinant;
	m_matrix.mt[3][1] = (mt[0][0] * mt[2][1] * mt[3][2] - mt[0][0] * mt[2][2] * mt[3][1] - mt[2][0] * mt[0][1] * mt[3][2] + mt[2][0] * mt[0][2] * mt[3][1] + mt[3][0] * mt[0][1] * mt[2][2] - mt[3][0] * mt[0][2] * mt[2][1]) / determinant;
	m_matrix.mt[3][2] = (-mt[0][0] * mt[1][1] * mt[3][2] + mt[0][0] * mt[1][2] * mt[3][1] + mt[1][0] * mt[0][1] * mt[3][2] - mt[1][0] * mt[0][2] * mt[3][1] - mt[3][0] * mt[0][1] * mt[1][2] + mt[3][0] * mt[0][2] * mt[1][1]) / determinant;
	m_matrix.mt[3][3] = (mt[0][0] * mt[1][1] * mt[2][2] - mt[0][0] * mt[1][2] * mt[2][1] - mt[1][0] * mt[0][1] * mt[2][2] + mt[1][0] * mt[0][2] * mt[2][1] + mt[2][0] * mt[0][1] * mt[1][2] - mt[2][0] * mt[0][2] * mt[1][1]) / determinant;
}


CMatrix CMatrix::Translate4d(double dx, double dy, double dz)
{
	CMatrix tmp(4);
	tmp[0][0] = 1; tmp[0][1] = 0; tmp[0][2] = 0; tmp[0][3] = dx;
	tmp[1][0] = 0; tmp[1][1] = 1; tmp[1][2] = 0; tmp[1][3] = dy;
	tmp[2][0] = 0; tmp[2][1] = 0; tmp[2][2] = 1; tmp[2][3] = dz;
	tmp[3][0] = 0; tmp[3][1] = 0; tmp[3][2] = 0; tmp[3][3] = 1;
	return (tmp);
}


CMatrix CMatrix::Rotate4d(double Angle, double vx, double vy, double vz)
{
	CMatrix tmp(4);
	double v[3];
	v[0] = vx / sqrt(vx*vx + vy * vy + vz * vz);
	v[1] = vy / sqrt(vx*vx + vy * vy + vz * vz);
	v[2] = vz / sqrt(vx*vx + vy * vy + vz * vz);

	tmp[0][0] = v[0] * v[0] * (1 - cos(Angle)) + cos(Angle);
	tmp[0][1] = v[0] * v[1] * (1 - cos(Angle)) - v[2] * sin(Angle);
	tmp[0][2] = v[0] * v[2] * (1 - cos(Angle)) + v[1] * sin(Angle);

	tmp[1][0] = v[0] * v[1] * (1 - cos(Angle)) + v[2] * sin(Angle);
	tmp[1][1] = v[1] * v[1] * (1 - cos(Angle)) + cos(Angle);
	tmp[1][2] = v[2] * v[1] * (1 - cos(Angle)) - v[0] * sin(Angle);

	tmp[2][0] = v[0] * v[2] * (1 - cos(Angle)) - v[1] * sin(Angle);
	tmp[2][1] = v[1] * v[2] * (1 - cos(Angle)) + v[0] * sin(Angle);
	tmp[2][2] = v[2] * v[2] * (1 - cos(Angle)) + cos(Angle);

	tmp[0][3] = 0; tmp[1][3] = 0; tmp[2][3] = 0;
	tmp[3][0] = 0; tmp[3][1] = 0; tmp[3][2] = 0; tmp[3][3] = 1;
	return (tmp);
}


CMatrix CMatrix::Scale4d(double scaleX, double scaleY, double scaleZ)
{
	CMatrix tmp(4);
	tmp[0][0] = scaleX;	tmp[0][1] = 0;	  tmp[0][2] = 0;      tmp[0][3] = 0;
	tmp[1][0] = 0;		tmp[1][1] = scaleY; tmp[1][2] = 0;      tmp[1][3] = 0;
	tmp[2][0] = 0;		tmp[2][1] = 0;      tmp[2][2] = scaleZ; tmp[2][3] = 0;
	tmp[3][0] = 0;		tmp[3][1] = 0;      tmp[3][2] = 0;      tmp[3][3] = 1;
	return (tmp);
}