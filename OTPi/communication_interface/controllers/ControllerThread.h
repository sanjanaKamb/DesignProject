#ifndef CONTROLLERTHREAD_H_
#define CONTROLLERTHREAD_H_

#include <queue>
#include <pthread.h>

#include "../task/Task.h"
#include "../../util/Logger.h"

class ControllerThread {

    public:
        /**
         * Task ControllerThread Constructor
		 *
		 * @param cL - the QQueue from
         * @param mutex - the QMutexd from
		 */
        ControllerThread(std::queue <class Task* > *tL, pthread_mutex_t *mutex);

        virtual ~ControllerThread();

        /**
         * Creates and starts pthread
         */
        void start();

		/**
         * Execute the tasks on the queue
		 *
         * @param
		 */
        void* executeTasks();

        /**
         * Trampoline function
         */
        static void* executeTasksEntry(void* self);

	private:
        Logger* logger = new Logger("ControllerThread");

        /**
         * A pointer to Controller's Queue of tasks
    	 */
        std::queue <class Task* > *taskList;

        /**
         * A pointer to Controller's mutex lock
         */
        pthread_mutex_t *mutex;

        /**
         * Thread
         */
        pthread_t thread;

};

#endif /* CONTROLLERTHREAD_H_ */
