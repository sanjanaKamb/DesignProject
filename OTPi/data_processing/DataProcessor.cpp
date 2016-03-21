#include "DataProcessor.h"

DataProcessor::DataProcessor(Properties* properties) {
	isOoiDefined = false;
	isRegionDefined = false;
	isSendNotification = false;
	cameraInterface = new CameraInterface(std::stoi(properties->getProperty("CAM_INDEX")));

}

DataProcessor::~DataProcessor() {
	// TODO Auto-generated destructor stub
}

void DataProcessor::initialize() {
	cameraInterface->init();
}

ImgData* DataProcessor::run() {
	//while(true) {
		//cameraInterface->poll()->showImg("Test");
		//TODO: Filter image
		//TODO: Detect objects
		//TODO: Track objects

		//TODO: Show result
	logger->info("polling");
	//return cameraInterface->poll();
	cv::Mat src, src_gray;
	cv::Mat dst, detected_edges, dst_temp;

	int edgeThresh = 1;
	int lowThreshold = 30;
	int const max_lowThreshold = 100;
	int ratio = 3;
	int kernel_size = 3;
	
	
	ImgData* temp = cameraInterface->poll();
	src = temp->getImg();
	dst = src;
	dst_temp.create( src.size(), src.type() );
	cv::cvtColor( src, src_gray, CV_BGR2GRAY );
	cv::blur( src_gray, detected_edges, cv::Size(3,3) );
	cv::Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
	//src = cv::Mat(2, 2, CV_8UC3, cv::Scalar(1,1,1));
	src.copyTo(dst_temp);
	src.setTo(cv::Scalar(255,255,255));
	//dst_temp = cv::Scalar::all(0);
	src.copyTo( dst_temp, detected_edges);
	temp->setImg(dst_temp);

	if(isOoiDefined){
		logger->info("Here in OoiDefined "+std::to_string(ooi.x)+","+std::to_string(ooi.y));
		//distance transform
		if(!isRegionDefined){
			//find contours using ooi point
		}
		isOoiDefined = false;
	}

	if(isRegionDefined){
		//TODO: send alert event if any movement
		isSendNotification=true;
	}

	return temp;

}

