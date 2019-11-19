#pragma once
#include "..\..\ProjectIncludes\ProjectIncludes_Header.h"
#include "..\MouseParameters\MouseParameters.h"
#include "..\Scene3D\Scene3D.h"

class SceneMotion
{
	double theta_z; //rotation clock with Z
	double phi_y; //perspective Y
	double gamma_x;//rotation X

	double scale;
	double fovy;
	double zoom;
	double B_delta_phi;

	double height;
	double angle;

	Scene3D scene;
	threadsafe_queue<Mat> queue;
	
	Mat stripes;

private:

	//method get two 2D imgs and convert them to one 3D img
	//Step B.2
	void setNewImgs(Mat top, Mat down, float _height);

public:

	//send 2 imgs : 1 - top img , 2 - down img
	//Step B.1
	void Convert2D_to_3D(const Mat &top, const Mat &down, float angle,  float height);

private:

	//scene motion main thread
	//Step A.2
	void startSceneMotion(threadsafe_queue<Mat> &saveQueue);

	//run 3d scene motion thread
	//Step A.1
	void init();

public:


	SceneMotion();
	virtual ~SceneMotion();



};

