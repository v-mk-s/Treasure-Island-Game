//
// Created by ser on 20.12.2021.
//

#ifndef ISLANDGAME_RESOURCES_H
#define ISLANDGAME_RESOURCES_H

#include "view.h"
#include <SFML/Graphics/Rect.hpp>

class Resources: public View {
public:
    Resources(const std::string& path_to_file, struct SpriteCoord coord, sf::Vector2f pos):
            View (path_to_file, coord, pos){

    };
    void render(struct SpriteCoord update_coord, sf::Vector2f position) {
        hero_sprite.setTextureRect(sf::IntRect(update_coord.begin_x, update_coord.begin_y,
                                               update_coord.width, update_coord.height));
        hero_sprite.setPosition(position);
    };
};

#endif //ISLANDGAME_RESOURCES_H
