#include <iostream>

#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/Packet.hpp>

#include "Models.h"


sf::Packet operator>> (sf::Packet &packet, Event &received_event) {
    int type_number;
    packet >> type_number;
    switch(type_number) {
        case 0: {
            received_event.type = user_init;
            break;
        }
        case 1: {
            received_event.type = dir_left;
            break;
        }
        case 2: {
            received_event.type = dir_right;
            break;
        }
        case 3: {
            received_event.type = dir_straight;
            break;
        }
        case 4: {
            received_event.type = dir_back;
            break;
        }
        case 5: {
            received_event.type = is_intersect_with_player;
            break;
        }
        case 6: {
            received_event.type = is_intersect_with_map;
            break;
        }
        case 7: {
            received_event.type = got_ship_resource;
            break;
        }
        default: {
            received_event.type = error;
            break;
        }
    }
    packet >> received_event.client_number;
    packet >> received_event.resources_data.picked_item_area;
    packet >> received_event.resources_data.picked_item_index;
    for (int i = 0; i < 2; ++i) {
        packet >> received_event.resources_data.ship_resource_count[i] >> received_event.user_moved.coordinates[i].x >> received_event.user_moved.coordinates[i].y \
        >> received_event.user_moved.sprite_coordinates[i].begin_x >> received_event.user_moved.sprite_coordinates[i].begin_y \
        >> received_event.user_moved.sprite_coordinates[i].height >> received_event.user_moved.sprite_coordinates[i].width;
    }
    int size;
    float x, y;
    for (int i = 0; i < RESOURCE_SPAWN_ZONE_COUNT; ++i) {
        packet >> received_event.resources_data.resource_spawn_areas[i].rect.left >> received_event.resources_data.resource_spawn_areas[i].rect.top;
        if (!received_event.resources_data.resource_positions_to_send) {
            continue;
        }
        received_event.resources_data.received_resource_positions[i].clear();
        packet >> size;
        for (int j = 0; j < size; ++j) {
            packet >> x >> y;
            received_event.resources_data.received_resource_positions[i].emplace_back(x,y);
        }
    }
    for (int i = 0; i < MAZE_SPAWN_ZONE_COUNT; ++i) {
        packet >> received_event.maze_data.maze_zones[i].rect.left >> received_event.maze_data.maze_zones[i].rect.top;
        packet >> x >> y;
        if (x == 0 && y != 0) {++y;}
        if (x != 0 && y == 0) {++x;}
        received_event.maze_data.maze_walls[i].x = x;
        received_event.maze_data.maze_walls[i].y = y;
    }
    return packet;
}

sf::Packet operator<< (sf::Packet &packet, Event &received_event) {
    packet << received_event.type;
    packet << received_event.client_number;
    packet << received_event.resources_data.picked_item_area;
    packet << received_event.resources_data.picked_item_index;
    for (int i = 0; i < 2; ++i) {
        packet << received_event.resources_data.ship_resource_count[i] << received_event.user_moved.coordinates[i].x << received_event.user_moved.coordinates[i].y \
 << received_event.user_moved.sprite_coordinates[i].begin_x << received_event.user_moved.sprite_coordinates[i].begin_y \
        << received_event.user_moved.sprite_coordinates[i].height << received_event.user_moved.sprite_coordinates[i].width;
    }
    for (int i = 0; i < RESOURCE_SPAWN_ZONE_COUNT; ++i) {
        packet << received_event.resources_data.resource_spawn_areas[i].rect.left << received_event.resources_data.resource_spawn_areas[i].rect.top;
        if (!received_event.resources_data.resource_positions_to_send) {
            continue;
        }
        packet << (int)received_event.resources_data.resource_positions_to_send[i].size();
        for (auto & j : received_event.resources_data.resource_positions_to_send[i]) {
            packet << j.x << j.y;
        }
    }
    for (int i = 0; i < MAZE_SPAWN_ZONE_COUNT; ++i) {
        packet << received_event.maze_data.maze_zones[i].rect.left << received_event.maze_data.maze_zones[i].rect.top;
        packet << received_event.maze_data.maze_walls[i].x << received_event.maze_data.maze_walls[i].y;
    }
    return packet;
}

