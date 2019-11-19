#pragma once
#include <vector>
#include <iterator>
#include <cstdlib>
#include <math.h>

#include <stack>
#include <queue>
#include <algorithm> // for copy() and assign() 

#include <future>
#include <chrono>
#include <thread>
#include <mutex>  // std::this_thread::sleep_for
#include <atomic>

#include <iostream>      // std::cout, std::endl
#include <utility>      // std::pair

#include "opencv2/calib3d.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/opencv.hpp"


#include "Threadsafe_Queue.h"
#include "ROI_headar.h"
#include "Triangle_header.h"
#include "RT_DataBinding_Params.h"
#include "COLORS_Header.h"


using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;



/* Defines */




#define KEY_DEFAULT 'a'
#define KEY_DETECT_NEW_SCENE 'd'

#define KEY_COMPARE_OBJ_AND_SCENE 'c'

#define KEY_CODE_PAUSE 112 // 'p'
#define KEY_CODE_DEFAULT -1 //  'a'
#define KEY_CODE_QUIT 113 //'q'






//arrow


//ARROWS PARAMS:
const int MATRIX_SCENE_Y[3][3]{ {-1, 0 , 1} , {-2, 0 , 2} , {-1 , 0 , 1} };
const int MATRIX_SCENE_X[3][3]{ {-1,-2 ,-1} , { 0, 0 , 0} , { 1 , 2 , 1} };

//ARROW START POINT
const Point2f ARROW_START_POINT(80, 100);
#define ARROW_LEN 30



//SCENE 3D
#define SCENE3D_SIZE 500

enum Position
{
	//DOWN = -1,
	DOWN = 0,
	TOP = 1
	//MID,

	
};
