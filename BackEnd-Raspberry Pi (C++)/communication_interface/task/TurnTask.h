#ifndef TURNTASK_H_
#define TURNTASK_H_

#include "../../communication_interface/task/Task.h"
#include "../../util/Logger.h"

class TurnTask : public Task {
private:
    Logger* logger = new Logger("TurnTask");
    int* currentTargetYaw;
    int targetYaw;

public:
	/**
	 * Constructor
	 */
    TurnTask();

    void execute();

	/**
	 * Destructor
	 */
    virtual ~TurnTask();

};

#endif /* SUBZERO_SRC_CONTROLLER_TASK_TURNTASK_H_ */
