#ifndef COMMUNICATION_INTERFACE_RECEIVER_H_
#define COMMUNICATION_INTERFACE_RECEIVER_H_

#include <string>
#include <queue>
#include <pthread.h>

#include "controllers/Controller.h"

class Controller;

class Receiver {
public:
	Receiver(Controller* controller);
	virtual ~Receiver();

	/**
	 * Polls the buffer and returns  first instance of string
	 *
	 * @return std::string null if buffer is empty
	 */
	std::string poll();

	void start();

	void* run();

	/**
	 * Trampoline function
	 */
	static void* runEntry(void* self);

private:
	Logger* logger = new Logger("Receiver");

	Controller* controller;

	std::queue<std::string> buffer;

	pthread_mutex_t mutex;

	pthread_t thread;

};

#endif /* COMMUNICATION_INTERFACE_RECEIVER_H_ */
