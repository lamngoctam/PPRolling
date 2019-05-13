#pragma once

#include "stdafx.h"

/*****************************************************************
glColor3dv(GetColor(CColor::magenta));
glColor3dv(GetColor(37));

CColor tmp;
tmp.ColorBar(value,max,min,PalettesCaseNumber,LinearFlag);
value:l, max,min
PalettesCaseNumber:RGB,
LinearFlag:

http://www.colordic.org/
http://ja.wikipedia.org/wiki/%E3%82%A6%E3%82%A7%E3%83%96%E3%82%AB%E3%83%A9%E3%83%BC
******************************************************************/

//###################################################//
//	CColor (RGB)								 //
//###################################################//
class CColor
{
public:
	double r;
	double g;
	double b;

	CColor();
	CColor(double R, double G, double B);
	void Set(double R, double G, double B);
	void SetGL(double R, double G, double B);
	void Clear();
	void Print();
	void ColorBar(double value, double max, double min, int PalettesCaseNumber = 0, bool LinearFlag = 1);

	static bool Less_r(const CColor& a, const CColor& b) { return a.r < b.r; };
	static bool Less_g(const CColor& a, const CColor& b) { return a.g < b.g; };
	static bool Less_b(const CColor& a, const CColor& b) { return a.b < b.b; };

	operator double*();
	//HTML
	enum Color_Name {

		indianred, lightcoral, salmon, darksalmon,
		lightsalmon, crimson, red, firebrick,
		darkred,
		/****** *****/
		pink, lightpink, hotpink, deeppink,
		mediumvioletred, palevioletred,
		/****** *****/
		coral, tomato, orangered, darkorange,
		orange,
		/******	*****/
		gold, yellow, lightyellow, lemonchiffon,
		lightgoldenrodyellow, papayawhip, moccasin,
		peachpuff, palegoldenrod, khaki, darkkhaki,
		/****** *****/
		lavender, thistle, plum, violet,
		orchid, fuchsia, magenta, mediumorchid,
		mediumpurple, amethyst, blueviolet, darkviolet,
		darkorchid, darkmagenta, purple, indigo,
		slateblue, darkslateblue, mediumslateblue,
		/***** *****/
		greenyellow, chartreuse, lawngreen, lime,
		limegreen, palegreen, lightgreen, mediumspringgreen,
		springgreen, mediumseagreen, seagreen,
		forestgreen, green, darkgreen, yellowgreen,
		olivedrab, olive, darkolivegreen,
		mediumaquamarine, darkseagreen,
		lightseagreen, darkcyan, teal,
		/*****  *****/
		aqua, cyan, lightcyan, paleturquoise,
		aquamarine, turquoise, mediumturquoise,
		darkturquoise, cadetblue, steelblue, lightsteelblue,
		powderblue, lightblue, skyblue, lightskyblue,
		deepskyblue, dodgerblue, cornflowerblue,
		royalblue, blue, mediumblue,
		darkblue, navy, midnightblue,
		/***** *****/
		cornsilk, blanchedalmond, bisque,
		navajowhite, wheat, burlywood, tan,
		rosybrown, sandybrown, goldenrod, darkgoldenrod,
		peru, chocolate, saddlebrown, sienna,
		brown, maroon,
		/*****  *****/
		white, snow, honeydew, mintcream,
		azure, aliceblue, ghostwhite, whitesmoke,
		seashell, beige, oldlace, floralwhite,
		ivory, antiquewhite, linen,
		lavenderblush, mistyrose,
		/***** *****/
		gainsboro, lightgrey, silver, darkgray,
		gray, dimgray, lightslategray,
		slategray, darkslategray, black,
		color_num	//F141
	}colorname;

private:
	CColor ConvertHSVtoRGB(double H, double S, double V, bool LinearFlag = 1);	//HSV-RGB
};



CColor GetColor(int ColorID);
