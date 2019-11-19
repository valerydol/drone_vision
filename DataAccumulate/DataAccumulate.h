#pragma once
#include "..\ProjectIncludes\ProjectIncludes_Header.h"

/*
this class must save data after processing
*/

class DataAccumulate
{
private:
	//ROI DATA
	Mat roiSrc; //img
	Mat roiCroped; //img

	Mat descriptors_obj_roi; // mat
	vector<KeyPoint> keyPoints_obj_roi;
	vector<Point2f> good_Points2F_obj_roi;
	vector<Point2f> good_Points2F_obj_roi_new_coordinates;


	//SCENE DATA
	Mat sceneSrc; //img

	Mat descriptors_scene; //mat
	vector<KeyPoint> keyPoints_scene;
	vector<Point2f> good_Points2F_scene;





	float offset_roi_x = 0;
	float offset_roi_y = 0;
	float width_roi_x = 0;
	float height_roi_y = 0;

	vector<int> hullCollectionVector;


	// Roi`s board coordinates
	//from TopLeft , clockwise
	Point2f roiA_TopL;
	Point2f roiB_TopR;
	Point2f roiC_BotR;
	Point2f roiD_BotL;
	//points of scene after perspective processing
	vector<Point2f> roiBoardCornerPoints2f;

	//
	float roiArea;

	// Scene`s board coordinates
	//from TopLeft , clockwise
	Point2f sceneA_TopL;
	Point2f sceneB_TopR;
	Point2f sceneC_BotR;
	Point2f sceneD_BotL;
	//points of scene after perspective processing
	vector<Point2f> sceneBoardCornerPoints2f;
	//
	float sceneArea;

	bool newRoiFlag = false;

public:

	//setters //getters X, Y ,W,H
	//Step
	void SetOffsetRoi_X(float _roiOffset_X) { offset_roi_x = _roiOffset_X; }
	void SetOffsetRoi_Y(float _roiOffset_Y) { offset_roi_y = _roiOffset_Y; }
	void SetWidthRoi_X(float _width_roi_x) { width_roi_x = _width_roi_x; }
	void SetHeightRoi_Y(float _height_roi_y) { height_roi_y = _height_roi_y; }

	//set img for scene
	void SetSceneNewImg(const Mat &sceneImgSrc) { sceneSrc = sceneImgSrc.clone(); }

	//getters
	float& getOffsetRoi_X_ref() { return offset_roi_x; }
	float& getOffsetRoi_Y_ref() { return offset_roi_y; }
	float& getRoiWidth_X_ref() { return width_roi_x; }
	float& getRoiHeight_Y_ref() { return height_roi_y; }

	float getOffsetRoi_X() const { return offset_roi_x; }
	float getOffsetRoi_Y()const { return offset_roi_y; }
	float getRoiWidth_X()const { return width_roi_x; }
	float getRoiHeight_Y() const { return height_roi_y; }


	//get roi IMG ref
	Mat& GetRoiNoCropImg_ref() { return roiSrc; }

	//get roi IMG clone
	Mat GetRoiNoCropImg_clone() { return roiSrc.clone(); }

	//get roi CROPED IMG ref
	Mat& GetRoiCropImg_ref() { return roiCroped; }

	//get roi CROPED IMG clone
	Mat GetRoiCropImg_clone() { return roiCroped.clone(); }

	//get Mat descriptors_obj_roi
	Mat& GetRoiDescriptors_ref() { return descriptors_obj_roi; }


	// set Roi IMG not croped
	void GetRoiSrcImg(const Mat & _roiSrc) { roiSrc = _roiSrc.clone(); }

	// set Roi IMG  croped
	void GetRoiSrcImg_Croped(const Mat & _roiCroped) { roiCroped = _roiCroped.clone(); }


	//get vector<KeyPoint> keyPoints_obj_roi_ref; 
	vector<KeyPoint>& GetKeyPointsRoi_ref() { return keyPoints_obj_roi; }

	//get / set vector<Point2f> good_Points2F_obj_roi_ref;
	vector<Point2f>& GetRoi_GoodPoint2F_vector_ref() { return good_Points2F_obj_roi; }

