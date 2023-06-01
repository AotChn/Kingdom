#include "unit.h"

Unit::ap_t Unit::ap = 4;

sf::RectangleShape Unit::unit(sf::Color c){
    int u = DX * 1/4;
    sf::RectangleShape s;
    s.setFillColor(c); 
    s.setPosition(sf::Vector2f( DX * get_cord().first + u, DY * get_cord().second + u ) );
    s.setSize(sf::Vector2f(DX/2, DY/2));
    return s;
}