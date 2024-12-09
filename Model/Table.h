#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <set>
#include "InvalidColumnNameException.h"

class Table {
public:
    Table() = default; // Add this default constructor
    Table(const std::vector<std::string>& columns);

    void insert(const std::pair<std::string, std::string>& entry);
    bool hasColumn(const std::string& column) const;
    const std::vector<std::map<std::string,std::string>>& getRows() const;
    void insertRow(const std::map<std::string, std::string>& rowData);

private:
    std::set<std::string> validColumns;
    std::vector<std::map<std::string,std::string>> rows;
};

#endif // TABLE_H
