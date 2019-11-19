#pragma once
#include "..\..\ProjectIncludes\ProjectIncludes_Header.h"
#include "..\..\PointsProcessing\PointsProcessing.h"
#include "..\..\DataAccumulate\DataAccumulate.h"
#include "..\..\MathCalculations\MathCalculations.h"


class PerspectiveCalculations
{
private:
	PointsProcessing pointsProcessing;
	MathCalculations mathCalculations;
public:
	PerspectiveCalculations();
	virtual ~PerspectiveCalculations();

	//calculate 4 points of ROI board
	//and
	//Calculate 4 points of Scene Board
	//result will be saved in DataAccumulate
	//Step A
	void CalculateCoordinatesOfBoardSidesPoints(DataAccumulate &dataAccumulate);

private:

	//get vector of scene new corner coordinates
	//using multiTheading
	//step B
	void runMultiThreadCornerCalculation(DataAccumulate &dataAccumulate);

	//get point with min distance between Point and vector<Points>
	//step C
	void getPointSceneCorner(DataAccumulate &dataAccumulate,  Point2f roiCorner, Point2f &result  );
};

