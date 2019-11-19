#pragma once
#include "..\..\ProjectIncludes\ProjectIncludes_Header.h"
//
class SmartPoint
{
	Point2f point;

public:
	SmartPoint(float x = 0 , float y = 0) :point(x , y){};

	SmartPoint( SmartPoint &rhPoint);

	virtual ~SmartPoint() {};

	//ANTI - CLOCKWISE ROTATION OF Point ABOUT ORIGIN
	// Rotate point ( degree )
	void Rotate(float _angle = 0);
	
	//Translate this point
	void Translate(float _x = 0, float _y = 0);
	
	//return point
	Point2f GetPoint()const;// { return point; }


	//return x
	float Get_X()const { return point.x; }

	//return y
	float Get_Y()const { return point.y; }

	//set point
	void SetPoint(const Point2f &_newPoint);

};

