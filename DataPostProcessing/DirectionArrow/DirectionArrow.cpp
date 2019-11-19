#include "DirectionArrow.h"



DirectionArrow::DirectionArrow()
{
}


DirectionArrow::~DirectionArrow()
{
}


//set 2 points and get Arrow
//step A 
pair<int, int> DirectionArrow::GetDirectionArrow(const Point2f A, const Point2f B)
{
	return mathCalculations.Get_X_Y_inDirectionMatrix(A, B);
}