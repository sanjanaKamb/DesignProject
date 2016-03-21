#ifndef DATA_PROCESSING_DATAPROCESSOR_H_
#define DATA_PROCESSING_DATAPROCESSOR_H_

#include "../camera/CameraInterface.h"
#include "../util/Properties.h"
#include "../storage/ObjectStorage.h"
#include "../util/data/ImgData.h"

class DataProcessor {
public:
	bool isOoiDefined; //TODO: set this to true
	bool isRegionDefined;
	bool isSendNotification;
	cv::Point ooi; //TODO: ooi.x .. ooi.y setPoint
	cv::Point topleft;
	cv::Point topright;
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
