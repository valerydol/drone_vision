#include "VideoConnection/VideoConnection.h"
#include "DataAndCommandReceiver/DataAndCommandReceiver.h"
#include"ProjectIncludes/ProjectIncludes_Header.h"	


int main()
{

	VideoConnection video;
	DataAndCommandReceiver receiver;
	
	
	while (true)
	{
	
		
		//call main class
		unique_ptr<pair<Mat, int>> frame(video.GetNewFramePair());
		pair<Mat, int> data = *frame.release();
		if (!data.first.empty())
		{
			receiver.SetNewPairFrameKey(make_unique<pair<Mat, int>>(data));
		
		}
		
		//receiver.SetNewPairFrameKey(video.GetNewFramePair());

	}

	return 0;

}