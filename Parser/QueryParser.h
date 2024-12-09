#ifndef QUERYPARSER_H
#define QUERYPARSER_H

#include <string>
#include <map>
#include <vector>

class QueryParser {
public:
    bool validate(const std::string& query);
    std::map<std::string, std::string> tokenize(const std::string& query);

private:
    // Helpers
    std::vector<std::string> splitTokens(const std::string& query);
    std::string toUpper(const std::string &str) const;

    void parseSelectTokens(const std::vector<std::string>& tokens, std::map<std::string,std::string>& dbTokens);
    void parseCreateTokens(const std::vector<std::string>& tokens, std::map<std::string,std::string>& dbTokens);
    void parseInsertTokens(const std::vector<std::string>& tokens, std::map<std::string,std::string>& dbTokens);
};

#endif // QUERYPARSER_H
