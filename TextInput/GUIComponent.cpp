// GUIComponent.cpp
#include "GUIComponent.h"
#include <iostream>

GUIComponent::GUIComponent()
    : _enabled(true)
{
}

GUIComponent::~GUIComponent() {
}

void GUIComponent::eventHandler(sf::RenderWindow& window, sf::Event& event) {
}

void GUIComponent::update() {
}

void GUIComponent::setPosition(const sf::Vector2f& position) {
}

void GUIComponent::setEnabled(bool enabled) {
    _enabled = enabled;
}

bool GUIComponent::isEnabled() const {
    return _enabled;
}

void GUIComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
}
