#include "Scene3D.h"


//Step B.1
void Scene3D:: warpMatrix(Size sz, double theta, double phi, double gamma, double scale, double fovy, Mat &M, vector<Point2f>* corners, double zoom , double height , Position posit )
{
	double st = sin(deg2Rad(theta));
	double ct = cos(deg2Rad(theta));
	double sp = sin(deg2Rad(phi));
	double cp = cos(deg2Rad(phi));
	double sg = sin(deg2Rad(gamma));
	double cg = cos(deg2Rad(gamma));

	double halfFovy = fovy * 0.5;
	double d = hypot(sz.width, sz.height);
	double sideLength = scale * d / cos(deg2Rad(halfFovy));
	double h = (d / (2.0*sin(deg2Rad(halfFovy))) * zoom);
	double n = h - (d / 2.0);
	double f = h + (d / 2.0);

	Mat F = Mat(4, 4, CV_64FC1);//Allocate 4x4 transformation matrix F
	Mat Rtheta = Mat::eye(4, 4, CV_64FC1);//Allocate 4x4 rotation matrix around Z-axis by theta degrees
	Mat Rphi = Mat::eye(4, 4, CV_64FC1);//Allocate 4x4 rotation matrix around X-axis by phi degrees
	Mat Rgamma = Mat::eye(4, 4, CV_64FC1);//Allocate 4x4 rotation matrix around Y-axis by gamma degrees

	Mat T = Mat::eye(4, 4, CV_64FC1);//Allocate 4x4 translation matrix along Z-axis by -h units
	Mat P = Mat::zeros(4, 4, CV_64FC1);//Allocate 4x4 projection matrix

	//Rtheta
	Rtheta.at<double>(0, 0) = Rtheta.at<double>(1, 1) = ct;
	Rtheta.at<double>(0, 1) = -st; Rtheta.at<double>(1, 0) = st;
	//Rphi
	Rphi.at<double>(1, 1) = Rphi.at<double>(2, 2) = cp;
	Rphi.at<double>(1, 2) = -sp; Rphi.at<double>(2, 1) = sp;
	//Rgamma
	Rgamma.at<double>(0, 0) = Rgamma.at<double>(2, 2) = cg;
	Rgamma.at<double>(0, 2) = -sg; Rgamma.at<double>(2, 0) = sg;

	//T
	T.at<double>(2, 3) = -h;
	//P
	P.at<double>(0, 0) = P.at<double>(1, 1) = 1.0 / tan(deg2Rad(halfFovy));
	P.at<double>(2, 2) = -(f + n) / (f - n);
	P.at<double>(2, 3) = -(2.0*f*n) / (f - n);
	P.at<double>(3, 2) = -1.0;
	//Compose transformations
	F = P * T*Rphi*Rtheta*Rgamma;//Matrix-multiply to produce master matrix

	//Transform 4x4 points
	double ptsIn[4 * 3];
	double ptsOut[4 * 3];
	/*double halfW = sz.width / 2, halfH = sz.height / 2;*/
	double halfW = sz.width / 2, halfH = sz.height / 2;
	ptsIn[0] = -halfW; ptsIn[1] = halfH;
	ptsIn[3] = halfW; ptsIn[4] = halfH;
	ptsIn[6] = halfW; ptsIn[7] = -halfH;
	ptsIn[9] = -halfW; ptsIn[10] = -halfH;
//	int i = (posit == TOP )? 1 : -1;
	ptsIn[2] = ptsIn[5] = ptsIn[8] = ptsIn[11] =((double)posit  * height);//Set Z component to zero for all 4 components
	//ptsIn[2] = ptsIn[5] = ptsIn[8] = ptsIn[11] = 0;
	Mat ptsInMat(1, 4, CV_64FC3, ptsIn);
	Mat ptsOutMat(1, 4, CV_64FC3, ptsOut);

	perspectiveTransform(ptsInMat, ptsOutMat, F);//Transform points

	//Get 3x3 transform and warp image
	Point2f ptsInPt2f[4];
	Point2f ptsOutPt2f[4];

	for (int i = 0; i < 4; i++)
	{
		Point2f ptIn((float)ptsIn[i * 3 + 0], (float)ptsIn[i * 3 + 1]);
		Point2f ptOut((float)ptsOut[i * 3 + 0], (float)ptsOut[i * 3 + 1]);
		ptsInPt2f[i] = ptIn + Point2f((float)halfW, (float)halfH);
		ptsOutPt2f[i] = (ptOut + Point2f(1, 1))*(sideLength*0.5);
	}

	M = getPerspectiveTransform(ptsInPt2f, ptsOutPt2f);
	//Load corners vector
	if (corners)
	{
		corners->clear();
		corners->push_back(ptsOutPt2f[0]);//Push Top Left corner
		corners->push_back(ptsOutPt2f[1]);//Push Top Right corner
		corners->push_back(ptsOutPt2f[2]);//Push Bottom Right corner
		corners->push_back(ptsOutPt2f[3]);//Push Bottom Left corner
	}


}

