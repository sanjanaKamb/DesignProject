#ifndef TASKFACTORY_H_
#define TASKFACTORY_H_

#include <string>
#include "../../communication_interface/task/Task.h"
#include "../../communication_interface/task/TurnTask.h"


class TaskFactory {
public:
    /**
     * Contructor
     */
    TaskFactory();

    /**
     * given a string, dynamically create new Tasks
     * @param input the name of the new task
     */
    static Task* newTask(const std::string input);

    /**
     * Destructor
     */
    virtual ~TaskFactory();

};

#endif /* SUBZERO_SRC_CONTROLLER_COMMAND_TASKFACTORY_H_ */
