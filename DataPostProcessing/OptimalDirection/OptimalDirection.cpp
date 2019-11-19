#include "OptimalDirection.h"


//set zeros in all arrays
//Step D 
void OptimalDirection::zeroAll()
{
	memset(arr_x, 0, sizeof(arr_x));
	memset(arr_y, 0, sizeof(arr_y));
}

//Step C
int OptimalDirection::getOptimalDirectionValue(axes axe)
{
	int index = 0;


	//int val = 0;
	if (axe == axe_X)
	{
		//val = max(max(arr_x[0], arr_x[1]), arr_x[2]);
		index = (arr_x[0] >= arr_x[1]) ? 0 : 1;
		index = (arr_x[index] >= arr_x[2]) ? index : 2;
	}
	else {
		//val = max(max(arr_y[0], arr_y[1]), arr_y[2]);
		index = (arr_y[0] >= arr_y[1]) ? 0 : 1;
		index = (arr_y[index] >= arr_y[2]) ? index : 2;
	}
	return index;
	//return val;
}

//return optimal direction
//Step B
pair<int, int> OptimalDirection::GetOptimalDirection()
{
	int x = getOptimalDirectionValue(axe_X);
	int y = getOptimalDirectionValue(axe_Y);
	zeroAll();

	return make_pair(x, y);
}


//Step A
void OptimalDirection::SetDirection(const pair<int, int> &direct)
{
	int x = direct.first;
	int y = direct.second;
	++(arr_x[x]);
	++(arr_y[y]);
}



OptimalDirection::OptimalDirection()
{
}


OptimalDirection::~OptimalDirection()
{
}


