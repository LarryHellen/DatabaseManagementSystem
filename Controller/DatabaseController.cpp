#include "DatabaseController.h"

DatabaseController::DatabaseController(Database &db, QueryParser &parser, TextInputView &textInput, SpreadsheetView &spreadsheet)
    : database(db), queryParser(parser), textInputView(textInput), spreadsheetView(spreadsheet) {}

void DatabaseController::handleEvent(sf::Event &event, sf::RenderWindow &window) {
    textInputView.handleEvent(event, window);

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        std::string query = textInputView.getText();
        executeQuery(query);
        textInputView.clearText();
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        auto cell = spreadsheetView.getClickedCell(mousePos);
        if (cell.first != -1 && cell.second != -1) {
            handleCellClick(cell.first, cell.second);
        }
    }
}

void DatabaseController::update() {
    textInputView.update();
}

void DatabaseController::draw(sf::RenderWindow &window) {
    window.draw(textInputView);
    window.draw(spreadsheetView);
}

void DatabaseController::executeQuery(const std::string &query) {
    if (!queryParser.validate(query)) {
        std::cerr << "Invalid query syntax." << std::endl;
        return;
    }

    auto dbTokens = queryParser.tokenize(query);

    try {
        database.query(dbTokens);
        if (database.hasResults()) {
            auto results = database.getResults();
            spreadsheetView.setData(results);
        } else {
            spreadsheetView.setData({});
        }
    } catch (std::exception &e) {
        std::cerr << "Query execution error: " << e.what() << std::endl;
    }
}

void DatabaseController::handleCellClick(int row, int column) {
    if (row == 0) return;

    auto data = database.getResults();
    if ((size_t)row >= data.size()) return;

    if ((size_t)column < data[row].size() && data[row][column] == "Run") {
        // Finding "Title"
        int titleIndex = -1;
        if (!data.empty()) {
            const auto &headers = data[0];
            for (size_t i = 0; i < headers.size(); ++i) {
                if (headers[i] == "Title") {
                    titleIndex = (int) i;
                    break;
                }
            }
        }

        if (titleIndex != -1 && (size_t)titleIndex < data[row].size()) {
            std::string projectName = data[row][titleIndex];
            launchProject(projectName);
        } else {
            std::cerr << "No 'Title' column found in the table, cannot launch project." << std::endl;
        }
    }
}

void DatabaseController::launchProject(const std::string &projectName)
{
    sf::RenderWindow projectWindow(sf::VideoMode(400, 300), projectName, sf::Style::Titlebar | sf::Style::Close);
    projectWindow.setFramerateLimit(60);


    sf::Font font;
    if(!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font for project window.\n";
        return;
    }

    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString(projectName);
    titleText.setCharacterSize(40);
    titleText.setFillColor(sf::Color::Black);


    sf::FloatRect textRect = titleText.getLocalBounds();
    titleText.setOrigin(textRect.width/2.0f, textRect.height/2.0f);
    titleText.setPosition(projectWindow.getSize().x/2.0f, projectWindow.getSize().y/2.0f);


    while (projectWindow.isOpen()) {
        sf::Event event;
        while (projectWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                projectWindow.close();
            }
        }

        projectWindow.clear(sf::Color::White);
        projectWindow.draw(titleText);
        projectWindow.display();
    }
}
