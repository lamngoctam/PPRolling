#pragma once

/************************************************************
*	New!Linear3d					*
*							*
*	Linear3d					*
*							*
*	Point3d     CVector3d				*
*	NURBS CPoint3d                        		*
*							*
*	programed by Kineri				*
*	program ver. 1.0 	2012.5.1		*
*			ver. 1.1	2012.5.6	CMatrix             	*
*			ver. 1.2	2012.5.8	CPoint3d            	*
*************************************************************/
#define MACHINE_ERROR 1.0e-15
#pragma warning(disable : 4996)//about scanf

//Sparse-CMatrix
//#include "../Csparse3.0.1\cs.h"


#include "CPoint3d.h"
#include "CMatrix.h"
#include "TimeTool.h"


/*
	Point3d a,b,c;
	a = Point3d(0,0,0);
	b = Point3d(1,2,3);
	c = add3d(a,b);
	cout<<c.r[0]<<","<<c.r[1]<<","<<c.r[2]<<endl;


	CPoint3d a,b,c;
	a = Point3d(0,0,0);
	b = Point3d(1,2,3);
	c = a + b;
	cout<<c.x<<","<<c.y<<","<<c.z<<endl;


//NURBS (x,y,z)


	c += a;
	c -= b;


http://homepage2.nifty.com/well/Operator.html#SQUARE_BRACKET
Programing Place
http://www.geocities.jp/ky_webid/cpp/language/017.html


*/
