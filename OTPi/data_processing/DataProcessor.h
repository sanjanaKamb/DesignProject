#ifndef DATA_PROCESSING_DATAPROCESSOR_H_
#define DATA_PROCESSING_DATAPROCESSOR_H_

#include "../camera/CameraInterface.h"
#include "../util/Properties.h"
#include "../storage/ObjectStorage.h"
#include "../util/data/ImgData.h"

class DataProcessor {
public:
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
