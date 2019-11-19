#pragma once
#include "..\ProjectIncludes\ProjectIncludes_Header.h"
#include"..\SceneGraphicMotion\SceneMotion\SceneMotion.h"
#include "..\DataPostProcessing\DataCorrection\DataCorrection.h"
#include"..\Painter\Painter.h"
#include "..\MathCalculations\MathCalculations.h"

class RT_DataBinding
{
	Point2f last;
	Painter painter;
	MathCalculations mathCalculations;

	pair<int, int> deltaCenter;
	Triangle triangle;
	SceneMotion sceneMotion;

	Mat tempBlack, tempDown;

	//we need decode pressed key
	//int can be ( -1 ) , this can thraw exception if we 
	//try find ascii code of(-1)
	//step A.1
	float lastAngle = 0.0F;


	float lastHeight = 0.0F;

	Point2f lastTriangleGeometricCenter;
	queue<Point2f> lastPointsQueue;
	stack<Point2f> tempPointsStack;

private:

	//step 4
	void drawQueueFromStack(Mat &dst);

	//step 3
	void checkPointPosition(Point2f &privPoint, const Point2f &currPoint, const int &X, const int &Y);

	//step 2
	void updateQueue(const pair<int, int > &newDelta, int X, int Y);

	//step 1
	void drawQueue(const pair<int, int > &newDelta, Mat &dst);





	//we need this for calc last points changing
	//Step B.2 
	void getDeltaCenter(const pair<int, int> &direction);



	//get correct points ,
	//and calc triangles geometric center
	//Step B.1
	void getTriangle_GeometricCent_Points(float angle, float height, vector<Point2f> &trianglePointsVector, Point2f &triangle_geometric_center);

	//update black img
	//Step A.1
	void updateBlackScreen(float angle, float height);
public:


	//insert new data to binding
	//Step A.1
	void InsertDataForBinding(float angle, float height, pair<int, int> direction);


	//void InsertDataForBinding(Mat otherImage,float imgHighe_from_zero,float angle, float height, pair<int, int> direction)
	RT_DataBinding();
	virtual ~RT_DataBinding();
};

