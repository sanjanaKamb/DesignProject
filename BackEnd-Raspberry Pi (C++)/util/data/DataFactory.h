/*
 * DataFactory.h
 *
 *  Created on: Mar 17, 2015
 *      Author: ahsueh1996
 */

#ifndef DATAFACTORY_H_
#define DATAFACTORY_H_
#include "ImgData.h"

/**
 * This factory holds static functions for others to
 * create data class objs.
 */
class DataFactory {

public:

	/**
	 * New ImgData object created. Takes the data required by
	 * ImgData and returns a ImgData*.
	 *
	 * @param imgID	of the image
	 * @param Mat 	pointer of the actual image object
	 * @return 		pointer to the newly made ImgData obj
	 */
    static ImgData* createImgData(std::string imgID, cv::Mat img);

};

#endif /* DATAFACTORY_H_ */
