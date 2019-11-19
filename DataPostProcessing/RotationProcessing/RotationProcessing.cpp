#include "RotationProcessing.h"



RotationProcessing::RotationProcessing()
{
}


RotationProcessing::~RotationProcessing()
{

}


//we wont angle in range +- 359 degree
//Step A.4
void  RotationProcessing::correctAngle()
{
	int i = (int)(angle / 360.0F);
	angle = angle - (float)i * 360.0F;
}

//calculate current angle
//step A.3
void RotationProcessing::calculateCurrentAngle(float newAngle)
{
	double deltaAngle = 0;
	if (newAngle == lastAngle)
	{
		lastAngle = 0.0F;
		newAngle = 0.0F;
		flag = true;
	}
	deltaAngle = (newAngle - lastAngle);
	if (deltaAngle != 0)
	{
		int i = deltaAngle > 0 ? 1 : -1;
		if ((deltaAngle < 0.2) && (deltaAngle > -0.2))
		{
			deltaAngle = 0;
		}
		else if ((deltaAngle < 0.25) && (deltaAngle > -0.25))
		{
			deltaAngle = i * 0.1;
		}
		else if ((deltaAngle < 0.3) && (deltaAngle > -0.3))
		{
			deltaAngle = i * 0.15;
		}
		else if ((deltaAngle < 0.35) && (deltaAngle > -0.35))
		{
			deltaAngle = i * 0.18;
		}
		else if ((deltaAngle < 0.4) && (deltaAngle > -0.4))
		{
			deltaAngle = i * 0.2;
		}
		else if ((deltaAngle < 0.45) && (deltaAngle > -0.45))
		{
			deltaAngle = i * 0.25;
		}
		else if ((deltaAngle < 0.5) && (deltaAngle > -0.5))
		{
			deltaAngle = i * 0.3 ;
		}
		else if ((deltaAngle < 0.56) && (deltaAngle > -0.56))
		{
			deltaAngle = i * 0.35;
		}
		else if ((deltaAngle < 0.6) && (deltaAngle > -0.6))
		{
			deltaAngle = i * 0.38;
		}
		else if ((deltaAngle < 0.8) && (deltaAngle > -0.8))
		{
			deltaAngle = i * 0.4;
		}
		else if ((deltaAngle < 1) && (deltaAngle > -1))
		{
			deltaAngle = i * 0.5;
		}
		else if ((deltaAngle < 1.1) && (deltaAngle > -1.1))
		{
			deltaAngle = i * 0.8;
		}
		else if ((deltaAngle < 1.25) && (deltaAngle > -1.25))
		{
			deltaAngle = i * 0.9;
		}
		else if ((deltaAngle < 1.3) && (deltaAngle > -1.3))
		{
			deltaAngle = deltaAngle  + i;
		}
		else if ((deltaAngle < 1.42) && (deltaAngle > -1.42))
		{
			deltaAngle = deltaAngle  + i+0.5;
		}
		else if ((deltaAngle < 1.6) && (deltaAngle > -1.6))
		{
			deltaAngle = deltaAngle +i*0.8;
		}
		else if ((deltaAngle < 2.6) && (deltaAngle > -2.6))
		{
			deltaAngle = deltaAngle + 2*i;
		}
		else 
		{
			deltaAngle *= 3;
		}

			
		
	}
	angle += (float)deltaAngle;
	lastAngle = newAngle;

	if (flag)
	{
		lastAngle = 0.0F;
		flag = false;
	}

}

//method return temp angle 
//Step A.2 
float RotationProcessing::getTempRotationAngleInRadians(const Point2f &centerPoint, const Point2f &roi_Mid, const Point2f &scen_Mid)
{

	Vec2f roiCenterPointVector(centerPoint);
	Vec2f roiDirectionVector(roi_Mid.x - centerPoint.x, roi_Mid.y - centerPoint.y);
	Vec2f sceneDirectionVector(scen_Mid.x - centerPoint.x, scen_Mid.y - centerPoint.y);
	Vec2f roiNormalVector = normalize(roiDirectionVector);
	Vec2f sceneNormalVector = normalize(sceneDirectionVector);

	//angle is:
	float newTempAngle = acos(roiNormalVector.dot(sceneNormalVector));;

	if (roi_Mid.x < scen_Mid.x)
	{
		newTempAngle *= (-1.0F);
	}

	return newTempAngle;
}


//return current rotation angle
	//Step A.1
void RotationProcessing::GetRotationAngle(DataAccumulate &dataAccumulate, float &result)
{

	vector<Point2f> roi_points = dataAccumulate.getSetVectorOfBoardRoiCorners_ref();
	vector<Point2f>scene_points = dataAccumulate.getSetVectorOfBoardSceneCorners_ref();
	//check vector sizes
	//step 1
	if (roi_points.empty() || scene_points.empty() || ((int)scene_points.size() != 4) || ((int)roi_points.size() != 4))
	{
		// input is wrong
		return;
	}
	Point2f roi_Mid, scen_Mid;


	//get mid point of roi
	//step 2
	mathCalculations.GetMiddleOfLine(roi_points[0], roi_points[1], roi_Mid);
	mathCalculations.GetMiddleOfLine(scene_points[0], scene_points[1], scen_Mid);

	//get center point of frame (ROI)
	//step 3
	Point2f centerPoint;
	//mathCalculations.GetCenterPointOfFrame(dataAccumulate.GetRoiNoCropImg_ref().cols, dataAccumulate.GetRoiNoCropImg_ref().rows, centerPoint);
	mathCalculations.GetCenterPointOfFrame((float)dataAccumulate.GetRoiCropImg_ref().cols, (float)dataAccumulate.GetRoiCropImg_ref().rows, centerPoint);

	//get temp angle 
	//step A.2
	float newAngle = getTempRotationAngleInRadians(centerPoint, roi_Mid, scen_Mid);

	newAngle *= (float)(180.0F / CV_PI);

	//calculate current angle
	//step A.3
	calculateCurrentAngle(newAngle);

	correctAngle();
	result = this->angle;

}