//
// Created by larry on 12/8/2024.
//

#ifndef FONT_H
#define FONT_H

#include <map>
#include <string>
#include <SFML/Graphics.hpp>


class Font {
private:
    inline static std::map<std::string, sf::Font> _fonts;
    static void loadFont(const std::string& fontName);
    static std::string getFontPath(std::string fontName);
public:
    static sf::Font& getFont(const std::string& fontName);

};



#endif //FONT_H
