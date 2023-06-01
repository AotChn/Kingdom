#ifndef G_CONSTANTS_H
#define G_CONSTANTS_H

#include <SFML/Graphics.hpp>

const unsigned int SCREEN_WIDTH = 900;
const unsigned int SCREEN_HEIGHT = 800;

const sf::Color GRID_GREY(70,70,70,255);
const sf::Color SELECTED_BLUE(51,78,232,200);
const sf::Color BACKGROUND_DARK(20, 20, 20,255);
const sf::Color RANGE_YELLOW(239,246,25,150);
const sf::Color RANGE_BLUE(51,78,232,100);


enum CUSTOM_SFEV{
    Draw = sf::Event::EventType::Count
};
#endif