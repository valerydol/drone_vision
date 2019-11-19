#include "HeightCalculations.h"



HeightCalculations::HeightCalculations()
{
}


HeightCalculations::~HeightCalculations()
{
}

//base operations
//Step B.2
void HeightCalculations::updateData()
{
	count++;
	lastArea = corrArea;
	corrArea = 0.0;
}

//calculate Coefficient
//Step B.1
void HeightCalculations::calcCoefficient()
{

	if (lastArea == corrArea) //new roi
	{
		count = 0;
		count++;
		corrArea = 0.0;
		return;
	}

	//check if lastArea != 0
	//if lastArea == 0 set new lastArea and return 0
	if ((lastArea == 0.0) || (count == 1))
	{
		//step B.2
		updateData();
		return;
	}

	double dif = (corrArea - lastArea) / 100.0;

	if (corrArea < lastArea) //down
	{
		dif += -10.0;//negative result
		if (dif < -30.0)
		{
			dif = -4.0;

			if ((Height + dif) > 0.0)
				Height += (float)dif;
		}

		updateData();
	}
	else // if (corrArea > lastArea) //UP
	{
		if (dif < 15)
		{
			dif = 3.0;

			if (Height < 100.0F)
				Height += (float)dif;
		}

	}
	updateData();
}

//start calculate Height 
//and then return 
//Step A
float HeightCalculations::CalculateHeight(DataAccumulate &dataAccumulate, const float &_corrAngle)
{


	//check if perspective is not valide, return 0 
	//step A.0
	if (!isContourConvex(dataAccumulate.getSetVectorOfBoardSceneCorners_ref()))
	{
		return 0.0F;
	}

	double newArea = 0.0;

	corrAngle = _corrAngle;
	float dif = mathCalculations.GetPositiveDeltaBetween2Angles(corrAngle, lastAngle);
	if (dif > 5.0F)
	{
		lastAngle = corrAngle;
		return Height;
	}

	//calculate Roi and scene areas
	//step A.1
	corrArea = contourArea(dataAccumulate.getSetVectorOfBoardSceneCorners_ref(), false);

	//calculate Height 
	//step B
	calcCoefficient();
	//lastAngle = corrArea;
	lastAngle = corrAngle;
	return Height;
}

