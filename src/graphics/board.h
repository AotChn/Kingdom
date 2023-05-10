#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "constants.h"
#include "SFML/Graphics.hpp"

class board{
    public:

    board(){}

    void set_param(int r, int c);
    void draw_grid(int col, int row, sf::RenderWindow& window);
    void soldier(int i, int j, sf::RenderWindow& window);

    private: 
    int row;
    int col;

};




#endif