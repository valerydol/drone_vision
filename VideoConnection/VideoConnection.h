#pragma once
#include "..\ProjectIncludes\ProjectIncludes_Header.h"
#include <iostream>
#include <chrono>
#include <ctime> 
//number of port connector
#define MAX_PORT_RNG 9 

class VideoConnection
{
	VideoCapture cap;
	VideoCapture cap_2;
	int count = 0;
	double_t frameCount = 0;
	int key = 0;
	Mat lastFrame;
public:

	// make unique ptr for return from class
	// must be save with threads
	// we do pair from frame and pressed key
	//step 2.1
	unique_ptr<pair<Mat, int>> GetNewFramePair();

	// make unique ptr for return from class
	// must be save with threads
	//step 2
	unique_ptr<Mat> GetNewFrame();

private:
	//find camera port
	//step 1
	void findPort(int port_num = 0);

	void startVideoStream();

	void init();

public:
	VideoConnection(int port_num = 0);
	virtual ~VideoConnection();

};

