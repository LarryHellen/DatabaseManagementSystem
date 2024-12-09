//States.h

#ifndef STATES_H
#define STATES_H

#include <map>
#include "StateEnum.h"
class States {
private:
    std::map<StateEnum, bool> _states;

public:
    States();

    void enableState(StateEnum state);
    void disableState(StateEnum state);
    void toggleState(StateEnum state);
    bool checkState(StateEnum state) const;
};



#endif //STATES_H