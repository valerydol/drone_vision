#include "Painter.h"



Painter::Painter()
{
}


Painter::~Painter()
{
}

void Painter::DrawTriangle(Mat &img, vector<Point2f> &newTrianglePoints)
{
	//check points in vector
	if (newTrianglePoints.empty())
		return;

	//get vector size
	int size = (int)newTrianglePoints.size();


	Point2f delta(-30, 100);
	for (int i = 0; i < size; i++)
	{
		int nextIndex = ((i + 1) % size);
		line(img, newTrianglePoints[i]+ delta, newTrianglePoints[nextIndex] + delta, COLOR_YELLOW, 1);
		circle(img, newTrianglePoints[i] + delta, 3, COLOR_GREEN, 1, LINE_AA);
		circle(img, newTrianglePoints[nextIndex] + delta, 3, COLOR_GREEN, 1, LINE_AA);
	}
}

//draw movment Arrow
void Painter::drawMovmentArrow(Mat &img, const pair<int, int> &movement)
{
	float x =(float) MATRIX_SCENE_X[movement.first][movement.second];
	float y = (float)MATRIX_SCENE_Y[movement.first][movement.second];

	Point newPoint(ARROW_START_POINT.x + ARROW_LEN * x, ARROW_START_POINT.y + ARROW_LEN * y);
	arrowedLine(img, ARROW_START_POINT, newPoint, COLOR_YELLOW, 2, LINE_AA);
	putText(img, "Your Direction", Point(30, 20), FONT_HERSHEY_PLAIN, 1, COLOR_WHITE);

}


//Draw X/Y axes
void  Painter::draw_X_Y_axes(Mat &src)
{
	if (src.empty())
		return;
	putText(src, "Y", Point2f(15, (float)(src.rows - 10)), FONT_HERSHEY_PLAIN, 1, COLOR_GREEN, 1, 1);
	putText(src, "0", Point2f(10.0F, 10.0F), FONT_HERSHEY_PLAIN, 1, COLOR_WHITE, 1, 1);
	putText(src, "X", Point2f((float)(src.cols - 20), 25.0F), FONT_HERSHEY_PLAIN, 1, COLOR_RED, 1,LINE_4);
	arrowedLine(src, Point2f(20.0F, 20.0F), Point2f(20, (float)(src.rows- 30)), COLOR_GREEN, 1, LineTypes::LINE_4);
	arrowedLine(src, Point2f(20.0F, 20.0F), Point2f((float)(src.cols- 30), 20.0F), COLOR_RED, 1,LineTypes::LINE_AA);
}


//Draw roi Board
void  Painter::drawRoiBoard(Mat &imgSrc, float  start_point_offset_x, float start_point_offset_y, float roiWidth_X, float roiHeight_Y)
{

	float end_point_offset_x = roiWidth_X + start_point_offset_x;
	float end_point_offset_y = roiHeight_Y + start_point_offset_y;

	line(imgSrc, Point2f(start_point_offset_x, start_point_offset_y), Point2f(end_point_offset_x, start_point_offset_y), COLOR_PURPLE, 1);
	line(imgSrc, Point2f(end_point_offset_x, start_point_offset_y), Point2f(end_point_offset_x, end_point_offset_y), COLOR_PURPLE, 1);
	line(imgSrc, Point2f(start_point_offset_x, end_point_offset_y), Point2f(end_point_offset_x, end_point_offset_y), COLOR_PURPLE, 1);
	line(imgSrc, Point2f(start_point_offset_x, end_point_offset_y), Point2f(start_point_offset_x, start_point_offset_y), COLOR_PURPLE, 1);
}


//Draw detected GREEN or RED point
void Painter::drawGreenRedDetectorPoint(Mat &srcImg, Scalar color)
{
	circle(srcImg, Point2f(10, 10), 5, color, FILLED, LINE_AA);
}


//Draw vector of Point2F points
void Painter::drawVectorOfPoint2F(const vector<Point2f>& srcPoints, Mat &imgForDrawing, Scalar color)
{
	// if no good points2f return
	if (srcPoints.empty())
	{
		return;
	}

	int size = (int)srcPoints.size();
	for (int i = 0; i < size; i++)
	{
		circle(imgForDrawing, srcPoints[i], 3, color, 1, LINE_AA);
	}
}




//draw matches if exist
void Painter::DrawMatches(Mat &img, DataAccumulate &dataAccumulate)
{
	if (dataAccumulate.GetScene_GoodPoint2F_vector_ref().empty())
	{
		return;//no matches
	}
	//we have matching
	drawVectorOfPoint2F(dataAccumulate.GetRoi_GoodPoint2F_new_coordinates_vector_ref(), img, COLOR_GREEN);
	drawVectorOfPoint2F(dataAccumulate.GetScene_GoodPoint2F_vector_ref(), img, COLOR_RED);


	drawGreenRedDetectorPoint(img, COLOR_GREEN);
	vector<Point2f> roi = dataAccumulate.GetRoi_GoodPoint2F_new_coordinates_vector_ref();
	vector<Point2f> scene = dataAccumulate.GetScene_GoodPoint2F_vector_ref();

	for (int i = 0; i < (int)scene.size(); i++)
	{
		line(img, roi[i], scene[i], COLOR_WHITE, 1);
		circle(dataAccumulate.GetRoiCropImg_ref(), dataAccumulate.GetRoi_GoodPoint2F_vector_ref()[0], 3, COLOR_GREEN, 1, LINE_AA);


	}
}


//draw Body of polygone 
void Painter::drawPoligonBody(Mat &img, const vector<Point2f> &points, Scalar color)
{
	//check points in vector
	if (points.empty())
		return;

	//get vector size
	int size = (int)points.size();

	

	for (int i = 0; i < size; i++)
	{
		int nextIndex = ((i + 1) % size);
		line(img, points[i],points[nextIndex], color, 1);
		circle(img, points[i], 3, color, 1, LINE_AA);
		circle(img, points[nextIndex], 3, color, 1, LINE_AA);
	}
}