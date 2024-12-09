#ifndef SPREADSHEETVIEW_H
#define SPREADSHEETVIEW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class SpreadsheetView : public sf::Drawable {
public:
    SpreadsheetView();

    void setData(const std::vector<std::vector<std::string>> &data);

    std::pair<int,int> getClickedCell(sf::Vector2i mousePos) const;

    void setCellSize(float width, float height);
    void setPosition(const sf::Vector2f& pos);

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::vector<std::vector<std::string>> tableData;
    sf::Font font;
    float cellWidth;
    float cellHeight;
    sf::Vector2f position;
};

#endif // SPREADSHEETVIEW_H
