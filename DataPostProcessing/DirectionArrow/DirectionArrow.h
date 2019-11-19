#pragma once

#include "..\..\MathCalculations\MathCalculations.h"
#include "..\..\ProjectIncludes\ProjectIncludes_Header.h"
class DirectionArrow
{
private:
	MathCalculations mathCalculations;
public:
	DirectionArrow();
	virtual ~DirectionArrow();

	//set 2 points and get Arrow
	//step A 
	pair<int, int> GetDirectionArrow(const Point2f A, const Point2f B);
};

