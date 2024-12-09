#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <SFML/Graphics.hpp>
#include "../Model/Database.h"
#include "../Parser/QueryParser.h"
#include "../View/TextInputView.h"
#include "../View/SpreadsheetView.h"
#include <iostream>

class DatabaseController {
public:
    DatabaseController(Database &db, QueryParser &parser, TextInputView &textInput, SpreadsheetView &spreadsheet);

    void handleEvent(sf::Event &event, sf::RenderWindow &window);
    void update();
    void draw(sf::RenderWindow &window);

private:
    Database &database;
    QueryParser &queryParser;
    TextInputView &textInputView;
    SpreadsheetView &spreadsheetView;

    void executeQuery(const std::string& query);
    void handleCellClick(int row, int column);
    void launchProject(const std::string& projectName);
};

#endif // DATABASECONTROLLER_H
