#include "PostProcessing.h"



PostProcessing::PostProcessing()
{
}


PostProcessing::~PostProcessing()
{
}



//Step A
void PostProcessing::SetDataToGetAngleDirectionHeight(DataAccumulate &dataAccumulate, float &_angle, float & _height, pair<int, int> &_direction)
{
	//check if we have 4 or more "good points"
	//if we don`t have return 
	//step 1
	if ((int)dataAccumulate.GetRoi_GoodPoint2F_new_coordinates_vector_ref().size() < 4)
	{
		return;
	}


	//perspective
	//step 2
	perspectiveCalculations.CalculateCoordinatesOfBoardSidesPoints(dataAccumulate);
	try {

		//check if contour is valid
		//step 3
		if (isContourConvex(dataAccumulate.getSetVectorOfBoardSceneCorners_ref()))
		{
			//calc rotation
			//step 4
			//rotationProcessing.GetRotationAngle(dataAccumulate, _angle);
			std::thread rotationProcessingThread(&RotationProcessing::GetRotationAngle, &rotationProcessing, std::ref(dataAccumulate), std::ref(_angle));

			//step 5
			//Get movment direction arrow
			//_direction = directionArrow.GetDirectionArrow(dataAccumulate.GetRoi_GoodPoint2F_new_coordinates_vector_ref()[1], dataAccumulate.GetScene_GoodPoint2F_vector_ref()[1]);
			int goodPointsCoordinateSize = (int)dataAccumulate.GetRoi_GoodPoint2F_new_coordinates_vector_ref().size();
			std::future< pair<int, int> > direction_1 = std::async(&DirectionArrow::GetDirectionArrow, &directionArrow, dataAccumulate.GetRoi_GoodPoint2F_new_coordinates_vector_ref()[0], dataAccumulate.GetScene_GoodPoint2F_vector_ref()[0]);
			std::future< pair<int, int> > direction_2 = std::async(&DirectionArrow::GetDirectionArrow, &directionArrow, dataAccumulate.GetRoi_GoodPoint2F_new_coordinates_vector_ref()[int(goodPointsCoordinateSize /2)], dataAccumulate.GetScene_GoodPoint2F_vector_ref()[int(goodPointsCoordinateSize / 2)]);
			std::future< pair<int, int> > direction_3 = std::async(&DirectionArrow::GetDirectionArrow, &directionArrow, dataAccumulate.GetRoi_GoodPoint2F_new_coordinates_vector_ref()[goodPointsCoordinateSize -1], dataAccumulate.GetScene_GoodPoint2F_vector_ref()[goodPointsCoordinateSize - 1]);

			
		
			//_direction = directionArrow.GetDirectionArrow(dataAccumulate.GetRoi_GoodPoint2F_new_coordinates_vector_ref()[1], dataAccumulate.GetScene_GoodPoint2F_vector_ref()[1]);


			if (rotationProcessingThread.joinable())
			{
				rotationProcessingThread.join();
			}
			//calc _height
		//step 5
			_height = heightCalculations.CalculateHeight(dataAccumulate, _angle);
			pair<int, int> direction_A = direction_1._Get_value();
			optimalDirection.SetDirection(direction_A);
			pair<int, int> direction_B = direction_2._Get_value();
			optimalDirection.SetDirection(direction_B);
			pair<int, int> direction_C = direction_3._Get_value();
			optimalDirection.SetDirection(direction_C);

			_direction = optimalDirection.GetOptimalDirection();

		}
		else {
			cout << "NOT valid isContourConvex" << endl;
		}

	}
	catch (Exception ex)
	{
		cout << "Exseption isContourConvex " << endl;
	}

}