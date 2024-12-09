#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <string>
#include <vector>
#include <map>
#include <set>

class StateMachine {
public:
    StateMachine();
    bool validate(const std::vector<std::string> &tokens) const;

private:
    std::map<std::string, std::set<std::string>> transitions;
    bool isWildcard(const std::string &state) const;
};

#endif // STATEMACHINE_H
