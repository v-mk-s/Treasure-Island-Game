//
// Created by alexey on 26.12.2021.
//

#ifndef ISLANDGAME_MAZE_H
#define ISLANDGAME_MAZE_H

#include "view.h"
#include <SFML/Graphics/Rect.hpp>

class Maze: public View {
public:
    Maze(const std::string& path_to_file, struct SpriteCoord coord, sf::Vector2f pos):
            View (path_to_file, coord, pos){

    };
    void render(struct SpriteCoord update_coord, sf::Vector2f position) {
        hero_sprite.setTextureRect(sf::IntRect(update_coord.begin_x, update_coord.begin_y,
                                               update_coord.width, update_coord.height));
        hero_sprite.setPosition(position);
    };
};

#endif //ISLANDGAME_MAZE_H
