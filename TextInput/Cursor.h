// Cursor.h
#ifndef CURSOR_H
#define CURSOR_H

#include <SFML/Graphics.hpp>
#include "Font.h"
#include "States.h"

class Cursor : public sf::Drawable, public States {
private:
    sf::Text _text;
    sf::Clock clock;

public:
    Cursor();
    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;
    void update();

    void setFont(const sf::Font& font);
    void setCharacterSize(unsigned int size);
    void setFillColor(const sf::Color& color);
    void setPosition(const sf::Vector2f& position);
};

#endif // CURSOR_H
