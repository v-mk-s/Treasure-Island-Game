//
// Created by alexey on 07.12.2021.
//

#ifndef ISLANDGAME_EVENT_H
#define ISLANDGAME_EVENT_H

#define MAZE_SPAWN_ZONE_COUNT 12
#define RESOURCE_SPAWN_ZONE_COUNT 3
#define QUANTITY_RES 10
#define PORT 3004


#include <vector>
#include <string>

#include <SFML/System/Vector2.hpp>

#include "Lev.h"

enum Types {
    user_init,
    dir_left,
    dir_right,
    dir_straight,
    dir_back,
    is_intersect_with_player,
    is_intersect_with_map,
    got_ship_resource,
    error,
};

// Режем кусочек изображения с помощью этого
struct SpriteCoord {
    int begin_x;
    int begin_y;
    int height;
    int width;
};

struct UserMovedEventData {
    sf::Vector2f coordinates[2];
    SpriteCoord sprite_coordinates[2];
};

struct ResourcesData {
    int picked_item_index;
    int picked_item_area;
    int ship_resource_count[2];
    std::vector<sf::Vector2f> *resource_positions_to_send;
    std::vector<sf::Vector2f> received_resource_positions[RESOURCE_SPAWN_ZONE_COUNT];
    std::vector<Object> resource_spawn_areas;
};

struct MazeData {
    std::vector<sf::Vector2f> maze_walls;
    std::vector<Object> maze_zones;
};

struct Event {
    Event() {
        Object a = Object();
        resources_data.resource_spawn_areas = {a, a, a};
        for (auto & received_shift : resources_data.received_resource_positions) {
            for (int j = 0; j < QUANTITY_RES; ++j) {
                received_shift.emplace_back(0, 0);
            }
        }
        for (int i = 0; i < MAZE_SPAWN_ZONE_COUNT; ++i) {
            maze_data.maze_zones.emplace_back(a);
            maze_data.maze_walls.emplace_back(0, 0);
        }

    }

    Types type;
    int moved_player_number;
    int client_number;
    UserMovedEventData user_moved;
    ResourcesData resources_data;
    MazeData maze_data;
};

#endif //ISLANDGAME_EVENT_H