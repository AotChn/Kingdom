#include "sfml_helper.h"
#include <utility>

std::pair<int,int> getMousePosition(sf::RenderWindow& window){
    return make_pair(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
}