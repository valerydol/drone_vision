#pragma once
#include "..\ProjectIncludes\ProjectIncludes_Header.h"


class PointsProcessing
{

public:
	//get only shape points vector
	//step B.0
	void ConvertGoodPoints2F_to_ConvexHull(vector<Point2f>& src_dst_ConvexHullPoints , vector<int>& hull);

private:
	//convert one specific point from ROI coordinates to GLOBAL coordinates
	//step A.1
	void ConvertOnePoint(const Point2f &pointSrc, Point2f &pointDst, float offset_roi_x, float offset_roi_y);

public:
	//convert ROI vector from local to global points
	//Step A.0
	void ConvertRoiPointsInVector(const vector<Point2f> &good_Points2F_obj_roi, vector<Point2f> &good_Points2F_obj_new_coordinates, float offset_roi_x, float offset_roi_y);

	PointsProcessing();
	virtual ~PointsProcessing();
};

