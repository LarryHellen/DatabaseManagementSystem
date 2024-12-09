#ifndef TEXTINPUTVIEW_H
#define TEXTINPUTVIEW_H

#include <SFML/Graphics.hpp>
#include "../TextInput/TextInput.h" // Assuming relative path

class TextInputView : public sf::Drawable {
public:
    TextInputView();

    void handleEvent(sf::Event &event, sf::RenderWindow &window);
    void update();

    std::string getText() const;

    void clearText();

    void setPosition(const sf::Vector2f& pos);

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    TextInput textInput;
};

#endif // TEXTINPUTVIEW_H
