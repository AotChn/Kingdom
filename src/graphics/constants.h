#ifndef G_CONSTANTS_H
#define G_CONSTANTS_H

#include <SFML/Graphics.hpp>
#include "color_constants.h"

const unsigned int SCREEN_WIDTH = 900;
const unsigned int SCREEN_HEIGHT = 800;

enum CUSTOM_SFEV{
    Idle = -1,
    Draw = sf::Event::EventType::Count,
    
};
#endif