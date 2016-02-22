#include "CameraInterface.h"
#include <string>


/* ==========================================================================
 * 				INTERACTING WITH DATA COMING IN (FROM Camera)
 * ==========================================================================
 * This interface class will be automatically polling and managing
 * the polling process privately within the interface at pollFrequency
 * using the functions below.
 */

/**
 * Poll raw data from the camera.
 * @return	data polled
 */
ImgData* CameraInterface::poll() {
    ImgData* new_data;
    cv::Mat raw;
    bool readSuccess = true; 
    //TODO: WHATS THE POINT OF READSUCCESS?????

    camStream.grab();

    camStream.retrieve(raw);

    if (readSuccess) {
        logger->info("Read successful");
        new_data = decode(raw);
    } else {
        logger->error("Camera stream failed to read image");
        cv::Mat temp = cv::Mat::zeros(640, 480, CV_8UC3);
        new_data = new ImgData("raw", temp);
        logger->debug("Inserting an artificial blank image");
    }

    return new_data;
}

/**
 * Decode the data.
 * @param	data	data to be decoded
 * @return	decoded data in a ImgData format
 */
ImgData* CameraInterface::decode(cv::Mat data) {
    if (data.cols <= 0) {
        data = cv::Mat::zeros(640, 480, CV_8UC3);
	logger->debug("No columns in image data.");
    }    
    //cv::cvtColor(data, data, cv::COLOR_BGR2RGB);
    ImgData* decoded = new ImgData("raw", data);
    return decoded;
}

/* ==========================================================================
 * 								GETTERS AND SETTERS
 * ==========================================================================
 */

int CameraInterface::getPosition() {
    return position;
}

/* ==========================================================================
 * 							CONSTRUCTOR AND DESTRUCTOR
 * ==========================================================================
 */


CameraInterface::CameraInterface(int position) {
    this->position = position;
}

void CameraInterface::init() {
    // thread for reading and polling camera input
    logger->info("Initializing camera");
    // Set camera parameters
    camStream.set(CV_CAP_PROP_FORMAT, CV_8UC3);
    logger->info("Opening video capture stream at position " + std::to_string(position));
    if (!camStream.open()) {
        logger->error("Failed to open video capture stream, exiting now. Make sure camera(s) are plugged in.");
	        exit(0);
    }
    
	
}

CameraInterface::~CameraInterface() {
    camStream.release();
    logger->trace("CameraInterface deleted");
    delete logger;
}

