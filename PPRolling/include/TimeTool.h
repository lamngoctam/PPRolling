#pragma once
/************************************************************
*							*
*							*
*			programed by Kineri		*
*	program ver. 1.0 	2012.5.1		*
*************************************************************/
/*(Example)
	CTime T(2);
	T.CalcStartTime(0);
	T.CalcStartTime(1);

	T.CalcEndTime(0);
	T.CalcEndTime(1);

	T.OutputTime();
*/
#include <iostream>
#include <ctime>
#include <math.h>

class CTime
{
public:
	int count;
	clock_t*	start;
	clock_t*	end;
public:
	CTime() {};
	CTime(int num)
	{
		count = num;
		start = new clock_t[num];
		end = new clock_t[num];
	};

	~CTime()
	{
		delete[] start, end;
	};

	void CalcStartTime(int num)
	{
		start[num] = clock();
	};

	void CalcEndTime(int num)
	{
		end[num] = clock();
	};

	void OutputTime()
	{
		double Timer = 0.0;
		for (int i = 0; i < count; i++) {
			Timer = (double)(end[i] - start[i]) / CLOCKS_PER_SEC;
			if (Timer > 1.0e-5) {
				std::cout << "count [" << i << "]:" << Timer << " times" << std::endl;
			}
		}
	};

};