#include "RT_DataBinding.h"




//step 4
void RT_DataBinding::drawQueueFromStack(Mat &dst)
{
	while (!tempPointsStack.empty())
	{
		Point2f temp(tempPointsStack.top());

		circle(dst, temp, 2, COLOR_RED, 1, LineTypes::LINE_AA, 0);
		tempPointsStack.pop();
	}
}

//step 3
void RT_DataBinding::checkPointPosition(Point2f &privPoint, const Point2f &currPoint, const int &X, const int &Y)
{
	if ((X < currPoint.x) || (Y < currPoint.y) || (currPoint.x < 0) || (currPoint.y < 0))
	{
		//point is not in range
		return;
	}
	double dist = 0.0;
	mathCalculations.GetDistanceBetweenPoints(privPoint, currPoint, dist);

	if (dist >= MINIMAL_DIST)
	{
		mathCalculations.GetDistanceBetweenPoints(lastTriangleGeometricCenter, currPoint, dist);
		if (dist <= MAXIMAL_DIST)
		{
			lastPointsQueue.push(currPoint);
			privPoint.x = currPoint.x;
			privPoint.y = currPoint.y;
		}
		tempPointsStack.push(currPoint);

		return;
	}
	lastPointsQueue.push(currPoint);

	return;

}
//step 2
void RT_DataBinding::updateQueue(const pair< int, int > &newDelta, int X, int Y)
{
	if (!lastPointsQueue.empty())
	{
		int size = (int)lastPointsQueue.size();

		Point2f privPoint(lastTriangleGeometricCenter);

		int i = (lastAngle > 0) ? POSITIVE_ONE : NEGATIVE_ONE;

		int element_X = newDelta.first;
		int element_Y = newDelta.second;

		float tempLastAngle = abs(lastAngle);
		if (tempLastAngle <= 90 || tempLastAngle >= 270)
		{
			swap(element_X, element_Y);
			element_X *= NEGATIVE_ONE;
		}

		while (size > 0)
		{
			Point2f currPoint(lastPointsQueue.front());

			currPoint.x += i * newDelta.first;
			currPoint.y += i * newDelta.second;

			checkPointPosition(privPoint, currPoint, X, Y);//good / bed point

			if (!lastPointsQueue.empty())
				lastPointsQueue.pop();
			size--;
		}
	}


}

//step 1
void RT_DataBinding::drawQueue(const pair<int, int > &newDelta, Mat &dst)
{
	int X = dst.cols;
	int Y = dst.rows;
	//step 2
	updateQueue(newDelta, X, Y);

	//step 3
	drawQueueFromStack(dst);
}

//we need this for calc last points changing
//Step B.2 
void  RT_DataBinding::getDeltaCenter(const pair<int, int> &direction )
{
	float x = MATRIX_SCENE_X[direction.first][direction.second];
	float y = MATRIX_SCENE_Y[direction.first][direction.second];

	deltaCenter = make_pair<int, int>((int)x, (int)y);

}


//get correct points ,
//and calc triangles geometric center
//Step B.1
void RT_DataBinding::getTriangle_GeometricCent_Points(float angle, float height, vector<Point2f> &trianglePointsVector, Point2f &triangle_geometric_center)
{
	triangle.TriangleCalculations(angle, trianglePointsVector, triangle_geometric_center);

	if ((last.x == 0.0F) && (last.y == 0.0F))//first point
	{
		last = triangle_geometric_center;
	}
	if (lastAngle != 0.0F)
	{
		float dif = angle - lastAngle;
		if (abs(dif) >= 2.0F) //minimal dist between points
		{
			if ((int)lastPointsQueue.size() < LAST_POINTS_QUEUE_SIZE)
			{
				lastPointsQueue.push(triangle_geometric_center);
				lastHeight = height;
			}
		}
	}

}


//update screen matrix 
//Step A.2
void RT_DataBinding::updateBlackScreen(float angle, float height)
{
	tempBlack.release();
	tempDown.release();

	Mat newMatrix(SCENE_3D_SIZE_W, SCENE_3D_SIZE_H, CV_64FC3, COLOR_BLACK);
	tempBlack = newMatrix.clone();
	tempDown = newMatrix.clone();
	
}


//insert new data to binding
//Step A.1
void RT_DataBinding::InsertDataForBinding(float angle, float height, pair<int, int> direction)
{
	//Step A.2
	updateBlackScreen(angle, height);
	
	Point2f triangle_geometric_center(0, 0);
	vector<Point2f> trianglePointsVector;

	//Step B.1
	getTriangle_GeometricCent_Points(angle, height, trianglePointsVector, triangle_geometric_center);

	painter.drawPoligonBody(tempBlack, trianglePointsVector, COLOR_YELLOW);
	circle(tempDown, triangle_geometric_center, 5, COLOR_GREEN, 2, 2, 0);

	lastTriangleGeometricCenter = triangle_geometric_center;

	circle(tempBlack, triangle_geometric_center, 5, COLOR_ORANGE, 2, 2, 0);
	painter.draw_X_Y_axes(tempDown);
	lastAngle = angle;
	getDeltaCenter(direction);

	drawQueue(deltaCenter, tempDown);

	sceneMotion.Convert2D_to_3D(tempBlack, tempDown, angle, lastHeight);

}



RT_DataBinding::RT_DataBinding()
{
}


RT_DataBinding::~RT_DataBinding()
{
}


