#pragma once
#include "..\ProjectIncludes\ProjectIncludes_Header.h"
#include "..\DataAccumulate\DataAccumulate.h"
#include "..\ProcessingCommand\ProcessingCommand.h"
#include "..\Painter\Painter.h"
#include "..\MathCalculations\MathCalculations.h"
#include "..\\DataPostProcessing\DirectionArrow\DirectionArrow.h"
#include "..\DataPostProcessing\PerspectiveCalculations\PerspectiveCalculations.h"
#include "..\DataPostProcessing\HeightCalculations\HeightCalculations.h"
#include "..\DataPostProcessing\RotationProcessing\RotationProcessing.h"
#include "..\DataPostProcessing\PostProcessing\PostProcessing.h"
#include "..\TriangleObject\Triangle\Triangle.h"
#include "..\SceneGraphicMotion\MouseParameters\MouseParameters.h"
#include "..\SceneGraphicMotion\SceneMotion\SceneMotion.h"
#include "..\DataPostProcessing\DataCorrection\DataCorrection.h"
#include "..\RealTimeDataBinding\RT_DataBinding.h"

using namespace cv;
/*
this class must receive data for processing
and commands from video CONNECTION CLASS
*/
class DataAndCommandReceiver
{
private:
	Point2f last;
	DataAccumulate dataAccumulate;
	ProcessingCommand processingCommand;
	Painter painter;
	MathCalculations mathCalculations;
	//DirectionArrow directionArrow;
	//PerspectiveCalculations perspectiveCalculations;
	//HeightCalculations heightCalculations;
	//RotationProcessing rotationProcessing;
	//TriangleObject triangleObject;
	PostProcessing postProcessing;
	MouseParameters mouseParameters;
	int oldKey = -1;

	Triangle triangle;
	DataCorrection dataCorrection;


	//we need decode pressed key
	//int can be ( -1 ) , this can thraw exception if we 
	//try find ascii code of(-1)
	//step A.1
	COMMAND detectPressedKey(int key_num);
	

	RT_DataBinding dataBinding;



public:

	//receive data and pressed key number
	//Step A.0
	void SetNewPairFrameKey(unique_ptr<pair<Mat, int>> data_ptr);

	DataAndCommandReceiver();
	virtual ~DataAndCommandReceiver();

	
};

