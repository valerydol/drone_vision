#include "PointsProcessing.h"



PointsProcessing::PointsProcessing()
{
}


PointsProcessing::~PointsProcessing()
{
}



//get only shape points vector
//step B.0
void PointsProcessing::ConvertGoodPoints2F_to_ConvexHull(vector<Point2f>& src_dst_ConvexHullPoints, vector<int>& hull)
{
	//check if vector is not empty
	//step 1
	if (src_dst_ConvexHullPoints.empty())
	{
		return;
	}

	//convert vector points
	//step 2
	hull.clear();
	convexHull(Mat(src_dst_ConvexHullPoints), hull, true);

}


//convert one specific point from ROI coordinates to GLOBAL coordinates
//step A.1
void PointsProcessing::ConvertOnePoint(const Point2f &pointSrc, Point2f &pointDst, float offset_roi_x, float offset_roi_y)
{
	pointDst.x = pointSrc.x;
	pointDst.x += offset_roi_x;
	pointDst.y = pointSrc.y;
	pointDst.y += offset_roi_y;
}

//convert ROI vector from local to global points
//Step A.0
void PointsProcessing::ConvertRoiPointsInVector(const vector<Point2f> &good_Points2F_obj_roi, vector<Point2f> &good_Points2F_obj_new_coordinates, float offset_roi_x, float offset_roi_y)
{
	//check if vector is not empty
	//step 1
	if (good_Points2F_obj_roi.empty())
	{
		return;
	}
	int size = (int)good_Points2F_obj_roi.size();
	//resize new_coordinates vector steps 2 - 3

	//clear vector
	//step 2
	if (!good_Points2F_obj_new_coordinates.empty())
	{
		good_Points2F_obj_new_coordinates.clear();
	}

	//set new vector size
	//step 3
	good_Points2F_obj_new_coordinates.resize(good_Points2F_obj_roi.size());

	//convert step by step points
	//step 4
	for (int i = 0; i < size; i++)
	{
		//Point2f point;
		//step A.1
		ConvertOnePoint(good_Points2F_obj_roi[i], good_Points2F_obj_new_coordinates[i], offset_roi_x, offset_roi_y);

	}
}