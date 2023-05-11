#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "constants.h"
#include "SFML/Graphics.hpp"
enum cursor_ST {IDLE, H_MOVE, MOVE, ACTION};
class board{
    public:

    board() : valid(false){}

    void set_param(int r, int c);
    void draw(sf::RenderWindow& window);
    

    void add(int coordx, int coordy);
    void draw_grid(sf::RenderWindow& window);
    void soldier(int i, int j, sf::RenderWindow& window, sf::Color c);
    void cursor(int i, int j, sf::RenderWindow& window, sf::Color c);
    int find_tile(int coordx, int coordy);
    int find_tile(int coordx, int coordy, std::pair<int,int> tile);
    int find_distance(std::pair<int,int> a, std::pair<int,int> b);
    int find_distance();
    int find_distance(int x, int y);
    void show_units(sf::RenderWindow& window);
    sf::RectangleShape move_unit(int i, int j, int x, int y, sf::RectangleShape u, sf::Color c);
    sf::RectangleShape unit(int i, int j, sf::Color c);
    std::pair<int,int> sfml_to_tile(int coordx, int coordy);

    void draw_cursor(sf::RenderWindow& window);
    void update();
    void set_board(board Board);
    int idle(bool v, sf::RenderWindow& window);
    int move(bool v, sf::RenderWindow& window);
    int h_move(bool v, sf::RenderWindow& window);
    int action(bool v, sf::RenderWindow& window);

    int(board::* IDLE_ST)(bool, sf::RenderWindow&) = &board::idle;
    int(board::*MOVE_ST)(bool, sf::RenderWindow&) = &board::move;
    int(board::*H_MOVE_ST)(bool, sf::RenderWindow&) = &board::h_move;
    int(board::*ACTION_ST)(bool, sf::RenderWindow&) = &board::action;


    //private: 
    int row;
    int col;
    int dy;
    int dx;
    int units[10][10] = {{0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,1,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {1,0,1,0,1,1,0,0,0,1},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,1,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,1,0},
                        {0,0,1,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0}};
    sf::RectangleShape u;
    std::vector<std::pair<int,int>> tiles;
    bool valid; 
    int cur_ST;
    int(board::*s[4])(bool, sf::RenderWindow&) = {IDLE_ST,H_MOVE_ST,MOVE_ST,ACTION_ST};
};  


void board::update(){
    valid = !valid;
}


void board::draw_cursor(sf::RenderWindow& window){
    cur_ST = (this->*s[cur_ST])(valid, window);
}

void board::show_units(sf::RenderWindow& window){
    for(int k=0; k<10; k++){
        for(int f=0; f<10; f++){
            if(units[k][f] == 1){
                u = unit(k,f,sf::Color::Red);
                window.draw(u);  
            }     
        }
    }
}

int board::idle(bool v, sf::RenderWindow& window){
    //std::cout<< dx << " | " << dy << std::endl;
    int i = sf::Mouse::getPosition(window).x/dx;
    int j = sf::Mouse::getPosition(window).y/dy;
    int w = 15;
    cursor(i,j,window, sf::Color::Red);
    show_units(window);
    
    if(v && units[i][j]==1)
        return H_MOVE;
    return IDLE;
    
    //return v ? H_MOVE : IDLE;
}

int board::h_move(bool v, sf::RenderWindow& window){
    int i = sf::Mouse::getPosition(window).x/dx;
    int j = sf::Mouse::getPosition(window).y/dy;
    show_units(window);
    if(tiles.size() >= 1){
        for(int k=0 ; k<col;k++){
            for(int m=0; m<row; m++){
                if(find_distance(k,m) < 4){
                    soldier(k,m, window, sf::Color(51,78,232,100));
                }
            }
        }
    }
    window.draw(unit(tiles[0].first,tiles[0].second,sf::Color::Red));
    if(find_distance(i,j) < 5){
        soldier(i,j,window,sf::Color(51,78,232,200));
        if(!v){
            tiles.push_back(std::pair<int,int>{i,j});
            return MOVE;
        }
    }
    else
        cursor(i,j,window,sf::Color::Green);

    if(v)
        return H_MOVE;
    
    else{
        while(!tiles.empty()){
            tiles.pop_back();
        }
        return IDLE;
    }
}

int board::move(bool v, sf::RenderWindow& window){
    int i = sf::Mouse::getPosition(window).x/dx;
    int j = sf::Mouse::getPosition(window).y/dy;
    int a = tiles[0].first, b = tiles[0].second, c = tiles[1].first, d = tiles[1].second;
    cursor(c, d,window, sf::Color(180,75,189,250));
    u = move_unit(a,b,-(a-c),-(b-d), u, sf::Color::Red);
    show_units(window);
    cursor(i,j,window,sf::Color::Blue);
    soldier(c+1,d-1,window,sf::Color(180,75,189,150));
    soldier(c+1,d,window,sf::Color(180,75,189,150));
    
    if(v){
        update();
        while(!tiles.empty()){
            tiles.pop_back();
        }
        return IDLE;}
    else
        return MOVE;
    
}
int board::action(bool v, sf::RenderWindow& window){
    int i = sf::Mouse::getPosition(window).x/dx;
    int j = sf::Mouse::getPosition(window).y/dy;
    cursor(tiles[1].first, tiles[1].second,window, sf::Color(180,75,189,250));
    cursor(i,j,window,sf::Color::Yellow);
    
    return v ? ACTION : IDLE;
}

//cursor states 
// idle -> click tile with own unit -> toggle movement -> click on valid movespace -> toggle action -> click action 

// idle - hovering screen and moves cursor with mouse 
//click title with own unit - opens all movement spaces possible highlighted 
// toggle movement - when hovering over tilespace that is valid will shift color 
// click on valid movespace - unit will go there and open actions menu 
// toggle action - hovering over options space will move the cursor 
// click action - will perform the action [attack, stay]



#endif