// TextInput.cpp
#include "TextInput.h"
#include "States.h"
#include "StateEnum.h"
#include <iostream>

TextInput::TextInput()
    : _isFocused(false), _labelPosition(LabelPosition::Top) // Default label position is Top
{
    // Setup box
    _box.setSize({300.f, 40.f});
    _box.setFillColor(sf::Color::White);
    _box.setOutlineColor(sf::Color::Blue);
    _box.setOutlineThickness(2.f);

    // Setup input text
    _inputText.setFont(Font::getFont("arial"));
    _inputText.setCharacterSize(20);
    _inputText.setFillColor(sf::Color::Black);
    _inputText.setPosition(_box.getPosition().x + 5.f, _box.getPosition().y + 5.f);

    // Setup cursor
    _cursor.setFont(Font::getFont("arial"));
    _cursor.setCharacterSize(20);
    _cursor.setFillColor(sf::Color::Black);
    _cursor.enableState(HIDDEN); // Initially hidden

    // Setup label
    _label.setFont(Font::getFont("arial"));
    _label.setCharacterSize(20); // Set to match input text
    _label.setFillColor(sf::Color::Black);
    // Initial position will be set in setLabelPosition
    setLabelPosition(_labelPosition);
}

void TextInput::setLabel(const std::string& label) {
    _label.setText(label);
    if (_label.isEnabled()) {
        setLabelPosition(_labelPosition);
    }
}

void TextInput::setLabelSize(unsigned int size) {
    _label.setCharacterSize(size);
    if (_label.isEnabled()) {
        setLabelPosition(_labelPosition);
    }
}

void TextInput::setLabelColor(const sf::Color& color) {
    _label.setFillColor(color);
}

void TextInput::setLabelPosition(LabelPosition position) {
    _labelPosition = position;

    sf::Vector2f boxPos = _box.getPosition();
    sf::FloatRect boxBounds = _box.getGlobalBounds();
    sf::FloatRect labelBounds = _label.getGlobalBounds();

    if (_labelPosition == LabelPosition::Top) {
        _label.setPosition(sf::Vector2f(boxPos.x, boxPos.y - labelBounds.height - TOP_LABEL_SPACING));
    }
    else if (_labelPosition == LabelPosition::Left) {
        _label.setPosition(sf::Vector2f(boxPos.x - labelBounds.width - LEFT_LABEL_SPACING,
                                       boxPos.y + (boxBounds.height - labelBounds.height) / 2.f));
    }
}

void TextInput::setBoxSize(const sf::Vector2f& size) {
    _box.setSize(size);
    if (_label.isEnabled()) {
        setLabelPosition(_labelPosition);
    }
}

void TextInput::setBoxFillColor(const sf::Color& color) {
    _box.setFillColor(color);
}

void TextInput::setBoxOutlineColor(const sf::Color& color) {
    _box.setOutlineColor(color);
}

void TextInput::setBoxOutlineThickness(float thickness) {
    _box.setOutlineThickness(thickness);
}

void TextInput::setCharacterSize(unsigned int size) {
    _inputText.setCharacterSize(size);
    _cursor.setCharacterSize(size);

    if (_label.isEnabled()) {
        setLabelPosition(_labelPosition);
    }
}

void TextInput::setFont(const std::string& fontName) {
    _inputText.setFont(Font::getFont(fontName));
    _cursor.setFont(Font::getFont(fontName));
    _label.setFont(Font::getFont(fontName));
}

void TextInput::setTextColor(const sf::Color& color) {
    _inputText.setFillColor(color);
    _cursor.setFillColor(color);
}

std::string TextInput::getText() const {
    return _textString;
}

void TextInput::setPosition(const sf::Vector2f& position) {
    _box.setPosition(position);
    _inputText.setPosition(position.x + 5.f, position.y + 5.f);
    updateCursorPosition();

    if (_label.isEnabled()) {
        setLabelPosition(_labelPosition);
    }
}

void TextInput::eventHandler(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (_box.getGlobalBounds().contains(mousePos)) {
            _isFocused = true;
            _cursor.enableState(BLINKING);
            _cursor.disableState(HIDDEN);
            updateCursorPosition();
        }
        else {
            _isFocused = false;
            _cursor.disableState(BLINKING);
            _cursor.enableState(HIDDEN);
        }
    }

    if (_isFocused && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8) { // Backspace
            if (!_textString.empty()) {
                _textString.pop_back();
                _inputText.setString(_textString);
                updateCursorPosition();
            }
        }
        else if (event.text.unicode >= 32 && event.text.unicode < 127) { // Printable characters
            _textString += static_cast<char>(event.text.unicode);
            _inputText.setString(_textString);
            updateCursorPosition();
        }
    }
}

void TextInput::updateCursorPosition() {
    float newX = _inputText.getPosition().x + _inputText.getLocalBounds().width + 2.f;
    _cursor.setPosition(sf::Vector2f(newX, _inputText.getPosition().y));
}

void TextInput::update() {
    _cursor.update();
}

void TextInput::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (_enabled) {
        if (_label.isEnabled()) {
            target.draw(_label, states);
        }
        target.draw(_box, states);
        target.draw(_inputText, states);
        target.draw(_cursor, states);
    }
}

void TextInput::clearText() {
    _textString.clear();
    _inputText.setString("");
    updateCursorPosition();
}
