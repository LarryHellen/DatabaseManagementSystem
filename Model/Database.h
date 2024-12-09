#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <string>
#include <vector>
#include <stdexcept>
#include "Table.h"

class Database {
public:
    typedef std::vector<std::vector<std::string>> Entries;
    Database();

    void query(const std::map<std::string, std::string> &dbTokens);

    const Entries& getResults() const;
    bool hasResults() const;

private:
    std::map<std::string, Table> tables;
    Entries _last_entries;
    bool hasNewResults;

    void create_table(const std::map<std::string, std::string> &dbTokens);
    void insert_into_table(const std::map<std::string, std::string> &dbTokens);
    void delete_table(const std::map<std::string, std::string> &dbTokens); // stub
    void query_select(const std::map<std::string, std::string> &dbTokens);

    static std::vector<std::string> get_columns(const std::string &columns_str);
    static std::vector<std::string> get_values(const std::string &values_str);
};

#endif // DATABASE_H
