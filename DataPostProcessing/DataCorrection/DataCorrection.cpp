#include "DataCorrection.h"


void DataCorrection::updateStack( float angle, float height)
{
	

	if ((last.x == 0.0F) && (last.y == 0.0F))
	{
		last = currentTriangleGeometricCenter;
	}
	if (lastAngle != 0.0F)
	{

		float dif = angle - lastAngle;
		if (abs(dif) >= 2.0F)
		{
			if ((int)lastPointsQueue.size() < LAST_POINTS_QUEUE_SIZE)
			{
				lastPointsQueue.push(currentTriangleGeometricCenter);
				lastHeight = height;
			}
		}
	}

	lastTriangleGeometricCenter = currentTriangleGeometricCenter;

	lastAngle = angle;
}

//return triangle geometric center
//Step C.1 
void DataCorrection::GetTriangleGeometricCenterPoint(Point2f &triangle_geometric_center_dst)
{
	triangle_geometric_center_dst = lastTriangleGeometricCenter;
}


//return delta center point
//Step B.1
pair<int, int> DataCorrection::GetDeltaCenterPoint(const pair<int, int> &direction)
{
	float x = MATRIX_SCENE_X[direction.first][direction.second];
	float y = MATRIX_SCENE_Y[direction.first][direction.second];
	return make_pair<int, int>((int)x, (int)y);
}



//
//Step A.1
void DataCorrection::UpdateLastPointsStack(  float angle, float height, vector<Point2f> &trianglePointsVector_dst)
{
	//Point2f triangle_geometric_center(0, 0);
	//vector<Point2f> trianglePointsVector;
	
	triangle.TriangleCalculations(angle, trianglePointsVector_dst, currentTriangleGeometricCenter);
	updateStack(angle, height);


}


float  DataCorrection::GetLastHeight()
{
	return lastHeight;
}
DataCorrection::DataCorrection()
:last(0.0F, 0.0F), currentTriangleGeometricCenter(0.0F, 0.0F)
{
}


DataCorrection::~DataCorrection()
{
}

