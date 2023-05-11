#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "constants.h"
#include "SFML/Graphics.hpp"
enum cursor_ST {IDLE, H_MOVE, MOVE, ACTION};
class board{
    public:

//set up 
    board() : valid(false){}
    void set_param(int r, int c);
    void init_map();
    
//===========================================
//	DRAW
//===========================================
    
    void draw(sf::RenderWindow& window);
    void draw_cursor(sf::RenderWindow& window);
    void draw_grid(sf::RenderWindow& window);
    void draw_units(sf::RenderWindow& window);
    void draw_range(int range, sf::RenderWindow& window);
    void draw_tile(int i, int j, sf::RenderWindow& window, sf::Color c);
    void cursor(int i, int j, sf::RenderWindow& window, sf::Color c);

//===========================================
//	TILE INFO/ MANIPULATION
//===========================================
    
    void add(int coordx, int coordy);

    std::pair<int,int> sfml_to_tile(int coordx, int coordy);
    int find_tile(int coordx, int coordy);
    int find_tile(int coordx, int coordy, std::pair<int,int> tile);
    int find_distance();
    int find_distance(int x, int y);
    int find_distance(std::pair<int,int> a, std::pair<int,int> b);

    sf::RectangleShape unit(int i, int j, sf::Color c);
    void move_unit(int i, int j, int x, int y, sf::Color c);

//===========================================
//	CURSOR STATES
//===========================================
    
    void update();
    int idle(bool v, sf::RenderWindow& window);
    int move(bool v, sf::RenderWindow& window);
    int h_move(bool v, sf::RenderWindow& window);
    int action(bool v, sf::RenderWindow& window);

    int(board::* IDLE_ST)(bool, sf::RenderWindow&) = &board::idle;
    int(board::*MOVE_ST)(bool, sf::RenderWindow&) = &board::move;
    int(board::*H_MOVE_ST)(bool, sf::RenderWindow&) = &board::h_move;
    int(board::*ACTION_ST)(bool, sf::RenderWindow&) = &board::action;


    private: 
    int row,
        col,
        dy,
        dx,
        cur_ST;
    bool valid;
    std::vector<int> u;
    int banjo[10][10] = {}; // why cant i delete this array
    std::vector<std::pair<int,int>> tiles;
    std::vector<int(board::*)(bool, sf::RenderWindow&)> s = {IDLE_ST,H_MOVE_ST,MOVE_ST,ACTION_ST};
};  


void board::update(){
    valid = !valid;
}


void board::draw_cursor(sf::RenderWindow& window){
    cur_ST = (this->*s[cur_ST])(valid, window);
}

void board::draw_units(sf::RenderWindow& window){
    for(int k=0; k<row; k++){
        for(int f=0; f<col; f++){
            if(u[find_tile(k,f)] == 1){
                window.draw(unit(k,f,sf::Color::Red));
            }     
        }
    }
}

void board::draw_range(int range, sf::RenderWindow& window){
    for(int i=0 ; i<col;i++){
            for(int j=0; j<row; j++){
                if(find_distance(i,j) < range){
                    draw_tile(i,j, window, sf::Color(51,78,232,100));
                }
            }
        }
}

int board::idle(bool v, sf::RenderWindow& window){
    int i = sf::Mouse::getPosition(window).x/dx;
    int j = sf::Mouse::getPosition(window).y/dy;
    int w = 15;
    if(u[find_tile(i,j)]==1)
        cursor(i,j,window, sf::Color::Green);
    else
        cursor(i,j,window, sf::Color::Red);
    draw_units(window);
    
    if(v && u[find_tile(i,j)]==1)
        return H_MOVE;
    return IDLE;

}

int board::h_move(bool v, sf::RenderWindow& window){
    int i = sf::Mouse::getPosition(window).x/dx;
    int j = sf::Mouse::getPosition(window).y/dy;
    draw_units(window);
    if(tiles.size() >= 1){
        draw_range(5, window);
    }
    window.draw(unit(tiles[0].first,tiles[0].second,sf::Color::Red));
    if(find_distance(i,j) < 5){
        draw_tile(i,j,window,sf::Color(51,78,232,200));
        if(!v){
            tiles.push_back(std::pair<int,int>{i,j});
            return MOVE;
        }
    }
    else
        cursor(i,j,window,sf::Color::Red);

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
    int i = sf::Mouse::getPosition(window).x/dx,
        j = sf::Mouse::getPosition(window).y/dy,
        a = tiles[0].first, b = tiles[0].second, 
        c = tiles[1].first, d = tiles[1].second;

    move_unit(a,b,-(a-c),-(b-d), sf::Color::Red);
    draw_units(window);
    cursor(c, d, window, sf::Color(180,75,189,250));
    cursor(i,j,window,sf::Color::Blue);
    draw_tile(c+1,d-1,window,sf::Color(180,75,189,150));
    draw_tile(c+1,d,window,sf::Color(180,75,189,150));
    
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