// Cursor.cpp
#include "Cursor.h"
#include <iostream>

Cursor::Cursor() {
    _text.setFont(Font::getFont("arial"));
    _text.setString("|");
    _text.setCharacterSize(20);
    _text.setFillColor(sf::Color::Black);
    enableState(HIDDEN);
}

void Cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!checkState(HIDDEN)) {
        target.draw(_text, states);
    }
}

void Cursor::update() {
    if (checkState(BLINKING)) {
        if (clock.getElapsedTime().asMilliseconds() > 250) {
            toggleState(HIDDEN);
            clock.restart();
        }
    }
}

void Cursor::setFont(const sf::Font& font) {
    _text.setFont(font);
}

void Cursor::setCharacterSize(unsigned int size) {
    _text.setCharacterSize(size);
}

void Cursor::setFillColor(const sf::Color& color) {
    _text.setFillColor(color);
}

void Cursor::setPosition(const sf::Vector2f& position) {
    _text.setPosition(position);
}
