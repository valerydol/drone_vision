#include "ImageProcessing.h"


//convert good matches to vector of KeyPoints in scene  
//step 3.3.2
void ImageProcessing::convertGoodMatches2GoodPointsRoi(vector<Point2f> &good_Points2F_1_obj, vector<Point2f> &good_Points2F_2_scene, vector<DMatch > &goodComparedMatches, const vector<KeyPoint> &keyPoints_1_obj, const vector<KeyPoint> &keyPoints_2_scene)
{
	try
	{
		if (!goodComparedMatches.empty() && !keyPoints_1_obj.empty() && !keyPoints_2_scene.empty() && ((int)goodComparedMatches.size() >= thresholdGoodMatches))
		{
			int goodMatchesSize =(int) goodComparedMatches.size();
			good_Points2F_1_obj.clear();
			good_Points2F_2_scene.clear();
			good_Points2F_1_obj.reserve(goodMatchesSize);
			good_Points2F_2_scene.reserve(goodMatchesSize);

			minPoints = min(min(min(goodMatchesSize, (int)keyPoints_1_obj.size()), (int)keyPoints_2_scene.size()), thresholdGoodMatches);
			//choose only good matches and set points to points vectors
			for ( int i = 0; i < minPoints; i++)
			{
				good_Points2F_1_obj.push_back(keyPoints_1_obj[goodComparedMatches[i].queryIdx].pt);
				good_Points2F_2_scene.push_back(keyPoints_2_scene[goodComparedMatches[i].trainIdx].pt);
			
			}
		}
	}
	catch (Exception ex)
	{
		cout << "EXCEPTION : convertGoodMatches2GoodPoints " << endl;
	}
}

//convert good matches to vector of KeyPoints in scene and object  
//step 3.3
void ImageProcessing::convertGoodMatches2GoodPoints(vector<Point2f> &good_Points2F_1_obj, vector<Point2f> &good_Points2F_2_scene, vector<DMatch > &goodComparedMatches, const vector<KeyPoint> &keyPoints_1_obj, const vector<KeyPoint> &keyPoints_2_scene)
{
	try
	{
		if (!goodComparedMatches.empty() && !keyPoints_1_obj.empty() && !keyPoints_2_scene.empty() && ((int)goodComparedMatches.size() >= thresholdGoodMatches))
		{
			int goodMatchesSize = (int)goodComparedMatches.size();
			good_Points2F_1_obj.clear();
			good_Points2F_2_scene.clear();
			good_Points2F_1_obj.reserve(goodMatchesSize);
			good_Points2F_2_scene.reserve(goodMatchesSize);

			minPoints = min ( min(min(goodMatchesSize, (int)keyPoints_1_obj.size()), (int)keyPoints_2_scene.size() ), thresholdGoodMatches);
			//choose only good matches and set points to points vectors
			for (unsigned int i = 0; i <(unsigned int) goodComparedMatches.size(); i++)
			{
				good_Points2F_1_obj.push_back(keyPoints_1_obj[goodComparedMatches[i].queryIdx].pt);
				good_Points2F_2_scene.push_back(keyPoints_2_scene[goodComparedMatches[i].trainIdx].pt);

			}
		}
	}
	catch (Exception ex)
	{
		cout << "EXCEPTION : convertGoodMatches2GoodPoints " << endl;
	}
}



//return only good matches after compare
//step 3.2 
void ImageProcessing::getOnlyGoodMatches(vector< DMatch > &goodComparedMatches, const vector < vector<DMatch> > &matches, const Mat &descriptor)
{
	try
	{
		int size = min(descriptor.rows, (int)matches.size());
		goodComparedMatches.clear();
		goodComparedMatches.reserve(size);

		for (int i = 0; i < min(descriptor.rows - 1, (int)matches.size()); i++) //THIS LOOP IS SENSITIVE TO SEGFAULTS
		{
			if (!matches[i].empty() && ((int)matches[i].size() <= 2 && (int)matches[i].size() > 0) && (matches[i][0].distance < thresholdMatchingNN*(matches[i][1].distance)))
			{
				goodComparedMatches.push_back(matches[i][0]);
			}
		}
	}
	catch (Exception ex)
	{
		cout << "EXCEPTION : getOnlyGoodMatches " << endl;
		//system("pause");
	}
}



