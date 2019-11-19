#pragma once
#include "..//ProjectIncludes/ProjectIncludes_Header.h"
#include "..//DataAccumulate/DataAccumulate.h"
class Painter
{
public:
	Painter();
	virtual ~Painter();

	//draw movement Arrow
	void drawMovmentArrow(Mat &img, const pair<int, int> &movement);

public:

	//Draw detected GREEN or RED point
	void drawGreenRedDetectorPoint(Mat &srcImg, Scalar color = COLOR_RED);

	//Draw X/Y axes
	void draw_X_Y_axes(Mat &src);

	//Draw roi Board
	void drawRoiBoard(Mat &imgSrc, float  start_point_offset_x, float start_point_offset_y, float roiWidth_X, float roiHeight_Y);

	//draw matches if exist
	

	//Draw vector of Point2F points
	void drawVectorOfPoint2F(const vector<Point2f>& srcPoints, Mat &imgForDrawing, Scalar color = Scalar(0, 0, 255));

	//draw matches 
	void DrawMatches(Mat &img, DataAccumulate &dataAccumulate);

	//draw Body of polygon
	void drawPoligonBody(Mat &img, const vector<Point2f> &points, Scalar color = Scalar(0, 0, 255));

	//draw triangle
	void DrawTriangle(Mat &img, vector<Point2f> &newTrianglePoints);

};

