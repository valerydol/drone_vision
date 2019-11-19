#include "MouseParameters.h"

void MouseParameters::SetZoom(int zoom)
{
	
	zoomLast = zoomCurr;
	zoomCurr = zoom;
	updateFlagZoom = true;
}

float MouseParameters::GetZoom()
{
	if (updateFlagZoom == true)
	{
		updateFlagZoom = false;
		int temp = (int)(zoomCurr - zoomLast);
		if (temp == 0)
			return 0;
		int i = temp < 0 ? 1 : -1;
		return  (float)i * 0.01F;
	}

	return 0;
}

//return Difference between old and new params
//Step B.1
float  MouseParameters::GetZ()
{
	if (updateFlagZ == true)
	{
		updateFlagZ = false;
		int temp =(int)(zCurr - zLast);
		if (temp == 0)
			return (float) 0;
		int i = temp < 0 ? 1 : -1;
		return (float)(2* i);
	}

	return 0;
}

//Step B.2
float  MouseParameters::GetY()
{
	if (updateFlagY == true)
	{
		updateFlagY = false;
		int temp = (int)(yCurr - yLast);
		if (temp == 0)
			return 0;
		int i = temp < 0 ? 1 : -1;
		return (float)(2 * i);
	}

	return 0;
}


//set current angle 
	//Step A.1 
void MouseParameters::SetCurrAngle(double zTheta, double yPhi, double xGamma)
{
	zLast = zCurr;
	yLast = yCurr;
	xLast = xCurr;

	zCurr = zTheta;
	yCurr = yPhi;
	xCurr = xGamma;

	updateFlagZ = true;
	updateFlagY = true;
	updateFlagX = true;
}


MouseParameters::MouseParameters(double zTheta, double yPhi, double xGamma)
	:zLast(0.0), yLast(0.0), xLast(0.0), zCurr(zTheta), yCurr(yPhi), xCurr(xGamma), zoomLast(0), zoomCurr(0), updateFlagZ(false), updateFlagY(false), updateFlagX(false), updateFlagZoom(false)
{
}


MouseParameters::~MouseParameters()
{
}
