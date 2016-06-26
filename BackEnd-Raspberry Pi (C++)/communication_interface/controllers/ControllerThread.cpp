#include "ControllerThread.h"
#include "Controller.h"

ControllerThread::ControllerThread(std::queue<Task *> *tL, pthread_mutex_t *mutex){
    taskList = tL;
    this->mutex = mutex;
}

ControllerThread::~ControllerThread() {
    delete logger;
}

void ControllerThread::start() {
	pthread_create(&thread, NULL, &ControllerThread::executeTasksEntry, this);
}

void* ControllerThread::executeTasks() {
    logger->info("Starting Controller Thread execution loop");
    while (Controller::isRunning()){
    	pthread_mutex_lock(mutex);
        if(!taskList->empty()){
            Task *temp = taskList->front();
            logger->trace("Executing new task");
            temp->execute();
            taskList->pop();
        }
        pthread_mutex_unlock(mutex);
    }

    pthread_exit(NULL);
}

void* ControllerThread::executeTasksEntry(void* self) {
	return static_cast<ControllerThread*>(self)->executeTasks();
}
