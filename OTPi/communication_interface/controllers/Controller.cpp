#include "../../communication_interface/controllers/Controller.h"

#include <iostream>
#include "../../communication_interface/controllers/ControllerThread.h"

bool Controller::running = false;

Controller::Controller() {
    logger->info("Constructor controller");
    taskList = new std::queue <class Task* >();
    mutex = PTHREAD_MUTEX_INITIALIZER;
    cT = new ControllerThread(taskList, &mutex);

	int listenfd = 0;
        int connfd = 0;
	int port = 5001;
        struct sockaddr_in serv_addr;
        
        listenfd = socket(AF_INET, SOCK_STREAM, 0);
        if(listenfd == -1){
            logger->error("Could not create socket");
            return;
        }
        logger->info("socket retrieve success");
        
        memset(&serv_addr, '0', sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;    
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
        serv_addr.sin_port = htons(port);  
        
        bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
	logger->info("binding done");
        
        if(listen(listenfd, 10) == -1){
            logger->error("Failed to listen");
            return;
        }
        logger->info("done listening");
        connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // accept awaiting request
	logger->info("accepting");
        if (connfd<0){
            logger->error("Accept Failed");
        }

    receiver = new Receiver(connfd);
    transmitter = new Transmitter(connfd);

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
    this->receiver->dataProcessor = dataProcessor;
    this->transmitter->dataProcessor = dataProcessor;

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
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

     
	
    
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
