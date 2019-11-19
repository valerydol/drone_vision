#pragma once
#include "..\ProjectIncludes\ProjectIncludes_Header.h"

class MathCalculations
{


public:
	MathCalculations();
	virtual ~MathCalculations();


	//return distance btween 2 points
	void GetDistanceBetweenPoints(const Point2f &pointA, const Point2f &pointB, double &distance);
	void GetDistanceBetweenPoints(const Point2f &pointA, const Point2f &pointB, float &distance);

	//return delta angle
	float GetPositiveDeltaBetween2Angles(const float &corrAngle, const float &lastAngle);

private:
	void getDifferenceBetweenPoints(const Point2f &pointA, const Point2f &pointB, Point2f &result);

public:
	//return angle btween 2 points in degrees
	//Step A.1
	float CalculateAngleBetween2Points2fInDegree(const Point2f &A, const Point2f &B);

private:
	//convert Angle to direction arrow
	//convert from degrees to Sobal mat position
	//return pair of X,Y in SOBaL matrix
	//step B.1 
	pair<int, int>convertFromAngleToMoveArrow(float angle);

public:

	//set 2 points and get  pair of X,Y in SOBAL matrix
	//(this step consist of STEPS A and B)
	//Step C
	pair<int, int> Get_X_Y_inDirectionMatrix(const Point2f &A,  const Point2f &B);

	//method can return mid point of line
	void GetMiddleOfLine(const Point2f &startPoint, const Point2f &endPoint, Point2f &result);

	//get width , height and you will get center point of RECTANGLE ONLY
	void GetCenterPointOfFrame(const float &width, const float& height, Point2f &centerFramePoint);

	void GetVectorDirectionFrom2Points(const Point2f& from, const Point2f &to, Point2f &result);

	//nomalize vector
	void vectorNormalization(const Point2f &vector, Vec2f& nomVector);

	

};

