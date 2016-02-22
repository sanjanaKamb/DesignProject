#include "../../communication_interface/controllers/Controller.h"

#include <iostream>
#include "../../communication_interface/controllers/ControllerThread.h"

bool Controller::running = false;

Controller::Controller() {
    logger->info("Constructor controller");
    taskList = new std::queue <class Task* >();
    mutex = PTHREAD_MUTEX_INITIALIZER;
    cT = new ControllerThread(taskList, &mutex);
    receiver = new Receiver(this);
    transmitter = new Transmitter(5001);

}

void Controller::initialize(void) {
    logger->info("Initializing Controller");
    cT->start();
    receiver->start();
    transmitter->start();
    running = true;
}

Controller::~Controller() {
	//Destructor to free pointers
    stop();
    delete taskList;
    delete logger;
}

void Controller::setDataProcessor(DataProcessor *dataProcessor){
    this->dataProcessor = dataProcessor;
}

void Controller::run(){
	/*while(true){
		dataProcessor->run()->showImg("Test");
    	}*/

    while(true){
        ImgData* imgData = dataProcessor->run();
            cv::Mat matFrame= imgData->getImg();
	logger->info("sending to transmitter");
        transmitter->send(matFrame);
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

        //std::vector<uchar> buff;
        /*vector<int> params;
        params.push_back(cv::IMWRITE_JPEG_QUALITY);
        //80 keeps the image size under 64KB ,ON MY CAMERA, so I can send the image in one piece
        params.push_back(80);*/
        
        //encode the mat
        /*bool encodeImage = cv::imencode(".jpg", matFrame, buff);
        if(!encodeImage){
            logger->error("Failed to encode video frame");
        }*/
       // uchar* frameBuf = &buff[0];
       // std::string frameString(reinterpret_cast<char*>(frameBuf)); 
        
      //  push frame converted to string into transmits buffer
       // transmitter->send(buff);

	
    
}

bool Controller::isRunning() {
    return running;
}

void Controller::stop() {
    running = false;
    while(!taskList->empty()) {
        Task *temp = taskList->front();
        if (temp != NULL) {
        	taskList->pop();
        }
    }
}


void Controller::addTaskToQueue(Task *newTask)
{
    logger->trace("Requesting mutex lock to add task");
    pthread_mutex_lock(&mutex);
    logger->trace("Lock request successful");
    taskList->push(newTask);
    logger->trace("Enqueued new task");
    pthread_mutex_unlock(&mutex);
    logger->trace("Unlocking mutex");

}
