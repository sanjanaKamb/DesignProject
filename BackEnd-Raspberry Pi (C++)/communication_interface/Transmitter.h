#ifndef COMMUNICATION_INTERFACE_TRANSMITTER_H_
#define COMMUNICATION_INTERFACE_TRANSMITTER_H_
#define byte uint8_t
#include <string>
#include <queue>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include "../util/Logger.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "controllers/Controller.h"

using namespace std;
using namespace cv;
class Controller;
class Transmitter {
public:
	Transmitter(int fd);
	virtual ~Transmitter();

	void send(cv::Mat message);

	void start();

	void* run();

	/**
	 * Trampoline function
	 */
	static void* runEntry(void* self);
	DataProcessor* dataProcessor;
private:

	int connfd;

	Logger* logger = new Logger("Transmitter");

	//std::queue<std::string> buffer;
        
        std::queue<cv::Mat> buffer;

	pthread_mutex_t mutex;

	pthread_t thread;
};

#endif /* COMMUNICATION_INTERFACE_TRANSMITTER_H_ */