void Scene3D::makeCorners(const Mat &src, Mat &dst, double ptsIn[], double ptsOut[], double  sideLength, Mat F, double halfW, double halfH)
{
	Mat ptsInMat(1, 4, CV_64FC3, ptsIn);
	Mat ptsOutMat(1, 4, CV_64FC3, ptsOut);
	Mat M;
	perspectiveTransform(ptsInMat, ptsOutMat, F);//Transform points
	vector<Point2f> corners;

	//Get 3x3 transform and warp image
	Point2f ptsInPt2f[4];
	Point2f ptsOutPt2f[4];

	for (int i = 0; i < 4; i++)
	{
		Point2f ptIn((float)ptsIn[i * 3 + 0], (float)ptsIn[i * 3 + 1]);
		Point2f ptOut((float)ptsOut[i * 3 + 0], (float)ptsOut[i * 3 + 1]);
		ptsInPt2f[i] = ptIn + Point2f((float)halfW, (float)halfH);
		ptsOutPt2f[i] = (ptOut + Point2f(1, 1))*(sideLength*0.5);
	}

	M = getPerspectiveTransform(ptsInPt2f, ptsOutPt2f);
	//Load corners vector
	if ((&corners))
	{
		corners.clear();
		corners.push_back(ptsOutPt2f[0]);//Push Top Left corner
		corners.push_back(ptsOutPt2f[1]);//Push Top Right corner
		corners.push_back(ptsOutPt2f[2]);//Push Bottom Right corner
		corners.push_back(ptsOutPt2f[3]);//Push Bottom Left corner
	}
	//finale step 
	warpPerspective(src, dst, M, Size((int)sideLength, (int)sideLength));//Do actual image warp
}



