#ifndef DATA_PROCESSING_DATAPROCESSOR_H_
#define DATA_PROCESSING_DATAPROCESSOR_H_

#include "../camera/CameraInterface.h"
#include "../util/Properties.h"
#include "../storage/ObjectStorage.h"
#include "../util/data/ImgData.h"

class DataProcessor {
public:
	bool isOoiDefined = false; //TODO: set this to true
	bool isRegionDefined = false;
	bool isSendNotification = false;
	bool isFirstFrameDefined = false;
	bool sentOnce = false;
	int cropCounter = 0;
	cv::Point ooi; //TODO: ooi.x .. ooi.y setPoint
	cv::Point topleft;
	cv::Point topright;
	cv::Mat first_frame;
	DataProcessor(Properties* properties);
	virtual ~DataProcessor();

	void initialize();

	ImgData* run();

private:
	CameraInterface* cameraInterface;
	Logger* logger = new Logger("DataProcessor");

	ObjectStorage* storage;

	ImgData* result;
};

#endif /* DATA_PROCESSING_DATAPROCESSOR_H_ */
