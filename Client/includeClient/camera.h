//
// Created by ser on 11.12.2021.
//

#ifndef ISLANDGAME_CAMERA_H
#define ISLANDGAME_CAMERA_H

#include <SFML/Graphics.hpp>

sf::View camera; // объект камера

void give_player_coord_to_camera(sf::Vector2f player_coordinates) {
    sf::Vector2f temporary_player_coordinates = player_coordinates;
    if (player_coordinates.y > 1100) {temporary_player_coordinates.y = 1100;}
    if (player_coordinates.y < 500) {temporary_player_coordinates.y = 500;}
    if (player_coordinates.x > 1740) {temporary_player_coordinates.x = 1740;}
    if (player_coordinates.x < 500) {temporary_player_coordinates.x = 500;}
    camera.setCenter(temporary_player_coordinates); // перерисовывает камеру, в зависимости от положения игрока
}
#endif //ISLANDGAME_CAMERA_H
