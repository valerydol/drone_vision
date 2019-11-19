#include "ProcessingCommand.h"

//if we have roi we can process other IMG
//step C.0
void  ProcessingCommand::setImg(Mat &srcSceneImg, DataAccumulate &dataAccumulate, COMMAND command )
{
	//set scene img to DataAccumulate
	//step 1
	dataAccumulate.SetSceneNewImg(srcSceneImg);

	//detect img Keypoints And Descriptors
	//step 2
	imgProcessing.DetectKeypointsAndDescriptors(dataAccumulate.GetSceneImg_ref(), dataAccumulate.GetKeyPointsScene_ref(), dataAccumulate.GetSceneDescriptors_ref());


	//compare ROI and scene data
	//step 3
	imgProcessing.GetGoodComparedKeypoints(dataAccumulate.GetRoi_GoodPoint2F_vector_ref(), dataAccumulate.GetScene_GoodPoint2F_vector_ref(), dataAccumulate.GetKeyPointsRoi_ref(), dataAccumulate.GetKeyPointsScene_ref(), dataAccumulate.GetRoiDescriptors_ref(), dataAccumulate.GetSceneDescriptors_ref());

}



//if we need set roi
//step B.2
void ProcessingCommand::setNewRoi( Mat &srcImg, DataAccumulate &dataAccumulate, COMMAND command)
{
	//find new roi region
	//step 1
	roiSelector.GetRoiFromImg(srcImg, dataAccumulate.GetRoiNoCropImg_ref(), dataAccumulate.GetRoiCropImg_ref(), dataAccumulate.getOffsetRoi_X_ref(), dataAccumulate.getOffsetRoi_Y_ref(), dataAccumulate.getRoiWidth_X_ref(), dataAccumulate.getRoiHeight_Y_ref(), command);
	
	//detect ROI Keypoints And Descriptors
	//perocess and save ROI KeyPoints and Roi descroptor
	//step 2
	imgProcessing.DetectKeypointsAndDescriptors(dataAccumulate.GetRoiCropImg_ref(), dataAccumulate.GetKeyPointsRoi_ref(), dataAccumulate.GetRoiDescriptors_ref());

	//set roi flag --> false ( roi is not empty )
	//step 3
	roiEmptyFlag = false;
	
	//dataAccumulate.SetNewRoiFlagTrue();
	//cout << "NEW ROI" << endl;
}

//Step B.0
void ProcessingCommand::SetFrame(Mat srcImg, DataAccumulate &dataAccumulate, COMMAND command)
{
	//if ROI is not set
	//Step B.1  
	if ( ( RoiIsEmpty()) || (command == ROI_NEW) || (command == ROI_BIGGER) || (command == ROI_SMALLER) || (command == ROI_LAST_SIZE) )
	{
		setNewRoi(srcImg, dataAccumulate, command);
		return;
	}
	else // if we have ROI , we can process scene img
	{
		//step B.2 process scene img , and compare with ROI
		setImg(srcImg, dataAccumulate, command);

		//if we found matching, convert ROI local points to GLOBAL
		//step B.3
		if (!(dataAccumulate.GetScene_GoodPoint2F_vector_ref().empty()))
		{
			pointProcessing.ConvertRoiPointsInVector(dataAccumulate.GetRoi_GoodPoint2F_vector_ref(), dataAccumulate.GetRoi_GoodPoint2F_new_coordinates_vector_ref(), dataAccumulate.getOffsetRoi_X(), dataAccumulate.getOffsetRoi_Y());
		}
	}
	
}

ProcessingCommand::ProcessingCommand()
	: roiEmptyFlag(true) ,roiSelector(), imgProcessing(), pointProcessing()
{

}


ProcessingCommand::~ProcessingCommand()
{
}


