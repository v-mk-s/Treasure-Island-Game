//
// Created by alexey on 18.12.2021.
//

#ifndef ISLANDGAME_RESOURCETEXT_H
#define ISLANDGAME_RESOURCETEXT_H

#include <SFML/Graphics.hpp>

#include <sstream>
#include <string>

class ResourceText {
public:
    sf::Font font;
    sf::Text text;
    std::string resource_count_string;
    //std::ostringstream resource_count_string;

    virtual void text_render(int resource_count, sf::Vector2f coordinates) = 0;
};

class ShipResourceText : public ResourceText {
public:
    ShipResourceText (const std::string& path_to_font_file) {
        font.loadFromFile(path_to_font_file);
        text = {"", font, 18};
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    }
    virtual void text_render(int resource_count, sf::Vector2f coordinates) override;
};

class WinText : public ResourceText {
public:
    WinText (const std::string& path_to_font_file) {
        font.loadFromFile(path_to_font_file);
        text = {"", font, 100};
        text.setFillColor(sf::Color(230, 78, 64));
        text.setStyle(sf::Text::Bold);
    }
    virtual void text_render(int resource_count, sf::Vector2f coordinates) override;
};


#endif //ISLANDGAME_RESOURCETEXT_H