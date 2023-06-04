#pragma once
#include <SFML/Graphics.hpp>
#include "pair_helper.h"

std::pair<int,int> getMousePosition(sf::RenderWindow& window);
//Return mouse position as std::pair
