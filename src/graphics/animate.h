#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "board_copy.h"

class animate{
    public: 
    
    animate();
    void run();
    void draw();
    void render();
    void update();
    void process_events();

    private: 
    board b;
    sf::RenderWindow window;
}; 

#endif