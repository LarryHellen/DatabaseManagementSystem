// Label.cpp
#include "Label.h"
#include <iostream>

Label::Label() {
    _text.setFont(Font::getFont("arial"));
    _text.setString("");
    _text.setCharacterSize(14);
    _text.setFillColor(sf::Color::Black);
}

void Label::setText(const std::string& str) {
    _text.setString(str);
}

void Label::setFont(const sf::Font& font) {
    _text.setFont(font);
}

void Label::setCharacterSize(unsigned int size) {
    _text.setCharacterSize(size);
}

void Label::setFillColor(const sf::Color& color) {
    _text.setFillColor(color);
}

void Label::setPosition(const sf::Vector2f& position) {
    _text.setPosition(position);
}

void Label::eventHandler(sf::RenderWindow& window, sf::Event& event) {
}

void Label::update() {
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (_enabled) {
        target.draw(_text, states);
    }
}

sf::FloatRect Label::getGlobalBounds() const {
    return _text.getGlobalBounds();
}
