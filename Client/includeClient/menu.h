//
// Created by ser on 06.12.2021.
//
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#ifndef ISLANDGAME_MENU_H
#define ISLANDGAME_MENU_H

void menu(sf::RenderWindow &window) { // Передаём переменную по ссылке
    sf::Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
    menuTexture1.loadFromFile("images/111.png");
    menuTexture2.loadFromFile("images/222.png");
    menuTexture3.loadFromFile("images/333.png");
    aboutTexture.loadFromFile("images/about.png");
    menuBackground.loadFromFile("images/Penguins.jpg");
    sf::Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
    bool isMenu = 1;
    int menuNum = 0;
    menu1.setPosition(100, 30);
    menu2.setPosition(100, 90);
    menu3.setPosition(100, 150);
    menuBg.setPosition(345, 0);

    //////////////////////////////МЕНЮ///////////////////
    while (isMenu)
    {
        menu1.setColor(sf::Color::White);
        menu2.setColor(sf::Color::White);
        menu3.setColor(sf::Color::White);
        menuNum = 0;
        window.clear(sf::Color(129, 181, 221));

        if (sf::IntRect(100, 30, 300, 50).contains(sf::Mouse::getPosition(window))) { menu1.setColor(sf::Color::Blue); menuNum = 1; }
        if (sf::IntRect(100, 90, 300, 50).contains(sf::Mouse::getPosition(window))) { menu2.setColor(sf::Color::Blue); menuNum = 2; }
        if (sf::IntRect(100, 150, 300, 50).contains(sf::Mouse::getPosition(window))) { menu3.setColor(sf::Color::Blue); menuNum = 3; }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню
            if (menuNum == 2) { window.draw(about); window.display(); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)); }
            if (menuNum == 3)  { window.close(); isMenu = false; }

        }

        window.draw(menuBg);
        window.draw(menu1);
        window.draw(menu2);
        window.draw(menu3);

        window.display();
    }
    ////////////////////////////////////////////////////
}

#endif //ISLANDGAME_MENU_H
