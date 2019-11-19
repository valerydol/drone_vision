#include "DataAccumulate.h"


DataAccumulate::DataAccumulate()
{
}


DataAccumulate::~DataAccumulate()
{
}

//calculate all ROI board Coordinates
void DataAccumulate::CalculateAllRoiBoardCoordinates()
{
	this->roiBoardCornerPoints2f.clear();
	Point2f A(offset_roi_x, offset_roi_y); 
	SetRoiBoardCoordinates_A_TopL( A );

	roiBoardCornerPoints2f.push_back (A);
	

	Point2f B(A.x + width_roi_x, A.y);
	SetRoiBoardCoordinates_B_TopR(B);
	roiBoardCornerPoints2f.push_back(B); 

	Point2f C(B.x, B.y + height_roi_y);
	SetRoiBoardCoordinates_C_BotR(C);
	roiBoardCornerPoints2f.push_back(C);

	Point2f D(A.x, C.y);
	SetRoiBoardCoordinates_D_BotL(D);
	roiBoardCornerPoints2f.push_back(D);

}
