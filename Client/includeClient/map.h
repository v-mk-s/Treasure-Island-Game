//
// Created by ser on 11.12.2021.
//

#ifndef ISLANDGAME_MAP_H
#define ISLANDGAME_MAP_H

#include <SFML/Graphics.hpp>
#include <view.h>

class Map:View {
public:
    static const int HEIGHT_MAP = 20; // Высота карты
    static const int WIDTH_MAP = 20;  // Ширина карты
    sf::String TileMap[HEIGHT_MAP] = {
            "ssssssssssssssssssss",
            "s000000000000000000s",
            "s000000000000k00000s",
            "s00000k000000000000s",
            "s000000000000000000s",
            "s000000000000000000s",
            "s000000000000000000s",
            "s000000000k00000000s",
            "s000000000000000000s",
            "s000000000000000000s",
            "s000000000000000000s",
            "s000000000000000000s",
            "s000000000000000000s",
            "s000000000000000000s",
            "s00000k000000000000s",
            "s000000000000000000s",
            "s000000000000k00000s",
            "s000000000000000000s",
            "s000000000000000000s",
            "ssssssssssssssssssss",
    };
    Map(const std::string& path_to_file, struct SpriteCoord coord, sf::Vector2f pos) : View(path_to_file, coord,
            pos) {};
    void render(sf::RenderWindow& window) {
        for (int i = 0; i < HEIGHT_MAP; i++) // идём по строкам
            for (int j = 0; j < WIDTH_MAP; j++)  // идём по столбцам
            {
                if (TileMap[i][j] == 's') {
                    hero_sprite.setTextureRect(
                            sf::IntRect(192, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
                }
                if ((TileMap[i][j] == '0')) {
                    hero_sprite.setTextureRect(
                            sf::IntRect(64, 0, 32, 32)); //если встретили символ 0, то рисуем 3й квадратик
                }
                if ((TileMap[i][j] == 'k')) {
                    hero_sprite.setTextureRect(
                            sf::IntRect(128, 96, 32, 32)); //если встретили символ 0, то рисуем 3й квадратик
                }
                hero_sprite.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

                window.draw(hero_sprite);//рисуем квадратики на экран
            }
    };

};
#endif //ISLANDGAME_MAP_H