//use KNN to detect matches 
//can throw exception
//step 3.1
void ImageProcessing::detectKnnMatches(vector<vector< DMatch > >&matches, const Mat &descript_1_obj, const Mat &descript_2_scene)
{
	try
	{
	if (!descript_1_obj.empty() && !descript_2_scene.empty())
		{
			int k = 2;
			matcher.knnMatch(  descript_1_obj,descript_2_scene,matches, k);
		}
	}
	catch (Exception ex)
	{
		cout << "EXEPRION : detectKnnMatches" << endl;

	}
}


//method return converter "GOOD MATCHES POINTS"
//STEP 3 
void ImageProcessing::GetGoodComparedKeypoints(vector<Point2f> &good_keyPoints_1_obj, vector<Point2f> &good_keyPoints_2_scene, const vector<KeyPoint> &keyPoints_1_obj, const vector<KeyPoint> &keyPoints_2_scene, const Mat &descript_1_obj, const Mat &descript_2_scene,bool roiFlag)
{
	vector<vector <DMatch> > matches;//knn matches
	good_keyPoints_2_scene.clear();
	try
	{
		detectKnnMatches(matches, descript_1_obj, descript_2_scene);//step 3.1 //detect matches

		vector< DMatch > goodComparedMatches(0);//good matches after compare
		getOnlyGoodMatches(goodComparedMatches, matches, descript_1_obj);//step 3.2 // select only good matches after compare
		
		convertGoodMatches2GoodPointsRoi(good_keyPoints_1_obj, good_keyPoints_2_scene, goodComparedMatches, keyPoints_1_obj, keyPoints_2_scene); //step 3.3
	
	}
	catch (Exception ex)
	{
		cout << "EXCEPRION : GetGoodComparedKeypoints" << endl;
	}

}

//Calculate descriptors (feature vectors)
//step 2.3
void ImageProcessing::calculateDescriptors(const Mat &grayImg, vector<KeyPoint> &keyPoints, Mat &descriptors)
{
	extractor->compute(grayImg, keyPoints, descriptors);
}


//Detect the keypoints using SURF Detector
//step 2.2
void ImageProcessing::detectKeypointsWithSURF(const Mat &grayImg, vector<KeyPoint> &keypoints)
{
	detector->detect(grayImg, keypoints);
}


//convert color to gray img
//step 2.1
void ImageProcessing::colorToGrayImg(const Mat &srcImg, Mat &grayImg)
{
	cvtColor(srcImg, grayImg, COLOR_BGR2GRAY);
}


//we need detect Keypoints and Descriptors of all pictures we wont work with
//STEP 2
void ImageProcessing::DetectKeypointsAndDescriptors(const Mat &img, vector<KeyPoint> &keyPoints, Mat &descriptors)
{
	Mat grayImg;
	colorToGrayImg(img, grayImg); //step 2.1 // convert img to gray 
	detectKeypointsWithSURF(grayImg, keyPoints);//step 2.2 // Detect the keypoints
	calculateDescriptors(grayImg, keyPoints, descriptors); //step 2.3 // Calculate descriptors

}



//step 1
void ImageProcessing::Initialize(int _minHess)
{
	detector = NULL;
	extractor = NULL;

	detector = SURF::create(_minHess); // threshold for detection
	extractor = detector;
}

ImageProcessing::ImageProcessing(int _minHess)
	:minHess(_minHess), detector(NULL), extractor(NULL), matcher(), thresholdMatchingNN(0.5f), thresholdGoodMatches(8), minPoints(0)
{
	Initialize(minHess);
}


ImageProcessing::~ImageProcessing()
{
}
