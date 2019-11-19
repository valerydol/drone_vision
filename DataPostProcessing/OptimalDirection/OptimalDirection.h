#pragma once
#include "..\..\ProjectIncludes\ProjectIncludes_Header.h"
class OptimalDirection
{
	enum axes{axe_X,axe_Y};

	int arr_x[3] = { 0,0,0 };
	int arr_y[3] = { 0,0,0 };


private :

	//set zeros in all arrays
	//Step D 
	void zeroAll();

	//Step C
	int getOptimalDirectionValue(axes axe);
public:

	//return optimal direction
	//Step B
	 pair<int, int> GetOptimalDirection();

	//Step A
	void SetDirection(const pair<int, int> &direct);


	OptimalDirection();
	virtual ~OptimalDirection();
};

