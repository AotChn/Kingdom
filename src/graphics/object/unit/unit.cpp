#include "unit.h"

sf::RectangleShape Unit::unit(sf::Color c){
    int u = DX * 1/4;
    sf::RectangleShape s;
    s.setFillColor(c); 
    s.setPosition(sf::Vector2f(DX*_cord.first+u,DY*_cord.second+u));
    s.setSize(sf::Vector2f(DX/2, DY/2));
    return s;
}