int main() {
    EventBus event_bus;

    Player players[2];
    players[0].set_player_number(0);
    players[1].set_player_number(1);

    Collision collision(players, 2);
    event_bus.subscribe(&collision, is_intersect_with_player);
    event_bus.subscribe(&collision, is_intersect_with_map);

    for (auto & player : players) {
        event_bus.subscribe(&player, dir_back);
        event_bus.subscribe(&player, dir_straight);
        event_bus.subscribe(&player, dir_right);
        event_bus.subscribe(&player, dir_left);
    }

    Event event_to_send;

    sf::Packet packet;
    sf::TcpListener listener;
    //data clients_data[2];


    if (listener.listen(PORT) != sf::Socket::Done) {
        std::cout << "ERROR OF NETWORK" << std::endl;
    }

    sf::TcpSocket clients[2];

    if (listener.accept(clients[0]) != sf::Socket::Done) {
        std::cout << "ERROR OF NETWORK" << std::endl;
    }

    event_to_send.resources_data.picked_item_index = -1;
    event_to_send.resources_data.picked_item_area = -1;
    event_to_send.resources_data.resource_spawn_areas = collision.get_resource_spawn_areas();
    event_to_send.resources_data.resource_positions_to_send = collision.get_resource_positions();
    event_to_send.maze_data.maze_walls = collision.get_maze_walls();
    event_to_send.maze_data.maze_zones = collision.get_maze_zones();

    event_to_send.type = user_init;
    players[0].set_coordinates({300, 1500});
    SpriteCoord player_initialise = {0, 0, 32,  32 };
    players[0].set_player_sprite_coordinates(player_initialise);
    event_to_send.user_moved.coordinates[0] = players[0].get_coordinates();
    event_to_send.user_moved.sprite_coordinates[0] = players[0].get_player_sprite_coordinates();
    event_to_send.resources_data.ship_resource_count[0] = 0;


    if (listener.accept(clients[1]) != sf::Socket::Done) {
        std::cout << "ERROR OF NETWORK" << std::endl;
    }

    players[1].set_coordinates({500, 1200});
    player_initialise = {0, 4*32, 32,  32 };
    players[1].set_player_sprite_coordinates(player_initialise);
    event_to_send.user_moved.coordinates[1] = players[1].get_coordinates();
    event_to_send.user_moved.sprite_coordinates[1] = players[1].get_player_sprite_coordinates();
    event_to_send.resources_data.ship_resource_count[1] = 0;

    packet.clear();
    event_to_send.client_number = 0;
    packet << event_to_send;
    clients[0].send(packet);

    packet.clear();
    event_to_send.client_number = 1;
    packet << event_to_send;
    clients[1].send(packet);

    for (auto & client : clients) {
        client.setBlocking(false);
    }

    /*for (auto & player : players) {
        event_bus.subscribe(&player, is_intersect);
    }*/

    Event received_event;

    while (true) {
        for (int i = 0; i < 2; ++i) {
            collision.set_picked_item_index(-1);
            event_to_send.resources_data.picked_item_area = -1;
            event_to_send.resources_data.picked_item_index = -1;
            collision.set_is_got(false);
            packet.clear();
            if (clients[i].receive(packet) == sf::Socket::NotReady) {
                continue;
            }
            packet >> received_event;
            /*if (received_event.type != user_init) {
                std::cout << received_event.type << std::endl;
            }*/
            received_event.moved_player_number = i;
            event_bus.dispatch(received_event.type, received_event);

            for (int j = 0; j < 2; ++j) {
                event_to_send.user_moved.coordinates[j] = players[j].get_coordinates();
                event_to_send.user_moved.sprite_coordinates[j] = players[j].get_player_sprite_coordinates();
            }
            players[i].set_direction(received_event.type);
            event_to_send.moved_player_number = i;
            event_to_send.type = is_intersect_with_player;
            event_bus.dispatch(is_intersect_with_player, event_to_send);
            event_to_send.type = is_intersect_with_map;
            event_bus.dispatch(is_intersect_with_map, event_to_send);
            for (int j = 0; j < 2; ++j) {
                event_to_send.user_moved.coordinates[j] = players[j].get_coordinates();
                event_to_send.resources_data.ship_resource_count[j] = players[j].get_ship_resource();
            }
            for (int j = 0; j < 2; ++j) {
                event_to_send.client_number = j;
                if (collision.get_is_got()) {
                    event_to_send.resources_data.picked_item_index = collision.get_picked_item_index();
                    event_to_send.resources_data.picked_item_area = collision.get_picked_item_area();
                    event_to_send.type = got_ship_resource;
                }
                packet.clear();
                packet << event_to_send;
                clients[j].send(packet);
            }
        }
    }
    return 0;
}