// GUIComponent.h
#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H

#include <SFML/Graphics.hpp>

class GUIComponent : public sf::Drawable
{
public:
    GUIComponent();
    virtual ~GUIComponent();

    virtual void eventHandler(sf::RenderWindow& window, sf::Event& event);
    virtual void update();
    virtual void setPosition(const sf::Vector2f& position);
    virtual void setEnabled(bool enabled);
    virtual bool isEnabled() const;

protected:
    bool _enabled;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // GUICOMPONENT_H
