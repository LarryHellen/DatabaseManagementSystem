// States.cpp
#include "States.h"
#include <iostream>

States::States()
{
    for(int i=0; i<LAST_STATE; i++) {
        _states[static_cast<StateEnum>(i)] = false;
    }
}

void States::enableState(StateEnum state)
{
    _states[state] = true;
}

void States::disableState(StateEnum state)
{
    _states[state] = false;
}

void States::toggleState(StateEnum state)
{
    _states[state] = !_states[state];
}

bool States::checkState(StateEnum state) const
{
    return _states.at(state);
}
