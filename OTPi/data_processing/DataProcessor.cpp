#include "DataProcessor.h"

DataProcessor::DataProcessor(Properties* properties) {
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
	return cameraInterface->poll();
	/*cv::Mat src, src_gray;
	cv::Mat dst, detected_edges, dst_temp;

	int edgeThresh = 1;
	int lowThreshold = 50;
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
	src.copyTo( dst, detected_edges);
	temp->setImg(dst);

	return temp;*/

}

