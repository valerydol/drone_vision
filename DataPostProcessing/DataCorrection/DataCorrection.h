#pragma once
#include "..\..\ProjectIncludes\ProjectIncludes_Header.h"
#include "..\..\TriangleObject\Triangle\Triangle.h"
class DataCorrection
{
	Point2f last;
	Point2f currentTriangleGeometricCenter;

	float lastAngle = 0.0F;

	float lastHeight = 0.0F;

	Point2f lastTriangleGeometricCenter;

	queue<Point2f> lastPointsQueue;
	stack<Point2f> tempPointsStack;

	Triangle triangle;

	//	vector<Point2f> trianglePointsVector;

private:
	//in this function we update stack
	//Step B.1
	void updateStack(float angle, float height);

public:
	//return triangle geometric center
//Step C.1 
	void GetTriangleGeometricCenterPoint(Point2f &triangle_geometric_center_dst);

	//return delta center point
	//Step B.1
	pair<int, int> GetDeltaCenterPoint(const pair<int, int> &direction);

	//lastPointsQueue
	//Step A.1
	void UpdateLastPointsStack( float angle, float height, vector<Point2f> &trianglePointsVector_dst);


	float GetLastHeight();

	DataCorrection();
	virtual ~DataCorrection();


};

