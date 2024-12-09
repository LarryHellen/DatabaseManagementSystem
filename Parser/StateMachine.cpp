#include "StateMachine.h"

StateMachine::StateMachine() {
    // Common start
    transitions["START"] = {"CREATE", "INSERT", "SELECT"};

    // CREATE query
    // CREATE TABLE table_name (col1,col2...)
    transitions["CREATE"] = {"TABLE"};
    transitions["TABLE"] = {"*CREATE_COLUMNS"};
    // *CREATE_COLUMNS leads to itself or END
    transitions["*CREATE_COLUMNS"] = {"*CREATE_COLUMNS", "END"};

    // INSERT query
    // INSERT INTO table_name (col1, col2) VALUES (val1, val2)
    transitions["INSERT"] = {"INTO"};
    transitions["INTO"] = {"*TABLE"};
    transitions["*TABLE"] = {"*INSERT_COLUMNS"};
    transitions["*INSERT_COLUMNS"] = {"*INSERT_COLUMNS", "VALUES"};
    transitions["VALUES"] = {"*VALUES"};
    transitions["*VALUES"] = {"*VALUES", "END"};

    // SELECT query
    // SELECT col1, col2 FROM table_name
    transitions["SELECT"] = {"*COLUMNS"};
    transitions["*COLUMNS"] = {"*COLUMNS", "FROM"};
    transitions["FROM"] = {"*TABLE"};
    // After *TABLE in SELECT query, we end.
    transitions["*TABLE"].insert("END");
}

bool StateMachine::isWildcard(const std::string &state) const {
    // Wildcards: *COLUMNS, *TABLE, *CREATE_COLUMNS, *INSERT_COLUMNS, *VALUES
    return !state.empty() && state[0] == '*';
}

bool StateMachine::validate(const std::vector<std::string> &tokens) const {
    std::string current_state = "START";
    for (auto &t : tokens) {
        auto it = transitions.find(current_state);
        if (it == transitions.end()) {
            return false; // No transitions from current state
        }
        const auto& nextStates = it->second;

        std::string upper = t;
        for (auto & c : upper) c = (char)std::toupper((unsigned char)c);

        bool matched = false;
        if (nextStates.find(upper) != nextStates.end()) {
            current_state = upper;
            matched = true;
        } else {
            for (auto &ns : nextStates) {
                if (isWildcard(ns)) {
                    current_state = ns;
                    matched = true;
                    break;
                }
            }
        }

        if (!matched) {
            return false;
        }
    }

    if (current_state == "END") {
        return true;
    }

    auto it = transitions.find(current_state);
    if (it != transitions.end()) {
        if (it->second.find("END") != it->second.end()) {
            return true;
        }
    }

    return false;
}
