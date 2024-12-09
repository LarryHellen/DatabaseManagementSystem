// main.cpp
#include <SFML/Graphics.hpp>
#include "Model/Database.h"
#include "Parser/QueryParser.h"
#include "View/TextInputView.h"
#include "View/SpreadsheetView.h"
#include "Controller/DatabaseController.h"


/*
1. CREATE TABLE Projects (ID, Title, Author, Launch)
2. INSERT INTO Projects (ID, Title, Author, Launch) VALUES (1, Hangman, Student, Run)
3. SELECT ID, Title, Author, Launch FROM Projects
*/



int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "DBMS with Projects");
    window.setFramerateLimit(60);

    Database database;
    QueryParser queryParser;
    TextInputView textInputView;
    SpreadsheetView spreadsheetView;

    textInputView.setPosition({100.f, 50.f});
    spreadsheetView.setPosition({50.f, 150.f});
    spreadsheetView.setCellSize(120.f, 30.f);

    DatabaseController controller(database, queryParser, textInputView, spreadsheetView);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            controller.handleEvent(event, window);
        }

        controller.update();

        window.clear(sf::Color::White);
        controller.draw(window);
        window.display();
    }

    return 0;
}
