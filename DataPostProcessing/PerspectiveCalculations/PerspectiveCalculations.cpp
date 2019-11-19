#include "PerspectiveCalculations.h"



PerspectiveCalculations::PerspectiveCalculations()
{
}


PerspectiveCalculations::~PerspectiveCalculations()
{
}


//get point with min distance btween Point and vector<Points>
//step C
void  PerspectiveCalculations::getPointSceneCorner(DataAccumulate &dataAccumulate, Point2f roiCorner,Point2f &result)
{

	//get max counter size
	//step 1
	int hullCount = (int)dataAccumulate.GetConvexHull_ref().size();

	//init values
	//step 2
	int index = 0; // in ConvexHull vector 

	double minDistance = 36000;
	//min difference (NOT DISTANCE) between corner and points in roi 
	Point2f deltaDifferencePoint;

	vector<Point2f>points_1_roi = dataAccumulate.GetRoi_GoodPoint2F_new_coordinates_vector_ref();
	vector<Point2f> points_2_scene = dataAccumulate.GetScene_GoodPoint2F_vector_ref();
	vector<int> hull = dataAccumulate.GetConvexHull_ref();


	//find delta of ROI Corner
	//step 3
	for (int i = 0; i < hullCount; i++)
	{
		Point2f difference = roiCorner - points_1_roi[hull[i]];
		double distance = sqrt(difference.ddot(difference));

		if (distance < minDistance)
		{
			minDistance = distance;
			index = i;
			deltaDifferencePoint = difference;
		}
	}

	//find new coordinate of scene corner 
	//step 4
	result = (points_2_scene[hull[index]] + deltaDifferencePoint);

}



//get vector of scene new corner coordinates
//using multiTheading
//step B
void PerspectiveCalculations::runMultiThreadCornerCalculation(DataAccumulate &dataAccumulate)
{
	//new corners 
	vector<Point2f> newCoordinates(4);// = dataAccumulate.vectorOfSceneCorners_ref();
	std::thread topLeft_A(&PerspectiveCalculations::getPointSceneCorner, this, std::ref(dataAccumulate), dataAccumulate.Get_ref_RoiBoardCoordinates_A_TopL(),std::ref(newCoordinates[0]));
	std::thread topRight_B(&PerspectiveCalculations::getPointSceneCorner, this, std::ref(dataAccumulate), dataAccumulate.Get_ref_RoiBoardCoordinates_B_TopR(), std::ref(newCoordinates[1]));
	std::thread botRight_C(&PerspectiveCalculations::getPointSceneCorner, this, std::ref(dataAccumulate), dataAccumulate.Get_ref_RoiBoardCoordinates_C_BotR(), std::ref(newCoordinates[2]));
	std::thread botLeft_D(&PerspectiveCalculations::getPointSceneCorner, this, std::ref(dataAccumulate),dataAccumulate.Get_ref_RoiBoardCoordinates_D_BotL(), std::ref(newCoordinates[3]));

	topLeft_A.join();
	topRight_B.join();
	botRight_C.join();
	botLeft_D.join();

	newCoordinates.swap(dataAccumulate.getSetVectorOfBoardSceneCorners_ref());

}



//calculate 4 points of ROI board
//and
//Calculate 4 points of Scene Board
//result will be saved in DataAccumulate
//Step A
void PerspectiveCalculations::CalculateCoordinatesOfBoardSidesPoints(DataAccumulate &dataAccumulate)
{

	//cheak if we have point work with
	//step 1
	if (dataAccumulate.GetRoi_GoodPoint2F_new_coordinates_vector_ref().empty() || dataAccumulate.GetScene_GoodPoint2F_vector_ref().empty() || dataAccumulate.GetRoi_GoodPoint2F_new_coordinates_vector_ref().size() < 5 || dataAccumulate.GetScene_GoodPoint2F_vector_ref().size() < 5)
		return;

	//convert good points to ConvexHull
	//step 2
	pointsProcessing.ConvertGoodPoints2F_to_ConvexHull(dataAccumulate.GetRoi_GoodPoint2F_new_coordinates_vector_ref(), dataAccumulate.GetConvexHull_ref());

	//cheak convexHull vector
	//if vector is empty return
	//step 3
	if (dataAccumulate.GetConvexHull_ref().empty() || (int)dataAccumulate.GetConvexHull_ref().size() < 4)
		return;

	//get vector of ConvexHull indexis
	//and get size
	//step 4
	//vector<int> hull = dataAccumulate.GetConvexHull_ref();
	//const int hullcount = (int)hull.size();

	//we need calculate all cotner points of ROI
	//step 5
	dataAccumulate.CalculateAllRoiBoardCoordinates();
	
	//get new scene coordinates
	//step 6
	runMultiThreadCornerCalculation(dataAccumulate);


}