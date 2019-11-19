#include "RoiSelector.h"



RoiSelector::RoiSelector(float _offset_roi_x, float _offset_roi_y, float _width_roi_x, float _height_roi_y, bool _isEmptyFlag)
	: offset_roi_x(_offset_roi_x), offset_roi_y(_offset_roi_y), width_roi_x(_width_roi_x), height_roi_y(_height_roi_y), isEmptyFlag(true), roiNotCroped(), roiCroped()
{

}


RoiSelector::~RoiSelector()
{
}


//if ROI was detected?
//step B.0
bool RoiSelector::isEmpty()
{
	return isEmptyFlag;
}

//select ROI with new data and crope
//step A.3
void RoiSelector::cropeNewROI(Mat &src, Mat &dstNotCroped, Mat &dstCroped)
{
	// Define the roi
	Rect roi((int)getOffsetRoi_X(), (int)getOffsetRoi_Y(), (int)getRoiWidth_X(), (int)getRoiHeight_Y());
	// Crop clone
	dstCroped = src(roi);
	dstNotCroped = src.clone();
	//copy croped roi
	roiCroped = dstCroped.clone();
	//copy src roi
	roiNotCroped = src.clone();

	//change isEmptyFlag
	isEmptyFlag = false;

}

//set new ROI offsets , new roi boarder sizes
//where is X / Y of start ROI
//step A.2.4
void RoiSelector:: setNewRoiOffsets(int src_cols_width, int src_rows_height, float &startOnX, float &startOnY)
{
	setOffsetRoi_X((src_cols_width / 2) - (getRoiWidth_X() / 2.0F));
	//setOffsetRoi_Y((src_rows_height / 2) - (getRoiHeight_Y() / 2));
	setOffsetRoi_Y((src_rows_height ) - (getRoiHeight_Y())-15.0F);

	startOnX = getOffsetRoi_X();
	startOnY = getOffsetRoi_Y();
}

//calculate ROI Width Height 
//do bigger 
//step A.2.3
void RoiSelector::doBigger(int src_cols_width, int src_rows_height)
{
	//check if we can do our ROI bigger
	if (((getRoiWidth_X() + ROI_DELTA) < src_cols_width) && ((getRoiHeight_Y() + ROI_DELTA) < src_rows_height))
	{
		setRoiWidth_X((float)(getRoiWidth_X() + ROI_DELTA)); //set Width_X
		setRoiHeight_Y((float)(getRoiHeight_Y() + ROI_DELTA));//set Height_Y
	}
	else//set max size
	{
		setRoiWidth_X((float)src_cols_width);//set Width_X
		setRoiHeight_Y((float)src_rows_height);//set Height_Y
	}
}


//calculate ROI Width Height 
//do smaller
//step A.2.3
void RoiSelector::doSmaller(int src_cols_width, int src_rows_height)
{
	//check if we can do our ROI smaller
	if (((getRoiWidth_X() - ROI_DELTA) > ROI_MIN_SIZE_WIDTH) && ((getRoiHeight_Y() - ROI_DELTA) > ROI_MIN_SIZE_HEIGTH))
	{
		if (getRoiWidth_X() != src_cols_width)
		{
			setRoiWidth_X((float)(getRoiWidth_X() - ROI_DELTA)); //set Width_X
			setRoiHeight_Y((float)(getRoiHeight_Y() - ROI_DELTA));//set Height_Y
		}
		else //if last roi.size equel src.size
		{
			//set width equels to height
			setRoiWidth_X((float)src_rows_height);//set Width_X
			setRoiHeight_Y((float)src_rows_height);//set Height_Y
		}
	}
	else // we can`t do ROI SMALLER , set ROI_SIZE_X1
	{
		setRoiWidth_X((float)ROI_DEFAULT_SIZE_WIDTH);
		setRoiHeight_Y((float)ROI_DEFAULT_SIZE_HEIGTH);
	}
}

//we need calculate roi size or get DEFAULT_SIZE
//step A.2.2
void RoiSelector:: getNewRoiSize(const Mat &src, float &width_frame_cols, float &height_frame_rows, COMMAND roi_size)
{
	int w = src.cols;
	int h = src.rows;
	if (roi_size == ROI_NEW)
	{
		setRoiWidth_X((float)ROI_DEFAULT_SIZE_WIDTH);
		setRoiHeight_Y((float)ROI_DEFAULT_SIZE_HEIGTH);
		
	}
	
	else if ((roi_size == ROI_BIGGER) || (roi_size == ROI_SMALLER))
	{
		

		if (roi_size == ROI_BIGGER)
		{
			doBigger(w, h);
		}
		else
		{
			doSmaller(w, h);
		}
	}
	
	width_frame_cols = getRoiWidth_X();
	height_frame_rows = getRoiHeight_Y();
}

//return croped Mat
// Define the roi and Crop img to ROI new size
//step A.2
void RoiSelector::GetRoiFromImg(Mat &src, Mat &dstNotCroped , Mat &dstCroped, float &startOnX, float &startOnY, float &width_frame_cols, float &height_frame_rows, COMMAND roi_size)
{
	//get new roi size
	getNewRoiSize(src, width_frame_cols, height_frame_rows, roi_size);

	//set start points for ROI
	setNewRoiOffsets(src.cols, src.rows, startOnX, startOnY);

	//crope ROI
	cropeNewROI(src, dstNotCroped, dstCroped);
}

