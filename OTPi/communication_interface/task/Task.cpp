#include "../../communication_interface/task/Task.h"

Task::~Task() {
    for(int i = 0 ; i < taskList.size() ; i++) {
        delete taskList[i];
    }
}
