#include "QueryParser.h"
#include "StateMachine.h"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <stdexcept>

bool QueryParser::validate(const std::string &query) {
    std::vector<std::string> tokens = splitTokens(query);
    StateMachine sm;
    return sm.validate(tokens);
}

std::map<std::string, std::string> QueryParser::tokenize(const std::string &query) {
    std::map<std::string,std::string> dbTokens;
    std::vector<std::string> tokens = splitTokens(query);

    if (tokens.empty()) {
        throw std::runtime_error("Empty query.");
    }

    std::string command = toUpper(tokens[0]);
    dbTokens["command"] = command;

    if (command == "SELECT") {
        parseSelectTokens(tokens, dbTokens);
    } else if (command == "CREATE") {
        parseCreateTokens(tokens, dbTokens);
    } else if (command == "INSERT") {
        parseInsertTokens(tokens, dbTokens);
    } else {
        throw std::runtime_error("Unsupported command: " + command);
    }

    return dbTokens;
}

std::vector<std::string> QueryParser::splitTokens(const std::string &query) {
    std::string q = query;
    // Insert spaces around parentheses and commas to split easily
    for (size_t i = 0; i < q.size(); i++) {
        if (q[i] == '(' || q[i] == ')' || q[i] == ',') {
            q.insert(i, " ");
            i++;
            q.insert(i+1, " ");
            i++;
        }
    }

    std::stringstream ss(q);
    std::string token;
    std::vector<std::string> tokens;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

std::string QueryParser::toUpper(const std::string &str) const {
    std::string up = str;
    for (size_t i = 0; i < up.size(); ++i) {
        up[i] = std::toupper(static_cast<unsigned char>(up[i]));
    }
    return up;
}

void QueryParser::parseSelectTokens(const std::vector<std::string> &tokens, std::map<std::string, std::string> &dbTokens) {
    size_t fromPos = 0;
    for (size_t i = 0; i < tokens.size(); i++) {
        if (toUpper(tokens[i]) == "FROM") {
            fromPos = i;
            break;
        }
    }

    if (fromPos == 0) {
        throw std::runtime_error("SELECT query missing FROM clause.");
    }

    if (fromPos+1 >= tokens.size()) {
        throw std::runtime_error("SELECT query missing table name.");
    }

    std::string table = tokens[fromPos+1];
    dbTokens["table"] = table;

    std::vector<std::string> cols;
    for (size_t i = 1; i < fromPos; i++) {
        if (tokens[i] == ",") continue;
        cols.push_back(tokens[i]);
    }

    std::string colStr;
    for (size_t i = 0; i < cols.size(); i++) {
        if (i > 0) colStr += ",";
        colStr += cols[i];
    }

    if (colStr.empty()) {
        colStr = "*";
    }

    dbTokens["columns"] = colStr;
}

void QueryParser::parseCreateTokens(const std::vector<std::string> &tokens, std::map<std::string, std::string> &dbTokens) {
    if (tokens.size() < 3) {
        throw std::runtime_error("CREATE syntax error.");
    }

    if (toUpper(tokens[1]) != "TABLE") {
        throw std::runtime_error("CREATE query missing TABLE keyword.");
    }

    std::string table = tokens[2];
    dbTokens["table"] = table;

    // Columns are inside parentheses
    size_t startPos = 0, endPos = 0;
    for (size_t i = 3; i < tokens.size(); i++) {
        if (tokens[i] == "(") startPos = i;
        if (tokens[i] == ")") {
            endPos = i;
            break;
        }
    }

    if (startPos == 0 || endPos == 0 || endPos <= startPos) {
        throw std::runtime_error("CREATE query missing columns parentheses.");
    }

    std::vector<std::string> cols;
    for (size_t i = startPos+1; i < endPos; i++) {
        if (tokens[i] == ",") continue;
        cols.push_back(tokens[i]);
    }

    // Join columns
    std::string colStr;
    for (size_t i = 0; i < cols.size(); i++) {
        if (i > 0) colStr += ",";
        colStr += cols[i];
    }

    dbTokens["columns"] = colStr;
}

void QueryParser::parseInsertTokens(const std::vector<std::string> &tokens, std::map<std::string, std::string> &dbTokens) {
    if (tokens.size() < 6) {
        throw std::runtime_error("INSERT syntax error.");
    }

    if (toUpper(tokens[1]) != "INTO") {
        throw std::runtime_error("INSERT query missing INTO keyword.");
    }

    std::string table = tokens[2];
    dbTokens["table"] = table;

    // Columns in parentheses after table
    size_t startPos = 0, endPos = 0;
    size_t valStart = 0, valEnd = 0;
    for (size_t i = 3; i < tokens.size(); i++) {
        if (tokens[i] == "(" && startPos == 0) startPos = i;
        if (tokens[i] == ")" && endPos == 0 && startPos != 0) {
            endPos = i;
            break;
        }
    }

    if (startPos == 0 || endPos == 0) {
        throw std::runtime_error("INSERT query missing column list parentheses.");
    }

    std::vector<std::string> cols;
    for (size_t i = startPos+1; i < endPos; i++) {
        if (tokens[i] == ",") continue;
        cols.push_back(tokens[i]);
    }

    size_t valuesPos = 0;
    for (size_t i = endPos+1; i < tokens.size(); i++) {
        if (toUpper(tokens[i]) == "VALUES") {
            valuesPos = i;
            break;
        }
    }

    if (valuesPos == 0) {
        throw std::runtime_error("INSERT query missing VALUES keyword.");
    }

    for (size_t i = valuesPos+1; i < tokens.size(); i++) {
        if (tokens[i] == "(" && valStart == 0) valStart = i;
        if (tokens[i] == ")" && valEnd == 0 && valStart != 0) {
            valEnd = i;
            break;
        }
    }

    if (valStart == 0 || valEnd == 0) {
        throw std::runtime_error("INSERT query missing values parentheses.");
    }

    std::vector<std::string> vals;
    for (size_t i = valStart+1; i < valEnd; i++) {
        if (tokens[i] == ",") continue;
        vals.push_back(tokens[i]);
    }

    std::string colStr, valStr;
    for (size_t i = 0; i < cols.size(); i++) {
        if (i > 0) colStr += ",";
        colStr += cols[i];
    }
    for (size_t i = 0; i < vals.size(); i++) {
        if (i > 0) valStr += ",";
        valStr += vals[i];
    }

    dbTokens["columns"] = colStr;
    dbTokens["values"] = valStr;
}
