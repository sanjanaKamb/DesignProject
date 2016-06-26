#include "ObjectMetaData.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

ObjectMetaData::ObjectMetaData() {
	// TODO Auto-generated constructor stub

}

ObjectMetaData::ObjectMetaData(int id, ImgData* image) {
	this->id = id;
	this->image = image;
	kalmanFilter = *(new cv::KalmanFilter(4, 2, 0));

}

ObjectMetaData::~ObjectMetaData() {
	// TODO Auto-generated destructor stub
}

void ObjectMetaData::initialize() {
	kalmanFilter.transitionMatrix = (cv::Mat_<float>(4, 4) << 1,0,1,0,  0,1,0,1,  0,0,1,0,  0,0,0,1);
	measurement = *(new cv::Mat_<float>(2,1));
	measurement.setTo(cv::Scalar(0));

	kalmanFilter.statePost.at<float>(0) = 0;
	kalmanFilter.statePost.at<float>(1) = 0;
	kalmanFilter.statePost.at<float>(2) = 0;
	kalmanFilter.statePost.at<float>(3) = 0;
	setIdentity(kalmanFilter.measurementMatrix);
	setIdentity(kalmanFilter.processNoiseCov, cv::Scalar::all(1e-4));
	setIdentity(kalmanFilter.measurementNoiseCov, cv::Scalar::all(10));
	setIdentity(kalmanFilter.errorCovPost, cv::Scalar::all(.1));
}

void ObjectMetaData::predict() {
	cv::Mat prediction = kalmanFilter.predict();
	cv::Point predictPt(prediction.at<float>(0),prediction.at<float>(1));
}

void ObjectMetaData::update() {
	//TODO: Update measurement
	cv::Mat estimated = kalmanFilter.correct(measurement);

}

ImgData* ObjectMetaData::getImage() {
	return image;
}

void ObjectMetaData::setImage(ImgData* image) {
	this->image = image;
}
