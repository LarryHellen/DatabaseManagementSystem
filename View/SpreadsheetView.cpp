#include "SpreadsheetView.h"
#include "../TextInput/Font.h" // Assuming your Font class for loading fonts

SpreadsheetView::SpreadsheetView()
    : cellWidth(100.f), cellHeight(30.f), position(50.f, 100.f) {
    font = Font::getFont("arial");
}

void SpreadsheetView::setData(const std::vector<std::vector<std::string>> &data) {
    tableData = data;
}

void SpreadsheetView::setCellSize(float width, float height) {
    cellWidth = width;
    cellHeight = height;
}

void SpreadsheetView::setPosition(const sf::Vector2f &pos) {
    position = pos;
}

std::pair<int,int> SpreadsheetView::getClickedCell(sf::Vector2i mousePos) const {
    float fx = (float)mousePos.x - position.x;
    float fy = (float)mousePos.y - position.y;

    if (fx < 0 || fy < 0) return {-1,-1};

    int col = (int)(fx / cellWidth);
    int row = (int)(fy / cellHeight);

    if (row < 0 || (size_t)row >= tableData.size()) return {-1,-1};

    if (col < 0) {
        return {-1, -1};
    } else {
        size_t numCols;
        if (tableData.empty()) {
            numCols = 0;
        } else {
            numCols = tableData[0].size();
        }
        if ((size_t)col >= numCols) {
            return {-1, -1};
        }
    }


    return {row, col};
}

void SpreadsheetView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (size_t r = 0; r < tableData.size(); r++) {
        for (size_t c = 0; c < tableData[r].size(); c++) {
            sf::RectangleShape cellRect({cellWidth, cellHeight});
            cellRect.setPosition(position.x + c*cellWidth, position.y + r*cellHeight);
            cellRect.setFillColor(sf::Color::White);
            cellRect.setOutlineColor(sf::Color::Black);
            cellRect.setOutlineThickness(1.f);

            if (tableData[r][c] == "Run") {
                cellRect.setFillColor(sf::Color(200,255,200));
            }

            target.draw(cellRect, states);

            sf::Text txt;
            txt.setFont(font);
            txt.setString(tableData[r][c]);
            txt.setCharacterSize(14);
            txt.setFillColor(sf::Color::Black);
            txt.setPosition(position.x + c*cellWidth + 5, position.y + r*cellHeight + 5);
            target.draw(txt, states);
        }
    }
}
