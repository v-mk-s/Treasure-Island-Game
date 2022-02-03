//
// Created by ser on 08.12.2021.
//

#ifndef ISLANDGAME_VIEW_H
#define ISLANDGAME_VIEW_H

#include "EventBus.h"

class View {

public:
    sf::Texture hero_texture;
    sf::Sprite hero_sprite;
    View (const std::string& path_to_file, struct SpriteCoord coord, sf::Vector2f pos)  { // static - позволяет вызывать методы без объектов

        //Создание текстуры
        hero_texture.loadFromFile(path_to_file);

        //Создание спрайта игрока
        hero_sprite;
        hero_sprite.setTexture(hero_texture);
        //hero_sprite.setTextureRect(sf::IntRect(coord.begin_x, coord.begin_y, coord.width, coord.height));

        hero_sprite.setPosition(pos);
    }
/*Создаём*/
};
#endif //ISLANDGAME_VIEW_H
