//
// Created by alexey on 08.12.2021.
//
#include "Models.h"

void Player::update(Event event) {
    if ((event.type == dir_left || event.type == dir_right || event.type == dir_straight \
 || event.type == dir_back) && event.moved_player_number == player_number) {

        switch (event.type) {
            case 1: {
                coordinates.x -= speed;
                if (player_number == 0) {
                    player_sprite_coordinates = {.begin_x = 32, .begin_y = 32, .height = 32, .width = 32};
                } else {
                    player_sprite_coordinates = {.begin_x = 32, .begin_y = 5*32, .height = 32, .width = 32};
                }
                break;
            }
            case 2: {
                coordinates.x += speed;
                if (player_number == 0) {
                    player_sprite_coordinates = {.begin_x = 32, .begin_y = 64, .height = 32, .width = 32};
                } else {
                    player_sprite_coordinates = {.begin_x = 32, .begin_y = 6*32, .height = 32, .width = 32};
                }
                break;
            }
            case 3: {
                coordinates.y -= speed;
                if (player_number == 0) {
                    player_sprite_coordinates = {.begin_x = 32, .begin_y = 96, .height = 32, .width = 32};
                } else {
                    player_sprite_coordinates = {.begin_x = 32, .begin_y = 7*32, .height = 32, .width = 32};
                }
                break;
            }
            case 4: {
                coordinates.y += speed;
                if (player_number == 0) {
                    player_sprite_coordinates = {.begin_x = 32, .begin_y = 0, .height = 32, .width = 32};
                } else {
                    player_sprite_coordinates = {.begin_x = 32, .begin_y = 4*32, .height = 32, .width = 32};
                }
                break;
            }
            default: {
                coordinates.x += speed;
                coordinates.y += speed;
                player_sprite_coordinates = {.begin_x = 32, .begin_y = 32, .height = 32, .width = 32};
                break;
            }
        }
    }
}
