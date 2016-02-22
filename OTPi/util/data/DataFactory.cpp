/*
 * DataFactory.cpp
 */

#include "DataFactory.h"

ImgData* DataFactory::createImgData(std::string imgID, cv::Mat img) {
	return new ImgData(imgID,img);
}
