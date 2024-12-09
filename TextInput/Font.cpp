// Font.cpp
#include "Font.h"
#include <iostream>

void Font::loadFont(const std::string &fontName)
{
    if(_fonts.count(fontName) == 0) {
        if (!_fonts[fontName].loadFromFile(getFontPath(fontName))) {
            std::cerr << "Failed to load font: " << fontName << "\n";
            throw std::runtime_error("Failed to load font: " + fontName);
        }
    }
}

sf::Font & Font::getFont(const std::string &fontName)
{
    loadFont(fontName);
    return _fonts[fontName];
}

std::string Font::getFontPath(std::string fontName)
{
    std::map<std::string, std::string> _map;
    _map["arial"] = "arial.ttf";
    _map["openSans"] = "openSans.ttf";
    if (_map.find(fontName) != _map.end()) {
        return _map[fontName];
    } else {
        std::cerr << "Font name not found in map: " << fontName << "\n";
        throw std::invalid_argument("Font name not found: " + fontName);
    }
}
