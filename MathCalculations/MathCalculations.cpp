#include "MathCalculations.h"



MathCalculations::MathCalculations()
{
}


MathCalculations::~MathCalculations()
{
}

float MathCalculations::GetPositiveDeltaBetween2Angles(const float &corrAngle, const float &lastAngle)
{
	float dif = corrAngle - lastAngle;
	dif = abs(dif);
	return dif;
}




void MathCalculations::getDifferenceBetweenPoints(const Point2f &pointA, const Point2f &pointB, Point2f &result)
{
	result = pointA - pointB;
}


//return distance between 2 points
void MathCalculations::GetDistanceBetweenPoints(const Point2f &pointA, const Point2f &pointB, double &distance)
{
	//Point2f difference = pointA - pointB;
	Point2f difference;
	getDifferenceBetweenPoints(pointA, pointB, difference);
	distance = sqrt(difference.ddot(difference));

}

//return distance between 2 points
void MathCalculations::GetDistanceBetweenPoints(const Point2f &pointA, const Point2f &pointB, float &distance)
{
	double result = 0.0;
	GetDistanceBetweenPoints(pointA, pointB, result);
	distance = (float)result;

}

//return angle between 2 points in degrees
//Step A.1
float MathCalculations::CalculateAngleBetween2Points2fInDegree(const Point2f &A, const Point2f &B)
{
	//Point2f difference = A - B;
	//double distance = sqrt(difference.dot(difference));

	double distance = 0.0;

	GetDistanceBetweenPoints(A, B, distance);

	if ((distance <= 3.0) ||(distance >= 10.0))
		return 0.0F;

	//find  delta X and delta Y
	//step 1 
	float deltaX = (A.x);
	float deltaY = (A.y);

	//point new coordinats are
	//step 3
	Point2f scenePointNewPosition((B.x - deltaX), (B.y - deltaY));

	//step  4
	float r = hypotf(scenePointNewPosition.x, scenePointNewPosition.y);

	//find alpha
	//step 5 
	float param = (scenePointNewPosition.x / r);
	float result = (float)(acos(param) * 180.0F / (float)CV_PI);

	//find result
	//step 6
	result = (scenePointNewPosition.y > 0.0F) ? 360.0F - result : result;
//	result -= 180.0F;
//	result += 180.0F;

	return result;
}


//convert Angle to direction arrow
//convert from degrees to Sobal mat position
//step B.1 
pair<int, int>MathCalculations::convertFromAngleToMoveArrow(float angle)
{
	if (angle < 0.0F)
	{
		angle =360.0F + angle;
	}
	int res = (int)(angle / 15);

	if (res == 0) // <15 deg
	{
		return make_pair(2, 1);
	}
	if (res <= 4) // res >=15 && res <75
	{
		return make_pair(2, 0);
	}
	if (res <= 6) // res > 75 && res < 105
	{
		return make_pair(1, 0);
	}
	if (res <= 10) // res > 105 && res < 165
	{
		return make_pair(0, 0);
	}
	if (res <= 12) // res > 165 && res < 195
	{
		return make_pair(0, 1);
	}
	if (res <= 16) // res > 195 && res < 255
	{
		return make_pair(0, 2);
	}
	if (res <= 18) // res > 255 && res < 285
	{
		return make_pair(1, 2);
	}
	if (res <= 22) // res > 285 && res < 345
	{
		return make_pair(2, 2);
	}
	return make_pair(2, 1);
}

//set 2 points and get  pair of X,Y in SOBAL matrix
//this step consist of STEPS A and B 
//Step C 
pair<int, int> MathCalculations::Get_X_Y_inDirectionMatrix(const Point2f &A, const Point2f &B)
{
	//Step A
	float angle = CalculateAngleBetween2Points2fInDegree(A, B);

	//if step no movment, return 
	if (angle == 0.0F)
		return make_pair(1, 1);

	//Step B
	return convertFromAngleToMoveArrow(angle);
}

//method can return mid point of line
void  MathCalculations::GetMiddleOfLine(const Point2f &startPoint, const Point2f &endPoint, Point2f &result)
{
	result.x = (float)((startPoint.x + endPoint.x) / 2.0F);
	result.y = (float)((startPoint.y + endPoint.y) / 2.0F);
}

//get width , height and you will get center point of RECTANGLE ONLY
void MathCalculations::GetCenterPointOfFrame(const float &width, const float& height, Point2f &centerFramePoint)
{
	centerFramePoint.x = width / 2.0F;
	centerFramePoint.y = height / 2.0F;
}

//return direction vector
void  MathCalculations::GetVectorDirectionFrom2Points(const Point2f& from, const Point2f &to, Point2f &result)
{
	result.x = to.x - from.x;
	result.y = to.y - from.y;
}


//nomalize vector
void MathCalculations::vectorNormalization(const Point2f &vector, Vec2f& nomVector)
{
	//convert point 2f to vec2f 
	Vec2f convVector(vector.x, vector.y);

	//normalize vector
	nomVector = normalize(convVector);
}