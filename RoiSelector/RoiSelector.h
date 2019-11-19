#pragma once
#include "..\ProjectIncludes\ProjectIncludes_Header.h"


class RoiSelector
{
private:
	float offset_roi_x;
	float offset_roi_y;
	float width_roi_x;
	float height_roi_y;
	bool isEmptyFlag;

	//save rois imgs
	Mat roiNotCroped;
	Mat roiCroped;

	//setters
	void setOffsetRoi_X(float _roiOffset_X){ offset_roi_x = _roiOffset_X; }
	void setOffsetRoi_Y(float _roiOffset_Y){ offset_roi_y = _roiOffset_Y; }
	//step A.2.2
	//void setRoiWidth_X(float _width_roi_x);
	//void setRoiHeight_Y(float _height_roi_y);

	//getters
	float getOffsetRoi_X()const{ return offset_roi_x; }
	float getOffsetRoi_Y()const{ return offset_roi_y; }
	float getRoiWidth_X()const{ return width_roi_x; }
	float getRoiHeight_Y()const{ return height_roi_y; }

public:
	RoiSelector(float _offset_roi_x = 0, float _offset_roi_y = 0, float _width_roi_x = ROI_DEFAULT_SIZE_WIDTH, float _height_roi_y = ROI_DEFAULT_SIZE_HEIGTH, bool _isEmptyFlag = true);
	virtual ~RoiSelector();

	//if ROI was detected?
	//step B.0
	bool isEmpty();
private:

	//select ROI with new data and crope
	//step A.3
	void cropeNewROI(Mat &src, Mat &dstNotCroped, Mat &dstCroped);

	//set new ROI offsets , new roi boarder sizes
	//where is X / Y of start ROI
	//step A.2.4
	void setNewRoiOffsets(int src_cols_width, int src_rows_height , float &startOnX , float &startOnY);

	//calculate ROI Width Height 
	//do bigger or smaller
	//step A.2.3
	void doBigger(int src_cols_width, int src_rows_height);
	void doSmaller(int src_cols_width, int src_rows_height);

	//set width and  height for roi
	//step A.2.2
	void setRoiWidth_X(float _width_roi_x) { width_roi_x = _width_roi_x; }
	void setRoiHeight_Y(float _height_roi_y) { height_roi_y = _height_roi_y; }

	//we need calculate roi size or get DEFAULT_SIZE
	//step A.2.1
	void getNewRoiSize(const Mat &src, float &width_frame_cols, float &height_frame_rows, COMMAND roi_size = ROI_NEW);
public:
	//return croped Mat
	// Define the roi and Crop img to ROI new size
	//step A.2.0
	void GetRoiFromImg(Mat &src, Mat &dstNotCroped, Mat &dstCroped, float &startOnX, float &startOnY, float &width_frame_cols, float &height_frame_rows, COMMAND roi_size= ROI_NEW);

};

