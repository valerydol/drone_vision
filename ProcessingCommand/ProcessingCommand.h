#pragma once
#include "..\RoiSelector\RoiSelector.h"
#include "..\ImageProcessing\ImageProcessing.h"
#include "..\DataAccumulate\DataAccumulate.h"
#include "..\PointsProcessing\PointsProcessing.h"
class ProcessingCommand
{
private:

	bool roiEmptyFlag;

	RoiSelector roiSelector;

	ImageProcessing imgProcessing;

	//pointProcessing convert ROI points from local to global coordinats
	PointsProcessing pointProcessing;


	//if we have roi we can process other IMG
	//step C.0
	void setImg(Mat &srcSceneImg, DataAccumulate &dataAccumulate, COMMAND command=DEFAULT);

	//if we need set roi
	//step B.2
	void setNewRoi( Mat &srcImg, DataAccumulate &dataAccumulate, COMMAND command );
	
	//we need to check if roi is not empty
	//Step B.1  
	bool RoiIsEmpty() { return roiEmptyFlag; }
public:

	//we need recognize if ROI is already setted
	//if no, first of all set ROI
	//Step B.0
	void SetFrame(Mat srcImg, DataAccumulate &dataAccumulate, COMMAND command = DEFAULT);

	//step A.0
	ProcessingCommand();
	virtual ~ProcessingCommand();


	

};
