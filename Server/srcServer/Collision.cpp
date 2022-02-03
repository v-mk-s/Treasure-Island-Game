//
// Created by alexey on 17.12.2021.
//

#include "Models.h"

void Collision::update(Event event) {
    if (event.type == is_intersect_with_player) {
        for (int i = 0; i < player_count; ++i) {
            if (event.moved_player_number != players[i].get_player_number()) {
                continue;
            }
            for (int j = 0; j < player_count; ++j) {
                if (j != players[i].get_player_number()) {
                    if (players[i].get_sprite_rect().intersects(sf::FloatRect(event.user_moved.coordinates[j], \
                {static_cast<float>(event.user_moved.sprite_coordinates[j].width),
                 static_cast<float>(event.user_moved.sprite_coordinates[j].height)}))) {
                        switch (players[i].get_direction()) {
                            case 1: {
                                players[i].set_coordinates({event.user_moved.coordinates[j].x + \
                                event.user_moved.sprite_coordinates[j].width, players[i].get_coordinates().y});
                                break;
                            }
                            case 2: {
                                players[i].set_coordinates({event.user_moved.coordinates[j].x -
                                                            players[i].get_player_sprite_coordinates().width, \
                                players[i].get_coordinates().y});
                                break;
                            }
                            case 3: {
                                players[i].set_coordinates({players[i].get_coordinates().x, \
                                event.user_moved.coordinates[j].y + event.user_moved.sprite_coordinates[j].height});
                                break;
                            }
                            case 4: {
                                players[i].set_coordinates({players[i].get_coordinates().x, \
                                event.user_moved.coordinates[j].y - players[i].get_player_sprite_coordinates().height});
                                break;
                            }
                            default: {
                                players[i].set_coordinates({players[i].get_coordinates().x + players[i].get_speed(), \
                                players[i].get_coordinates().y + players[i].get_speed()});
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    if (event.type == is_intersect_with_map) {
        for (int i = 0; i < player_count; ++i) {
            if (event.moved_player_number != players[i].get_player_number()) {
                continue;
            }
            for (auto object_solid: objects_solid) {
                if (players[i].get_sprite_rect().intersects(object_solid.rect)) {
                    switch (players[i].get_direction()) {
                        case 1: {
                            players[i].set_coordinates({object_solid.rect.left + object_solid.rect.width,
                                                        players[i].get_coordinates().y});
                            break;
                        }
                        case 2: {
                            players[i].set_coordinates(
                                    {object_solid.rect.left - players[i].get_player_sprite_coordinates().width, \
                                players[i].get_coordinates().y});
                            break;
                        }
                        case 3: {
                            players[i].set_coordinates({players[i].get_coordinates().x, \
                                    object_solid.rect.top + object_solid.rect.height});
                            break;
                        }
                        case 4: {
                            players[i].set_coordinates({players[i].get_coordinates().x, \
                                object_solid.rect.top - players[i].get_player_sprite_coordinates().height});
                            break;
                        }
                        default: {
                            players[i].set_coordinates(
                                    {object_solid.rect.left - players[i].get_player_sprite_coordinates().width, \
                                object_solid.rect.top - players[i].get_player_sprite_coordinates().height});
                            break;
                        }
                    }
                }
            }
            for (int j = 0; j < maze_zones.size(); ++j) {
                if (players[i].get_sprite_rect().intersects(
                        sf::FloatRect(maze_zones[j].rect.left, maze_zones[j].rect.top,
                                      32 * (1 + maze_walls[j].x), 32 * (1 + maze_walls[j].y)))) {

                    switch (players[i].get_direction()) {
                        case 1: {
                            players[i].set_coordinates({maze_zones[j].rect.left + 32 * (1 + maze_walls[j].x),
                                                        players[i].get_coordinates().y});
                            break;
                        }
                        case 2: {
                            players[i].set_coordinates(
                                    {maze_zones[j].rect.left - players[i].get_player_sprite_coordinates().width, \
                                players[i].get_coordinates().y});
                            break;
                        }
                        case 3: {
                            players[i].set_coordinates({players[i].get_coordinates().x, \
                                    maze_zones[j].rect.top + 32 * (1 + maze_walls[j].y)});
                            break;
                        }
                        case 4: {
                            players[i].set_coordinates({players[i].get_coordinates().x, \
                                maze_zones[j].rect.top - players[i].get_player_sprite_coordinates().height});
                            break;
                        }
                        default: {
                            players[i].set_coordinates(
                                    {maze_zones[j].rect.left - players[i].get_player_sprite_coordinates().width, \
                                maze_zones[j].rect.top - players[i].get_player_sprite_coordinates().height});
                            break;
                        }
                    }
                }
            }
            for (int j = 0; j < resource_spawn_areas.size(); ++j) {
                for (int k = 0; k < resource_positions[j].size(); ++k) {
                    if (players[i].get_sprite_rect().intersects(sf::FloatRect(resource_positions[j][k].x,
                                                                              resource_positions[j][k].y,
                                                                              resource_sprite_width,
                                                                              resource_sprite_height))) {
                        players[i].set_ship_resource(players[i].get_ship_resource() + 1);
                        is_got = true;
                        picked_item_area = j;
                        picked_item_index = k;
                        std::cout << '\t' << "pckd itm area: " << picked_item_area << '\t' << "pckd itm ind: "
                                  << picked_item_index
                                  << "\t X: " << resource_positions[j][k].x << "\t Y: "
                                  << resource_positions[j][k].y << std::endl;
                        resource_positions[j].erase(resource_positions[j].begin() + k);
                        for (int l = 0; l < resource_positions[j].size(); ++l) {
                            std::cout << "el nmb: " << l << "\t X: " << resource_positions[j][l].x << "\t Y: "
                                      << resource_positions[j][l].y << std::endl;
                        }
                    }
                }
            }
        }
    }
}
