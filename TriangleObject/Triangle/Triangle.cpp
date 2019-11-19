#include "Triangle.h"


Triangle::Triangle()
	:geometric_center(0, 0)
{
	//step 1
	init();
}


Triangle::~Triangle()
{
}


//update triangle geometric center point 
//Step A.2
void Triangle::updateGeometric_center()
{
	geometric_center.x = 0;
	geometric_center.y = 0;
	for (int i = 0; i < 3; i++)
	{
		geometric_center.x += (trianglePoints[i].Get_X() / 3);
		geometric_center.y += (trianglePoints[i].Get_Y() / 3);
	}
}

//init triangle data
//Step A.1
void Triangle::init()
{
	//init triangle points
	trianglePoints[0].SetPoint(Point2f(TRIANGLE_MAIN_X, TRIANGLE_MAIN_Y));
	trianglePoints[1].SetPoint(Point2f(TRIANGLE_MAIN_X + TRIANGLE_MAIN_DELTA, 300 - TRIANGLE_MAIN_DELTA));
	trianglePoints[2].SetPoint(Point2f(TRIANGLE_MAIN_X - TRIANGLE_MAIN_DELTA, 300 - TRIANGLE_MAIN_DELTA));

	// calculate updateGeometric center of triangle
	//step A.2
	updateGeometric_center();
}

//insert new rotate and translate params
//Step B.1
void Triangle::TriangleCalculations(float angle, vector<Point2f> &newTrianglePoints)
{
	Point2f A, B, C;

	//create 3 threads ,for rotate every point of triangle
	//step 1
	//step B.2
	std::thread thread_A(&Triangle::moveSinglePointOfTriangle, this, angle, std::ref(trianglePoints[0]), std::ref(A));
	std::thread thread_B(&Triangle::moveSinglePointOfTriangle, this, angle, std::ref(trianglePoints[1]), std::ref(B));
	std::thread thread_C(&Triangle::moveSinglePointOfTriangle, this, angle, std::ref(trianglePoints[2]), std::ref(C));

	thread_A.join();
	thread_B.join();
	thread_C.join();

	//insert new triangle points to vector
	//step 2
	newTrianglePoints.push_back(A);
	newTrianglePoints.push_back(B);
	newTrianglePoints.push_back(C);

}

//insert new rotate and translate params
//Step B.1.2
void Triangle::TriangleCalculations(float angle, vector<Point2f> &newTrianglePoints, Point2f &_geometric_center)
{
	Point2f A, B, C;

	//create 3 threads ,for rotate every point of triangle
	//step 1
	//step B.2
	std::thread thread_A(&Triangle::moveSinglePointOfTriangle, this, angle, std::ref(trianglePoints[0]), std::ref(A));
	std::thread thread_B(&Triangle::moveSinglePointOfTriangle, this, angle, std::ref(trianglePoints[1]), std::ref(B));
	std::thread thread_C(&Triangle::moveSinglePointOfTriangle, this, angle, std::ref(trianglePoints[2]), std::ref(C));

	thread_A.join();
	thread_B.join();
	thread_C.join();

	//insert new triangle points to vector
	//step 2
	newTrianglePoints.push_back(A);
	newTrianglePoints.push_back(B);
	newTrianglePoints.push_back(C);
	_geometric_center = geometric_center;
}

//we need calculate 2 points of triangle
//Step B.2
void Triangle::moveSinglePointOfTriangle(float angle, SmartPoint &originTrianglePoint, Point2f &result)
{
	SmartPoint trianglePoint(originTrianglePoint);

	trianglePoint.Translate(-geometric_center.x, -geometric_center.y);

	trianglePoint.Rotate(angle);

	trianglePoint.Translate(geometric_center.x, geometric_center.y);

	result.x = trianglePoint.Get_X();
	result.y = trianglePoint.Get_Y();

}


