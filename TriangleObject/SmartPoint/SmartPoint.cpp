#include "SmartPoint.h"



SmartPoint::SmartPoint( SmartPoint &rhPoint)
	:point(0, 0)
{
	SetPoint(rhPoint.GetPoint());
}



//ANTI - CLOCKWISE ROTATION OF Point ABOUT ORIGIN
// Rotate point ( degree )
void SmartPoint::Rotate(float _angle)
{
	//cout << _angle << endl;
	float xTemp = point.x;
	float yTemp = point.y;
	float theta = (float)( ((float)_angle )* CV_PI / 180.0F);

	float c = cos(theta);
	float s = sin(theta);

	point.x = xTemp * c - yTemp * s;
	point.y = xTemp * s + yTemp * c;
}

Point2f SmartPoint::GetPoint()const
{
	return point;
}


//Translate this point
void SmartPoint::Translate(float _x, float _y)
{
	point.x += _x;
	point.y += _y;
}

//set point
void SmartPoint::SetPoint(const Point2f &_newPoint)
{
	point.x = _newPoint.x;
	point.y = _newPoint.y;

}
