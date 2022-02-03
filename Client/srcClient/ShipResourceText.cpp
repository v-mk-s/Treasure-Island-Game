#include "ResourceText.h"
#include <iostream>

void ShipResourceText::text_render(int resource_count, sf::Vector2f coordinates) {
    //resource_count_string.clear();
    //resource_count_string << resource_count;
    resource_count_string = std::to_string(resource_count);
    text.setString("Ship resources: " + resource_count_string);
    text.setPosition(coordinates.x-450, coordinates.y-360);
}
