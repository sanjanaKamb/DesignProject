#ifndef STORAGE_OBJECTMETADATA_H_
#define STORAGE_OBJECTMETADATA_H_

#include "../util/data/ImgData.h"

#include <opencv2/video/tracking.hpp>

class ObjectMetaData {
public:
	ObjectMetaData();
	ObjectMetaData(int id, ImgData* image);
	virtual ~ObjectMetaData();

	void initialize();

	void predict();

	void update();

	ImgData* getImage();

	void setImage(ImgData* image);

private:
	//TODO: Insert metadata here

	int id;

	ImgData* image;

	cv::KalmanFilter kalmanFilter;

	cv::Mat_<float> measurement;

};

#endif /* STORAGE_OBJECTMETADATA_H_ */
