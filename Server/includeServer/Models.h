//
// Created by alexey on 08.12.2021.
//

#ifndef ISLANDGAME_MODELS_H
#define ISLANDGAME_MODELS_H

#include <time.h>

#include <SFML/Graphics.hpp>

#include "EventBus.h"

enum Team {
    first,
    second,
};

class Model : public IObservable {
public:
    virtual void update(Event event) override = 0;
};

class Player : public Model {
public:
    Player() {
        coordinates = {0,0};
        speed = 4;
        player_number = 0;
        player_sprite_coordinates = {.begin_x = 0, .begin_y = 0, .height = 32, .width = 32};
        ship_resource = 0;
    }

    sf::Vector2f get_coordinates() {
        return coordinates;
    }

    void set_coordinates(sf::Vector2f new_coordinates) {
        coordinates = new_coordinates;
    }


    int get_player_number() const {
        return player_number;
    }

    void set_player_number(int number) {
        player_number = number;
    }

    float get_speed() const {
        return speed;
    }


    SpriteCoord get_player_sprite_coordinates() {
        return player_sprite_coordinates;
    }


    int get_direction() {
        return direction;
    }

    void set_direction(int new_direction) {
        direction = new_direction;
    }

    void set_player_sprite_coordinates(SpriteCoord &new_player_sprite_coordinates) {
        player_sprite_coordinates.begin_x = new_player_sprite_coordinates.begin_x;
        player_sprite_coordinates.begin_y = new_player_sprite_coordinates.begin_y;
        player_sprite_coordinates.height = new_player_sprite_coordinates.height;
        player_sprite_coordinates.width = new_player_sprite_coordinates.width;
    }

    int get_ship_resource() {
        return ship_resource;
    }

    void set_ship_resource(int new_ship_resource) {
        ship_resource = new_ship_resource;
    }

    sf::FloatRect get_sprite_rect() {
        return sf::FloatRect(coordinates, {static_cast<float>(player_sprite_coordinates.width), static_cast<float>(player_sprite_coordinates.height)});
    }
private:
    sf::Vector2f coordinates;
    float speed;
    int direction;
    int player_number;
    int ship_resource;
    Team team;
    SpriteCoord player_sprite_coordinates;

    virtual void update(Event event) override;
};

class Collision : public Model {
public:
    Collision(Player (&players)[2], int player_count) : players(players), player_count(player_count), is_got(false) {
        srand((unsigned int) time(NULL));
        map.load("../Client/srcClient/main_map_two.xml");
        resource_spawn_areas = map.getObjectsByName("res");
        objects_solid = map.getObjectsByName("Solid");
        maze_zones = map.getObjectsByName("maze");
        for (int i = 0; i < resource_spawn_areas.size(); i++ ) {
            for (int j = 0; j < QUANTITY_RES; j++) {
                resource_positions[i].emplace_back(resource_spawn_areas[i].rect.left + ((rand() % (int)(resource_spawn_areas.at(i).rect.width / 32) + 1) * 32.f),
                                                 (resource_spawn_areas[i].rect.top + (rand() % (int)(resource_spawn_areas.at(i).rect.height / 32) + 1) * 32.f));
            }
        }
        resource_sprite_width = 32;
        resource_sprite_height = 32;
        for (auto & maze_zone : maze_zones) {
            maze_walls.emplace_back(rand() % (int)(maze_zone.rect.width / 32), rand() % (int)(maze_zone.rect.height / 32));
        }
    };

    virtual void update(Event event) override;

    bool get_is_got() const {
        return is_got;
    }

    void set_is_got(bool is) {
        is_got = is;
    }

    int get_picked_item_index() const {
        return picked_item_area;
    }

    int get_picked_item_area() const {
        return picked_item_area;
    }
    void set_picked_item_index(int new_picked_item_index) {
        picked_item_area = new_picked_item_index;
    }

    std::vector<sf::Vector2f>* get_resource_positions() {
        return resource_positions;
    }

    std::vector<Object> get_resource_spawn_areas() {
        return resource_spawn_areas;
    }

    std::vector<Object> get_maze_zones() {
        return maze_zones;
    }

    std::vector<sf::Vector2f> get_maze_walls() {
        return maze_walls;
    }

private:
    Player (&players)[2];
    int player_count;
    TileMap map;
    std::vector<sf::Vector2f> resource_positions[RESOURCE_SPAWN_ZONE_COUNT];
    float resource_sprite_width;
    float resource_sprite_height;
    int picked_item_index;
    int picked_item_area;
    std::vector<sf::Vector2f> maze_walls;
    std::vector<Object> maze_zones;
    std::vector<Object> resource_spawn_areas;
    std::vector<Object> objects_solid;
    bool is_got;
};

#endif //ISLANDGAME_MODELS_H