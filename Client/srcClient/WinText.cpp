#include "ResourceText.h"
#include <iostream>

void WinText::text_render(int resource_count, sf::Vector2f coordinates) {
    //resource_count_string.clear();
    //resource_count_string << resource_count;
    if (resource_count == 0) {
        text.setString("You have won!");
    } else {
        text.setString("You have lost!");
    }
    text.setPosition(coordinates.x - 300, coordinates.y);
}
