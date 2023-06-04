#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "observer/Window_Observer.h"

using namespace std;

class animate: public Window_Subject{
    public: 
    
    animate();
    void run();
    void draw();
    void render();
    void update();
    void process_events();

    private: 
    sf::RenderWindow window;
}; 

#endif