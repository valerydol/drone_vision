#pragma once
#include "..\..\ProjectIncludes\ProjectIncludes_Header.h"
#include "..\DirectionArrow\DirectionArrow.h"
#include "..\HeightCalculations\HeightCalculations.h"
#include "..\RotationProcessing\RotationProcessing.h"
#include "..\PerspectiveCalculations\PerspectiveCalculations.h"
#include "..\..\DataAccumulate\DataAccumulate.h"
#include "..\OptimalDirection\OptimalDirection.h"
class PostProcessing
{
private:
	
	//can do before PerspectiveCalculations
	//step 0
	DirectionArrow directionArrow;

	//first of all we need PerspectiveCalculations
	//and then other things
	//step 1
	PerspectiveCalculations perspectiveCalculations;
	RotationProcessing rotationProcessing;
	HeightCalculations heightCalculations;
	OptimalDirection optimalDirection;

public:
	PostProcessing();
	virtual ~PostProcessing();

	//
	//Step A
	void SetDataToGetAngleDirectionHeight(DataAccumulate &dataAccumulate, float &_angle, float & _height, pair<int, int> &_direction);
};