//
//Step B.1.1
void Scene3D::wrapTopDownMatrix(const Mat &srcTop, const Mat &srcDown, Mat& dstTop, Mat& dstDown, Size sz, double theta, double phi, double gamma, double scale, double fovy,   double zoom, double height)
{
	double st = sin(deg2Rad(theta));
	double ct = cos(deg2Rad(theta));
	double sp = sin(deg2Rad(phi));
	double cp = cos(deg2Rad(phi));
	double sg = sin(deg2Rad(gamma));
	double cg = cos(deg2Rad(gamma));

	double halfFovy = fovy * 0.5;
	double d = hypot(sz.width, sz.height);
	double sideLength = scale * d / cos(deg2Rad(halfFovy));
	double h = (d / (2.0*sin(deg2Rad(halfFovy))) * zoom);
	double n = h - (d / 2.0);
	double f = h + (d / 2.0);

	Mat F = Mat(4, 4, CV_64FC1);//Allocate 4x4 transformation matrix F
	Mat Rtheta = Mat::eye(4, 4, CV_64FC1);//Allocate 4x4 rotation matrix around Z-axis by theta degrees
	Mat Rphi = Mat::eye(4, 4, CV_64FC1);//Allocate 4x4 rotation matrix around X-axis by phi degrees
	Mat Rgamma = Mat::eye(4, 4, CV_64FC1);//Allocate 4x4 rotation matrix around Y-axis by gamma degrees

	Mat T = Mat::eye(4, 4, CV_64FC1);//Allocate 4x4 translation matrix along Z-axis by -h units
	Mat P = Mat::zeros(4, 4, CV_64FC1);//Allocate 4x4 projection matrix

	//Rtheta
	Rtheta.at<double>(0, 0) = Rtheta.at<double>(1, 1) = ct;
	Rtheta.at<double>(0, 1) = -st; Rtheta.at<double>(1, 0) = st;
	//Rphi
	Rphi.at<double>(1, 1) = Rphi.at<double>(2, 2) = cp;
	Rphi.at<double>(1, 2) = -sp; Rphi.at<double>(2, 1) = sp;
	//Rgamma
	Rgamma.at<double>(0, 0) = Rgamma.at<double>(2, 2) = cg;
	Rgamma.at<double>(0, 2) = -sg; Rgamma.at<double>(2, 0) = sg;

	//T
	T.at<double>(2, 3) = -h;
	//P
	P.at<double>(0, 0) = P.at<double>(1, 1) = 1.0 / tan(deg2Rad(halfFovy));
	P.at<double>(2, 2) = -(f + n) / (f - n);
	P.at<double>(2, 3) = -(2.0*f*n) / (f - n);
	P.at<double>(3, 2) = -1.0;
	//Compose transformations
	F = P * T*Rphi*Rtheta*Rgamma;//Matrix-multiply to produce master matrix

	//Transform 4x4 points
	double ptsInTop[4 * 3];
	double ptsOutTop[4 * 3];

	double ptsInDown[4 * 3];
	double ptsOutDown[4 * 3];

	double halfW = sz.width / 2, halfH = sz.height / 2;
	ptsInTop[0] = -halfW; ptsInTop[1] = halfH;
	ptsInTop[3] = halfW; ptsInTop[4] = halfH;
	ptsInTop[6] = halfW; ptsInTop[7] = -halfH;
	ptsInTop[9] = -halfW; ptsInTop[10] = -halfH;

	std::copy(std::begin(ptsInTop), std::end(ptsInTop), std::begin(ptsInDown));
	std::copy(std::begin(ptsOutTop), std::end(ptsOutTop), std::begin(ptsOutDown));

	ptsInTop[2] = ptsInTop[5] = ptsInTop[8] = ptsInTop[11] = (height);//Set Z component to zero for all 4 components

	ptsInDown[2] = ptsInDown[5] = ptsInDown[8] = ptsInDown[11] = 0;//Set Z component to zero for all 4 components

	std::thread threadTop(&Scene3D::makeCorners, this, std::ref(srcTop), std::ref(dstTop), ptsInTop, ptsOutTop, sideLength, F, halfW, halfH);
	std::thread threadDown(&Scene3D::makeCorners, this, std::ref(srcDown), std::ref(dstDown), ptsInDown, ptsOutDown, sideLength, F, halfW, halfH);
	if (threadTop.joinable())
		threadTop.join();
	if (threadDown.joinable())
		threadDown.join();

	//makeCorners(srcTop, dstTop, ptsInTop, ptsOutTop, sideLength, F, halfW, halfH);
	//makeCorners(srcDown, dstDown, ptsInDown, ptsOutDown, sideLength, F, halfW, halfH);

}



//Step A.1
void Scene3D::WarpImage(const Mat &src, double theta, double phi, double gamma, double scale, double fovy, Mat& dst, double zoom , double height , Position posit )
{
	Mat M;
	vector<Point2f> corners;
	double halfFovy = fovy * 0.5;
	double d = hypot(src.cols, src.rows);
	double sideLength = scale * d / cos(deg2Rad(halfFovy));
	//Step B.1
	warpMatrix(src.size(), theta, phi, gamma, scale, fovy, M, &corners, zoom, height,posit);//Compute warp matrix
	
	//finale step 
	warpPerspective(src, dst, M, Size((int)sideLength,(int) sideLength));//Do actual image warp
}



//faster method , using multithreading
	//Step A.1.1
void Scene3D::WrapTopDownImages(const Mat &srcTop, const Mat &srcDown, double theta, double phi, double gamma, double scale, double fovy, Mat& dstTop, Mat& dstDown, double zoom, double height)
{
	Mat M_Top,M_Down;
	//vector<Point2f> corners_Top, vector<Point2f> corners_Down;
	double halfFovy = fovy * 0.5;
	double d = hypot(srcTop.cols, srcTop.rows);
	double sideLength = scale * d / cos(deg2Rad(halfFovy));
	 wrapTopDownMatrix(srcTop, srcDown, dstTop,  dstDown, srcTop.size(),  theta,  phi,  gamma,  scale,  fovy,  zoom,  height);


}

Scene3D::Scene3D()
{
}


Scene3D::~Scene3D()
{
}
