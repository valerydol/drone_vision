#pragma once
#include "..\\..\\ProjectIncludes\ProjectIncludes_Header.h"


class Scene3D
{

	

private:

	double rad2Deg(double rad) { return rad * ((double)180 / CV_PI); }//Convert radians to degrees
	double deg2Rad(double deg) { return deg * (CV_PI / (double)180); }//Convert degrees to radians

	//Step B.1
	void warpMatrix(Size sz, double theta, double phi, double gamma, double scale, double fovy, Mat& M, vector<Point2f>* corners, double zoom , double height , Position posit );

	//Step B.1.2
	void makeCorners(const Mat &src , Mat &dst , double ptsIn[], double ptsOut[], double  sideLength, Mat F, double halfW, double halfH);
	//
	//Step B.1.1
	void wrapTopDownMatrix(const Mat &srcTop, const Mat &srcDown , Mat& dstTop, Mat& dstDown, Size sz, double theta, double phi, double gamma, double scale, double fovy, double zoom, double height);

public:

	//Step A.1
	void WarpImage(const Mat &src, double theta, double phi, double gamma, double scale, double fovy, Mat& dst, double zoom , double height , Position posit );

	//faster method , using multithreading
	//Step A.1.1
	void WrapTopDownImages(const Mat &srcTop, const Mat &srcDown, double theta, double phi, double gamma, double scale, double fovy, Mat& dstTop, Mat& dstDown, double zoom, double height);
	
	Scene3D();
	virtual ~Scene3D();
};

