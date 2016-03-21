#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <pthread.h>
#include <queue>

#include "../../data_processing/DataProcessor.h"
#include "../../communication_interface/controllers/ControllerThread.h"
#include "../../communication_interface/task/Task.h"
#include "../../communication_interface/task/TaskFactory.h"
#include "../../util/data/ImgData.h"
#include "../../util/Logger.h"
#include "../../util/Properties.h"
#include "../Receiver.h"
#include "../Transmitter.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <chrono>
#include <thread>



class Receiver;
class Transmitter;

class Controller {

	public:	 

        static bool running;

        /**
         * Empty Constructor
         */
        Controller();

		/**
		 * Destructor
		 */
		virtual ~Controller();

        /**
         * Set local variable dataProcessor
         *
         * @param dataProcessor - reference to dataProcessor
         */
        void setDataProcessor(DataProcessor *dataProcessor);

		/**
         * Adds a new Task to our queue
		 *
         * @param newTask - the Task pointer to be added to queue
		 */
        void addTaskToQueue(Task *newTask);

		/**
		 * Clears all Commands from our queue
		 */
		void clearQueue(void);

        /**
         * Initializes our Controller
         */
        void initialize(void);


        void run();

        /**
         * Returns controller's current running state;
         */
        static bool isRunning();

    protected:
        void stop();

	private:
        Logger* logger = new Logger("Controller");

        ControllerThread *cT;

        Receiver* receiver;

        Transmitter* transmitter;

        DataProcessor* dataProcessor;

		/**
        * A Queue of commands View tells us to complete
		*/
        std::queue <class Task* >* taskList;

        /**
         * A mutex lock that will make our writes thread safe.
         */
        pthread_mutex_t mutex;
};

#endif /* CONTROLLER_H_ */
