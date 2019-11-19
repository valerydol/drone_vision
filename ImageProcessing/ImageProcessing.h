#pragma once
#include"..\ProjectIncludes\ProjectIncludes_Header.h"
//this class Work only with Images 
class ImageProcessing
{
public:
	int minHess;
	//SURF Detector, and descriptor parameters, match object initialization
	//Detect the keypoints using SURF Detector, compute the descriptors
	Ptr<SURF> detector; // threshold for detection
	Ptr<DescriptorExtractor> extractor;
	FlannBasedMatcher matcher;  // descriptor matcher (k-NN based) --> (FLANN = Fast Library for Approximate Nearest Neighbors)

	float thresholdMatchingNN;
	int thresholdGoodMatches; 

	int minPoints;
	
	ImageProcessing(int _minHess = 400);
	virtual ~ImageProcessing();

private:

	//convert good matches to vector of KeyPoints in scene ONLY
	//step 3.3.2 
	void convertGoodMatches2GoodPointsRoi(vector<Point2f> &good_Points2F_1_obj, vector<Point2f> &good_Points2F_2_scene, vector<DMatch > &goodComparedMatches, const vector<KeyPoint> &keyPoints_1_obj, const vector<KeyPoint> &keyPoints_2_scene);

	//convert good matches to vector of KeyPoints in scene and object  
	//step 3.3
	void convertGoodMatches2GoodPoints(vector<Point2f> &good_Points2F_1_obj, vector<Point2f> &good_Points2F_2_scene, vector<DMatch > &goodComparedMatches, const vector<KeyPoint> &keyPoints_1_obj, const vector<KeyPoint> &keyPoints_2_scene);

	//return only good matches after compare
	//step 3.2 
	void getOnlyGoodMatches(vector< DMatch > &goodComparedMatches, const vector < vector<DMatch> > &matches, const Mat &descriptor);

	//use KNN to detect matches 
	//step 3.1
	void detectKnnMatches(vector <vector< DMatch >> &matches, const Mat &descript_1_obj, const Mat &descript_2_scene);

public:
	//compare keyPoints and descriptors
	//method return converted "GOOD MATCHES POINTS"
	//STEP 3 
	void GetGoodComparedKeypoints(vector<Point2f> &good_keyPoints_1_obj, vector<Point2f> &good_keyPoints_2_scene, const vector<KeyPoint> &keyPoints_1_obj, const vector<KeyPoint> &keyPoints_2_scene, const Mat &descript_1_obj, const Mat &descript_2_scene, bool roiFlag = false);


private:
	//Calculate descriptors (feature vectors)
	//step 2.3
	void calculateDescriptors(const Mat &grayImg, vector<KeyPoint> &keyPoints, Mat &descriptors);

	//Detect the keypoints using SURF Detector
	//step 2.2
	void detectKeypointsWithSURF(const Mat &grayImg, vector<KeyPoint> &keypoints);

	//convert color to gray img
	//step 2.1
	void colorToGrayImg(const Mat &srcImg, Mat &grayImg);

public:

	//we need detect Keypoints and Descriptors of all pictures we wont work with
	//STEP 2
	void DetectKeypointsAndDescriptors(const Mat &img, vector<KeyPoint> &keyPoints, Mat &descriptors);

	//initialize all values in constructor
	//STEP 1
	void Initialize(int _minHess = 400);


};

