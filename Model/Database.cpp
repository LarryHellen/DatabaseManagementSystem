#include "Database.h"
#include <sstream>
#include <algorithm>
#include <cctype>

Database::Database() : hasNewResults(false) {}

void Database::query(const std::map<std::string, std::string> &dbTokens) {
    hasNewResults = false;
    _last_entries.clear();

    std::string command;
    if (dbTokens.find("command") != dbTokens.end()) {
        command = dbTokens.at("command");
    } else {
        throw std::runtime_error("No command found in query tokens.");
    }

    for (size_t i = 0; i < command.size(); ++i)
        command[i] = std::toupper((unsigned char)command[i]);


    if (command == "CREATE") {
        create_table(dbTokens);
    } else if (command == "INSERT") {
        insert_into_table(dbTokens);
    } else if (command == "SELECT") {
        query_select(dbTokens);
    } else if (command == "DELETE") {
        delete_table(dbTokens);
    } else {
        throw std::runtime_error("Unsupported command: " + command);
    }
}

void Database::create_table(const std::map<std::string, std::string> &dbTokens) {
    if (dbTokens.find("table") == dbTokens.end()) {
        throw std::runtime_error("CREATE TABLE error: No table name provided.");
    }

    std::string tableName = dbTokens.at("table");
    std::string columns_str;
    if (dbTokens.count("columns")) {
        columns_str = dbTokens.at("columns");
    } else {
        columns_str = "";
    }

    std::vector<std::string> cols = get_columns(columns_str);
    if (cols.empty()) {
        throw std::runtime_error("No columns provided for CREATE TABLE.");
    }

    if (tables.find(tableName) != tables.end()) {
        throw std::runtime_error("Table already exists: " + tableName);
    }

    Table newTable(cols);
    tables[tableName] = newTable;
}

void Database::insert_into_table(const std::map<std::string, std::string> &dbTokens) {
    if (dbTokens.find("table") == dbTokens.end()) {
        throw std::runtime_error("INSERT error: No table name provided.");
    }

    std::string tableName = dbTokens.at("table");
    if (tables.find(tableName) == tables.end()) {
        throw std::runtime_error("Table does not exist: " + tableName);
    }

    Table &tbl = tables[tableName];

    std::string columns_str;
    if (dbTokens.count("columns")) {
        columns_str = dbTokens.at("columns");
    } else {
        columns_str = "";
    }

    std::string values_str;
    if (dbTokens.count("values")) {
        values_str = dbTokens.at("values");
    } else {
        values_str = "";
    }

    std::vector<std::string> cols = get_columns(columns_str);
    std::vector<std::string> vals = get_values(values_str);

    if (cols.size() != vals.size()) {
        throw std::runtime_error("INSERT error: Number of columns does not match number of values.");
    }

    // Construct a row
    std::map<std::string,std::string> rowData;
    for (size_t i = 0; i < cols.size(); ++i) {
        rowData[cols[i]] = vals[i];
    }

    tbl.insertRow(rowData);
}

void Database::delete_table(const std::map<std::string, std::string> &dbTokens) {
    // Decided not to do
    throw std::runtime_error("DELETE TABLE not supported yet.");
}

void Database::query_select(const std::map<std::string, std::string> &dbTokens) {
    if (dbTokens.find("table") == dbTokens.end()) {
        throw std::runtime_error("SELECT error: No table name provided.");
    }

    std::string tableName = dbTokens.at("table");
    if (tables.find(tableName) == tables.end()) {
        throw std::runtime_error("SELECT error: Table does not exist: " + tableName);
    }

    Table &tbl = tables[tableName];

    std::string columns_str;
    if (dbTokens.count("columns")) {
        columns_str = dbTokens.at("columns");
    } else {
        columns_str = "*";
    }

    std::vector<std::string> cols;
    if (columns_str == "*") {
        // Select all columns
        auto rows = tbl.getRows();
        if (!rows.empty()) {
            for (auto &kv : rows.front()) {
                cols.push_back(kv.first);
            }
        }
    } else
    {
        cols = get_columns(columns_str);
    }

    for (auto &c : cols) {
        if (!tbl.hasColumn(c)) {
            throw std::runtime_error("SELECT error: Invalid column: " + c);
        }
    }

    _last_entries.clear();

    // Header row
    _last_entries.push_back(cols);

    // Data rows
    for (auto &r : tbl.getRows())
    {
        std::vector<std::string> rowData;
        for (auto &c : cols) {
            if (r.find(c) != r.end()) {
                rowData.push_back(r.at(c));
            } else {
                rowData.push_back("");
            }
        }
        _last_entries.push_back(rowData);
    }

    hasNewResults = true;
}

const Database::Entries& Database::getResults() const {
    return _last_entries;
}

bool Database::hasResults() const {
    return hasNewResults;
}

std::vector<std::string> Database::get_columns(const std::string &columns_str) {
    std::vector<std::string> result;
    std::string temp = columns_str;
    // Remove paranthesis
    for (size_t i = 0; i < temp.size(); ++i) {
        if (temp[i] == '(' || temp[i] == ')') {
            temp.erase(i, 1);
            --i; // Adjust index after erase
        }
    }

    std::stringstream ss(temp);
    std::string token;
    // Remove spaces
    while (std::getline(ss, token, ',')) {
        while (!token.empty() && std::isspace((unsigned char)token.front())) {
            token.erase(token.begin());
        }
        while (!token.empty() && std::isspace((unsigned char)token.back())) {
            token.pop_back();
        }
        if (!token.empty()) {
            result.push_back(token);
        }
    }
    return result;
}

std::vector<std::string> Database::get_values(const std::string &values_str) {
    return get_columns(values_str);
}
