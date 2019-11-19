#include "DataAndCommandReceiver.h"


DataAndCommandReceiver::DataAndCommandReceiver()
	:last(0.0F, 0.0F)
{
}


DataAndCommandReceiver::~DataAndCommandReceiver()
{
}

//we need decode pressed key
//int can be ( -1 ) , this can thraw exception if we 
//try find ascii code of(-1)
//step A.1
COMMAND DataAndCommandReceiver::detectPressedKey(int key_num)
{
	//get last key press
	//step 1
	key_num = (key_num > -1) ? key_num : oldKey;


	if (key_num == KEY_CODE_DEFAULT)
		return DEFAULT;

	if (key_num == KEY_CODE_NEW_ROI)
		return ROI_NEW;

	if (key_num == KEY_CODE_DO_ROI_SMALLER)
		return ROI_SMALLER;

	if (key_num == KEY_CODE_DO_ROI_BIGGER)
		return ROI_BIGGER;

	if (key_num == KEY_CODE_LAST_SIZE)
		return ROI_LAST_SIZE;

	if (key_num == KEY_CODE_PAUSE)
	{
		system("pause");
		return DEFAULT;
	}


	if (key_num == KEY_CODE_QUIT)
	{
		cout << "EXIT" << endl;
		exit(0);
	}

	return DEFAULT;
}

//receive data and pressed key number
//Step A.0
void DataAndCommandReceiver::SetNewPairFrameKey(unique_ptr<pair<Mat, int>> data_ptr)
{

	pair<Mat, int> data = *data_ptr.get();
	Mat temp = data.first.clone();
	Mat tempBlack(300, 300, CV_64FC3, COLOR_BLACK);

	COMMAND key = detectPressedKey(data.second);


	if ((key == ROI_NEW) || (key == ROI_BIGGER) || (key == ROI_SMALLER) || (key == ROI_LAST_SIZE) || (key == DEFAULT))
	{
		processingCommand.SetFrame(data.first, dataAccumulate, key);
	}

	if (dataAccumulate.GetScene_GoodPoint2F_vector_ref().empty())
	{
		//no matching
		painter.drawGreenRedDetectorPoint(temp, COLOR_RED);
	}
	else
	{
		painter.drawGreenRedDetectorPoint(temp, COLOR_GREEN);
		//we have matching

		if ((int)dataAccumulate.GetRoi_GoodPoint2F_new_coordinates_vector_ref().size() > 4)
		{
			float angle = 0;
			float height = 0;
			pair<int, int> direction;

		
			postProcessing.SetDataToGetAngleDirectionHeight(dataAccumulate, angle, height, direction);



			//Get movment direction arrow
			//pair<int, int> direction = directionArrow.GetDirectionArrow(dataAccumulate.GetRoi_GoodPoint2F_new_coordinates_vector_ref()[1], dataAccumulate.GetScene_GoodPoint2F_vector_ref()[1]);
			//painter.drawMovmentArrow(temp, direction);

			try {

				if (isContourConvex(dataAccumulate.getSetVectorOfBoardSceneCorners_ref()))
				{
					dataBinding.InsertDataForBinding(angle, height, direction);
				}
				else
				{
					cout << "NOT in isContourConvex" << endl;
				}
			}
			catch (Exception ex)
			{
				cout << "Exseption isContourConvex " << endl;
			}


		}

	}

	try {
		painter.drawPoligonBody(temp, dataAccumulate.getSetVectorOfBoardSceneCorners_ref(), COLOR_YELLOW);
		painter.drawPoligonBody(temp, dataAccumulate.getSetVectorOfBoardRoiCorners_ref(), COLOR_RED);

		//painter.drawVectorOfPoint2F(dataAccumulate.getSetVectorOfBoardSceneCorners_ref(), temp, COLOR_GREEN);
		//painter.drawRoiBoard(temp, dataAccumulate.getOffsetRoi_X(), dataAccumulate.getOffsetRoi_Y(), dataAccumulate.getRoiWidth_X(), dataAccumulate.getRoiHeight_Y());
		//
		imshow("video", temp);
		waitKey(1);

	}
	catch (Exception ex)
	{
		cout << "EXCEPTION EX " << ex.msg << endl;
		system("pause");
	}
	
}
