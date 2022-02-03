//
// Created by ser on 27.11.2021.
//

#ifndef ISLANDGAME_CLIENTPLAYER_H
#define ISLANDGAME_CLIENTPLAYER_H

#include <view.h>

class Player : public View {

public:
    sf::View camera;

    Player (const std::string& path_to_file, struct SpriteCoord coord, sf::Vector2f pos, sf::Vector2f size_camera) :
            View (path_to_file, coord, pos) {
        camera.reset(sf::FloatRect(0, 0, size_camera.x, size_camera.y)); // При создании объекта говорим, где прям сейчас появится камера
    };
    //
    void render(struct SpriteCoord update_coord, sf::Vector2f position) {
        hero_sprite.setTextureRect(sf::IntRect(update_coord.begin_x, update_coord.begin_y,
                                                        update_coord.width, update_coord.height));
        hero_sprite.setPosition(position);
    };

};

#endif //ISLANDGAME_CLIENTPLAYER_H
