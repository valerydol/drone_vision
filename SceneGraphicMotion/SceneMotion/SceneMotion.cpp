#include "SceneMotion.h"

//mouse motion receiver
void MauseCallBackFunction(int event, int x, int y, int flags, void *userdata)
{

	if (flags == (EVENT_LBUTTONDOWN))
	{
		(*(MouseParameters*)userdata).SetCurrAngle((double)x, (double)y, (double)(x + y));
	}
	else
	{
		(*(MouseParameters*)userdata).SetCurrAngle(0, 0, 0);
	}

	if (flags == EVENT_RBUTTONDOWN)
	{
		(*(MouseParameters*)userdata).SetZoom(y);
	}
	else
	{
		(*(MouseParameters*)userdata).SetZoom(0);
	}


}


//method get two 2D imgs and convert them to one 3D img
//Step B.2
void  SceneMotion::setNewImgs(Mat top, Mat down, float _height)
{
	Mat  srcDst_A = top.clone();
	Mat  srcDst_B = down.clone();

	scene.WrapTopDownImages(top, down,
		theta_z,
		B_delta_phi + phi_y,
		gamma_x,
		scale,
		fovy,
		srcDst_A,
		srcDst_B,
		zoom,
		_height
	);

#pragma region threads not in use
	//std::thread thread_A(&Scene3D::WarpImage,
//	&scene,
//	top.clone(),
//	theta_z,
//	B_delta_phi + phi_y,
//	gamma_x,
//	scale,
//	fovy,
//	std::ref(srcDst_A),
//	zoom,
//	_height,
//	TOP);

//std::thread thread_B(&Scene3D::WarpImage,
//	&scene,
//	down.clone(),
//	theta_z,
//	B_delta_phi + phi_y,
//	gamma_x,
//	scale,
//	fovy,
//	std::ref(srcDst_B),
//	zoom,
//	_height,
//	DOWN);

//if (thread_A.joinable())
//	thread_A.join();

//if (thread_B.joinable())
//	thread_B.join();

#pragma endregion

	Mat Scene_dst(srcDst_A - srcDst_B);

	//save thread queue
	queue.push(Scene_dst);

}




//send 2 imgs : 1 - top img , 2 - down img
//Step B.1
void SceneMotion::Convert2D_to_3D(const Mat &top, const Mat &down, float _angle, float _height)
{
	//clone imgs 
	Mat tempTop(top.clone());
	Mat tempDown(down.clone());

	angle = _angle;
	height = _height;
	//Step B.2
	std::thread setImgsThread(&SceneMotion::setNewImgs, this, tempTop, tempDown, height);
	setImgsThread.detach();

}

//scene motion main thread
//Step A.2
void SceneMotion::startSceneMotion(threadsafe_queue<Mat> &saveQueue)
{
	const string WINDOW_NAME = "Scene 3D";
	MouseParameters userData;

	namedWindow(WINDOW_NAME, WINDOW_KEEPRATIO);
	moveWindow(WINDOW_NAME, 3000, 100);

	Mat scene3D(400,400, CV_64FC3, COLOR_BLACK);
	Mat last(scene3D.clone());

	setMouseCallback(WINDOW_NAME, MauseCallBackFunction, &userData);

	int key = 0;
	int w = 0;
	int h = 0;
	double scale = 1.0;
	while (!queue.try_pop(last))
	{
		w = last.cols;
		h = last.rows;
		last.release();
		last = scene3D.clone();
		break;
	}

			
	while (true)
	{
		Mat tempNewMat;

		theta_z += userData.GetZ();
		phi_y += userData.GetY();
		float tempZoom = userData.GetZoom();

		if (zoom >= 0.2 || tempZoom > 0)
		{
			zoom += tempZoom;
		}
			

		if (!queue.try_pop(tempNewMat))
		{
			last.release();
			last = tempNewMat.clone();

		}
		Rect window = getWindowImageRect(WINDOW_NAME);
		if (window.width != w || window.height != h) {
			scale = (double)w / (double)window.width;
			w /= scale;
			h /= scale;
			resizeWindow(WINDOW_NAME, (int)(w), (int)(h));
		}
		if (!last.empty())
		{
			
			putText(tempNewMat, "Zoom  : " + to_string(zoom), Point2f(20, 20), FONT_HERSHEY_PLAIN, 1, COLOR_YELLOW, 1, 1);
			putText(tempNewMat, "Angle : " + to_string(angle), Point2f(20, 40), FONT_HERSHEY_PLAIN, 1, COLOR_YELLOW, 1, 1);
			putText(tempNewMat, "Height: " + to_string(height), Point2f(20, 60), FONT_HERSHEY_PLAIN, 1, COLOR_YELLOW, 1, 1);

			imshow(WINDOW_NAME, tempNewMat);
		}

		key = waitKey(1);

		if (key == 112)
			system("pause");

		tempNewMat.release();
	}
}



//run 3d scene motion thread
//Step A.1
void SceneMotion::init()
{
	//Step A.2
	std::thread sceneThread(&SceneMotion::startSceneMotion, this, std::ref(this->queue));
	sceneThread.detach(); //release thread 
}


SceneMotion::SceneMotion()
	: theta_z(-15.0), phi_y(-15.0), gamma_x(0.0), scale(1.0), fovy(10.0), zoom(1.0), B_delta_phi(90.0), height(50.0), angle(0.0), scene(), queue()
{
	//Step A.1
	init();
}


SceneMotion::~SceneMotion()
{
}
