#ifndef COMMUNICATION_INTERFACE_RECEIVER_H_
#define COMMUNICATION_INTERFACE_RECEIVER_H_

#include <string>
#include <queue>
#include <pthread.h>
#include <stdlib.h> 


#include "controllers/Controller.h"

class Controller;
using namespace std;
class Receiver {


public:
	Receiver(int fd);
	virtual ~Receiver();

	/**
	 * Polls the buffer and returns  first instance of string
	 *
	 * @return std::string null if buffer is empty
	 */
	std::string poll();
	std::string removespace(string line);

	void start();

	void* run();

	/**
	 * Trampoline function
	 */
	static void* runEntry(void* self);
	DataProcessor* dataProcessor;


private:
	int connfd;

	Logger* logger = new Logger("Receiver");

	Controller* controller;

	std::queue<std::string> buffer;

	pthread_mutex_t mutex;

	pthread_t thread;

};

#endif /* COMMUNICATION_INTERFACE_RECEIVER_H_ */
