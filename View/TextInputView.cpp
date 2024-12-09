#include "TextInputView.h"

TextInputView::TextInputView() {
    textInput.setLabel("SQL:");
    textInput.setLabelSize(16);
    textInput.setLabelColor(sf::Color::Black);
    textInput.setLabelPosition(LabelPosition::Top);
    textInput.setBoxSize({650.f, 40.f});
    textInput.setBoxFillColor(sf::Color::White);
    textInput.setBoxOutlineColor(sf::Color::Blue);
    textInput.setBoxOutlineThickness(2.f);
    textInput.setCharacterSize(16);
    textInput.setFont("arial");
    textInput.setTextColor(sf::Color::Black);

    textInput.setPosition({50.f, 80.f});
}
void TextInputView::handleEvent(sf::Event &event, sf::RenderWindow &window) {
    textInput.eventHandler(window, event);
}

void TextInputView::update() {
    textInput.update();
}

std::string TextInputView::getText() const {
    return textInput.getText();
}

void TextInputView::clearText()
{
    const_cast<TextInput&>(textInput).clearText();
}

void TextInputView::setPosition(const sf::Vector2f &pos) {
    textInput.setPosition(pos);
}

void TextInputView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(textInput, states);
}
