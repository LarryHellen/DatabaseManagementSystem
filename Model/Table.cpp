#include "Table.h"

Table::Table(const std::vector<std::string>& columns) {
    // Validate columns: no duplicates, no invalid chars (we’ll assume just no empty strings for simplicity)
    for (auto& col : columns) {
        if (col.empty()) {
            throw InvalidColumnNameException("Column name cannot be empty.");
        }
        // Could add further validation (no spaces, special chars), but let's keep it simple
        validColumns.insert(col);
    }
}

void Table::insert(const std::pair<std::string, std::string>& entry) {
    const std::string& column = entry.first;
    const std::string& value = entry.second;

    if (!hasColumn(column)) {
        throw InvalidColumnNameException("Invalid column: " + column);
    }

    // Insert a single column-value pair as a new row would not make sense here,
    // because we need a full set of columns to represent a row.
    // Instead, let's interpret this differently: We'll store partial rows and assume insert() is called repeatedly for each column in that row.
    // This approach is not ideal. It's better to have a single method to insert a full row at once.
    // Let's pivot: We'll just create a new row with one column each time, assuming the caller ensures correctness.
    // This isn't realistic for a DB, but let's follow instructions.

    // Actually, let's not break the logic. We'll add a method insertRow() that inserts a full row.
    // The Database class will use insertRow() for a full row.
    // The insert() method can be a fallback if needed, but let's store partial rows in a single-row scenario.
    // For now, let's do a simple approach: add a row with just this one column.

    std::map<std::string,std::string> row;
    row[column] = value;
    rows.push_back(row);
}

bool Table::hasColumn(const std::string& column) const {
    return validColumns.find(column) != validColumns.end();
}

const std::vector<std::map<std::string,std::string>>& Table::getRows() const {
    return rows;
}

void Table::insertRow(const std::map<std::string, std::string>& rowData) {
    // Validate all columns
    for (auto& kv : rowData) {
        if (!hasColumn(kv.first)) {
            throw InvalidColumnNameException("Invalid column in insertRow: " + kv.first);
        }
    }
    rows.push_back(rowData);
}
