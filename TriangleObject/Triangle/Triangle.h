#pragma once
#include "..\..\ProjectIncludes\ProjectIncludes_Header.h"
#include "..\SmartPoint\SmartPoint.h"

class Triangle
{

	Point2f geometric_center;
	SmartPoint trianglePoints[3];

public:
	Triangle();

	virtual ~Triangle();

private:
	//update triangle geometric center point 
	//Step A.2
	void updateGeometric_center();

	//init triangle data
	//Step A.1
	void init();

	//we need calculate 2 points of triangle
	//Step B.2
	void moveSinglePointOfTriangle(float angle, SmartPoint &originTrianglePoint, Point2f &result);

public:

	//insert new rotate and translate params
	//Step B.1
	void TriangleCalculations(float angle, vector<Point2f> &newTrianglePoints);

	//insert new rotate and translate params
	//Step B.1.2
	void TriangleCalculations(float angle, vector<Point2f> &newTrianglePoints, Point2f &geometric_center);
};

