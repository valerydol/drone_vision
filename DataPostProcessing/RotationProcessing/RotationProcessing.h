#pragma once

#include"..\..\ProjectIncludes\ProjectIncludes_Header.h"
#include "..\..\MathCalculations\MathCalculations.h"
#include "..\..\DataAccumulate\DataAccumulate.h"

class RotationProcessing
{
private:
	MathCalculations mathCalculations;
	float angle = 0;
	float lastAngle = 0;
	bool flag = false;
	float lastDeltaAngle = 0;

public:
	RotationProcessing();
	virtual ~RotationProcessing();

private:

	//we wont angle in range +- 359 degree
	//Step A.4
	void correctAngle();

	//calculate current angle
	//step A.3
	void calculateCurrentAngle(float tempAngleInRadians);

	//method return temp angle 
	//Step A.2 
	float getTempRotationAngleInRadians(const Point2f &centerPoint, const Point2f &roi_Mid, const Point2f &scen_Mid);
public:

	//return current rotation angle
	//Step A.1
	void GetRotationAngle(DataAccumulate &dataAccumulate, float &result);


};

