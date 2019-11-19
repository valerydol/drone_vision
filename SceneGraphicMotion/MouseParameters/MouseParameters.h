#pragma once
#include "..\..\ProjectIncludes\ProjectIncludes_Header.h"
class MouseParameters
{
private:

	double zLast;
	double yLast;
	double xLast;


	double zCurr;
	double yCurr;
	double xCurr;

	
	int zoomLast;
	int zoomCurr;

	bool updateFlagZ ;
	bool updateFlagY ;
	bool updateFlagX ;
	bool updateFlagZoom ;

	

public:



	//Step C.2
	float GetZoom();

	//Step C.1
	void SetZoom(int zoom);

	//return Difference between old and new params
	//Step B.1
	float GetZ();

	//Step B.2
	float GetY();



	//set current angle 
	//Step A.1 
	void SetCurrAngle(double zTheta, double yPhi, double xGamma);


	MouseParameters(double zTheta = 0, double yPhi = 0, double xGamma = 0);

	virtual ~MouseParameters();


};

