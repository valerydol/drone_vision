#pragma once
#include "..\..\ProjectIncludes\ProjectIncludes_Header.h"
#include "..\..\DataAccumulate\DataAccumulate.h"
#include "..\..\MathCalculations\MathCalculations.h"

class HeightCalculations
{
private:

	//last Area that recived
	double lastArea = 0.0;
	double corrArea = 0.0;

	float Height = 0.0F;
	int count = 0;

	float lastAngle = 0.0F;
	float corrAngle = 0.0F;
	MathCalculations mathCalculations;

private :
	//base operations
	//Step B.2
	void updateData();

	//calculate Coefficient
	//Step B.1
	void calcCoefficient();
public:


	HeightCalculations();
	virtual ~HeightCalculations();

	//start calculate Height Coefficient
	//and then return this Coefficient
	//Step A
	float CalculateHeight( DataAccumulate &dataAccumulate, const float &_corrAngle);


};

