#include "VideoConnection.h"
auto start = std::chrono::system_clock::now();
// Some computation here

VideoConnection::VideoConnection(int port_num)
	:cap(port_num), cap_2("video12.mp4")
{

	findPort();
	init();
}


VideoConnection::~VideoConnection()
{
	if (cap.isOpened())
	{
		cap.release();
		cout << "Camera is disconnected" << endl;
	}
}



void  VideoConnection::startVideoStream()
{
	const string VIDEO_STREAM("Stream");
	//namedWindow(VIDEO_STREAM, WINDOW_AUTOSIZE);
	namedWindow(VIDEO_STREAM, WINDOW_KEEPRATIO );
	//namedWindow(VIDEO_STREAM, WINDOW_NORMAL );


	moveWindow(VIDEO_STREAM, 2200, 100);
	Mat frameTest;
	cap_2 >> frameTest;
	int w = frameTest.cols;
	int h = frameTest.rows;
	double scale = 1.0;
	while (true)
	{
		//double fps = cap_2.get(CAP_PROP_FPS);
		auto end = std::chrono::system_clock::now();

		std::chrono::duration<double> elapsed_seconds = end - start;
		start = end;
		frameCount += (double)elapsed_seconds.count() * 1000;
		pair<Mat, int> data; //returned data

		// set frame position
		cap_2.set(CAP_PROP_POS_MSEC, frameCount + 5000);

		Mat frame;
		cap_2 >> frame;
		lastFrame = frame.clone();
		Rect window =getWindowImageRect(VIDEO_STREAM);
		if (window.width != w || window.height != h) {
			scale = (double)w / (double)window.width;
			w/=scale;
			h /= scale;
			cout << window.size() << endl;
			resizeWindow(VIDEO_STREAM, (int)(w ),(int) (h));
		}
		
		imshow(VIDEO_STREAM, frame);
		key = waitKey(1); // pressed key

	}
	destroyWindow(VIDEO_STREAM);
}

void VideoConnection::init()
{
	std::thread videoStream(&VideoConnection::startVideoStream, this);
	videoStream.detach(); //release thread 
}

// make unique ptr for return from class
// must be save with threads
// we do pair from frame and pressed key
//step 2.1
unique_ptr<pair<Mat, int>>VideoConnection::GetNewFramePair()
{
	count++;
	pair<Mat, int> data; //returned data
	Mat frame;

	if (count == 3)
	{
		count = 0;
		data = make_pair(lastFrame, 51);
		return make_unique<pair<Mat, int>>(data);
	}

	data = make_pair(lastFrame, key);
	return make_unique<pair<Mat, int>>(data);
}



// make unique ptr for return from class
// must be save with threads
//step 2
unique_ptr<Mat> VideoConnection::GetNewFrame()
{

	Mat frame;
	cap >> frame;

	return make_unique<Mat>(frame);
}



//we need coonect our web camera
//step 1 
void VideoConnection::findPort(int port_num)
{
	for (int i = port_num; i < MAX_PORT_RNG; i++)
	{
		cout << "try connect to webcam" << endl;
		if (cap.isOpened())
		{
			cout << "connect to port : " << port_num << endl;
			return;
		}
		cap = VideoCapture(i);
	}
}