#ifndef TASK_H_
#define TASK_H_

#include <vector>

class Task {
    public:
        //The Task class is purely virtual (abstract)
        virtual ~Task();

        virtual void execute() = 0;

    protected:
       std::vector<Task*> taskList;
};

#endif /* TASK_H_ */
