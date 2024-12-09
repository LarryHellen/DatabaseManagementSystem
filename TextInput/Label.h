// Label.h
#ifndef LABEL_H
#define LABEL_H

#include <SFML/Graphics.hpp>
#include "GUIComponent.h"
#include "Font.h"

class Label : public GUIComponent {
private:
    sf::Text _text;

public:
    Label();
    void setText(const std::string& str);
    void setFont(const sf::Font& font);
    void setCharacterSize(unsigned int size);
    void setFillColor(const sf::Color& color);
    void setPosition(const sf::Vector2f& position) override;

    void eventHandler(sf::RenderWindow& window, sf::Event& event) override;
    void update() override;

    sf::FloatRect getGlobalBounds() const;

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // LABEL_H