	//get/set scene IMG ref
	Mat& GetSceneImg_ref() { return sceneSrc; }

	//get scene IMG clone
	Mat GetSceneImg_clone() { return sceneSrc.clone(); }

	//get/set Mat descriptors_scene-ref
	Mat& GetSceneDescriptors_ref() { return descriptors_scene; }

	//get/set vector<KeyPoint> keyPoints_scene_ref
	vector<KeyPoint>& GetKeyPointsScene_ref() { return keyPoints_scene; }

	//get / set vector<Point2f> vector<Point2f> good_Points2F_scene_ref;
	vector<Point2f>& GetScene_GoodPoint2F_vector_ref() { return good_Points2F_scene; }

	//get good_Points2F_obj_roi_new_coordinates
	vector<Point2f>& GetRoi_GoodPoint2F_new_coordinates_vector_ref() { return good_Points2F_obj_roi_new_coordinates; }

	//get convexHULL vector_ref
	vector<int>& GetConvexHull_ref() { return hullCollectionVector; }

private:
	//Setters Roi Board coordinates
	void SetRoiBoardCoordinates_A_TopL(const Point2f &_roiA_TopL) { roiA_TopL = _roiA_TopL; }
	void SetRoiBoardCoordinates_B_TopR(const Point2f &_roiB_TopR) { roiB_TopR = _roiB_TopR; }
	void SetRoiBoardCoordinates_C_BotR(const Point2f &_roiC_BotR) { roiC_BotR = _roiC_BotR; }
	void SetRoiBoardCoordinates_D_BotL(const Point2f &_roiD_BotL) { roiD_BotL = _roiD_BotL; }

public:
	//getters Roi Board coordinates
	Point2f& Get_ref_RoiBoardCoordinates_A_TopL() { return roiA_TopL; }
	Point2f& Get_ref_RoiBoardCoordinates_B_TopR() { return roiB_TopR; }
	Point2f& Get_ref_RoiBoardCoordinates_C_BotR() { return roiC_BotR; }
	Point2f& Get_ref_RoiBoardCoordinates_D_BotL() { return roiD_BotL; }

	//calculate all ROI board Coordinates
	void CalculateAllRoiBoardCoordinates();

	//Setters Scene Board coordinates
	void SetSceneBoardCoordinates_A_TopL(const Point2f &_sceneA_TopL) { sceneA_TopL = _sceneA_TopL; }
	void SetSceneBoardCoordinates_B_TopR(const Point2f &_sceneB_TopR) { sceneB_TopR = _sceneB_TopR; }
	void SetSceneBoardCoordinates_C_BotR(const Point2f &_sceneC_BotR) { sceneC_BotR = _sceneC_BotR; }
	void SetSceneBoardCoordinates_D_BotL(const Point2f &_sceneD_BotL) { sceneD_BotL = _sceneD_BotL; }
	//getters Scene Board coordinates
	Point2f& Get_ref_SceneBoardCoordinates_A_TopL() { return sceneA_TopL; }
	Point2f& Get_ref_SceneBoardCoordinates_B_TopR() { return sceneB_TopR; }
	Point2f& Get_ref_SceneBoardCoordinates_C_BotR() { return sceneC_BotR; }
	Point2f& Get_ref_SceneBoardCoordinates_D_BotL() { return sceneD_BotL; }


	//points of scene after perspective processing
	vector<Point2f>& getSetVectorOfBoardSceneCorners_ref() { return sceneBoardCornerPoints2f; }

	//void SetAllNewArrayOfRoiCornersFromLocalMemory();
	vector<Point2f>& getSetVectorOfBoardRoiCorners_ref() { return roiBoardCornerPoints2f; }

	float& getSetRoiArea_ref() { return roiArea; }
	float& getSetSceneArea_ref() { return sceneArea; }

	//Step A.0
	DataAccumulate();
	virtual ~DataAccumulate();

	//this is angle roi controller methods
	/*void SetNewRoiFlagTrue() { newRoiFlag = true; }
	void SetNewRoiFlagFalse() { newRoiFlag = false; }
	bool GetNewRoiFlag()
	{
		return newRoiFlag;
	}*/

};
