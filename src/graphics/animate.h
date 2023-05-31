#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "board_copy.h"
#include "../observer/Window_iobserver.h"

class animate: public Window_Subject{
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