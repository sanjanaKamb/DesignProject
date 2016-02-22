#include "Receiver.h"

Receiver::Receiver(Controller* controller) {
	this->controller = controller;
}

Receiver::~Receiver() {
	// TODO Auto-generated destructor stub
}

std::string Receiver::poll() {
	pthread_mutex_lock(&mutex);
	std::string temp = "";
	if(!buffer.empty()){
		temp = buffer.front();
		logger->trace("New input received");
		buffer.pop();
	}
	pthread_mutex_unlock(&mutex);
	return temp;
}

void Receiver::start() {
	pthread_create(&thread, NULL, &Receiver::runEntry, this);
}

void* Receiver::run() {
	logger->info("Starting Receiver Thread execution loop");
	while (Controller::isRunning()){
		pthread_mutex_lock(&mutex);
		//TODO: Copy implementation here
		pthread_mutex_unlock(&mutex);
	}

	pthread_exit(NULL);
}

void* Receiver::runEntry(void* self) {
	return static_cast<Receiver*>(self)->run();
}
