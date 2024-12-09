// TextInput.h
#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include <SFML/Graphics.hpp>
#include "GUIComponent.h"
#include "Label.h"
#include "Cursor.h"
#include "LabelPosition.h" // Include the LabelPosition enum

class TextInput : public GUIComponent {
private:
    sf::RectangleShape _box;
    Label _label;
    Cursor _cursor;
    sf::Text _inputText;
    std::string _textString;
    bool _isFocused;
    LabelPosition _labelPosition;

    void updateCursorPosition();

public:
    // Spacing constants
    static constexpr float TOP_LABEL_SPACING = 10.f;
    static constexpr float LEFT_LABEL_SPACING = 10.f;

    TextInput();
    void setLabel(const std::string& label);
    void setLabelSize(unsigned int size);
    void setLabelColor(const sf::Color& color);
    void setLabelPosition(LabelPosition position);
    void setBoxSize(const sf::Vector2f& size);
    void setBoxFillColor(const sf::Color& color);
    void setBoxOutlineColor(const sf::Color& color);
    void setBoxOutlineThickness(float thickness);
    void setCharacterSize(unsigned int size);
    void setFont(const std::string& fontName);
    void setTextColor(const sf::Color& color);
    std::string getText() const;

    void setPosition(const sf::Vector2f& position) override;
    void eventHandler(sf::RenderWindow& window, sf::Event& event) override;
    void update() override;

    void clearText();

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // TEXTINPUT_H
