#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "constants.h"
#include "tile.h"
#include "SFML/Graphics.hpp"
#include "../bool_source/bool_source.h"
#include "../data/board_paths.h"

//sorry for scuffed code 

enum cursor_ST {IDLE, H_MOVE, MOVE, ACTION};
class board{
    public:

//set up 
    board() : cur_ST(0), valid(false){ }
    void set_param(int r, int c);
    void init_map();
    
//===========================================
//	DRAW
//===========================================
    
    void draw(sf::RenderWindow& window);
    void draw_path(tile,sf::RenderWindow& window);
    void draw_cursor(sf::RenderWindow& window);
    void draw_grid(sf::RenderWindow& window);
    void draw_units(sf::RenderWindow& window);
    void draw_range(int range, sf::RenderWindow& window);
    void draw_tile(int i, int j, sf::RenderWindow& window, sf::Color c);
    void draw_tile(tile, sf::RenderWindow& window, sf::Color c);
    void cursor(int i, int j, sf::RenderWindow& window, sf::Color c);

//===========================================
//	TILE INFO/ MANIPULATION
//===========================================
    
    void add(tile);
    void add(int,int);
    void add(int, int, int unused);

    tile sfml_to_tile(int coordx, int coordy);
    int find_tile(int coordx, int coordy);
    int find_tile(int coordx, int coordy, tile);
    int find_distance();
    int find_distance(tile);
    int find_distance(int x, int y);
    int find_distance(tile, tile);

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

//===========================================
//	BOOL UTILITIES
//===========================================
    bool is_unit(int coordx, int coordy, int unused);
    bool is_unit(tile t,int i=0, int j=0){return u[find_tile(t.x+i,t.y+j)] > 0;}
    bool is_unit(int i, int j){return u[find_tile(i,j)] > 0;}
    bool in_range(int i, int j, int range){return find_distance(i,j) < range;}
    void empty_tiles();
    void empty_tiles_one();
    bool is_idle(){return cur_ST == 0;}


    private: 
    int row,
        col,
        dy,
        dx,
        cur_ST;
    bool valid;
    board_paths H;
    std::vector<int> u;
    std::vector<tile> tiles;
    std::vector<int(board::*)(bool, sf::RenderWindow&)> s = {IDLE_ST, H_MOVE_ST, MOVE_ST, ACTION_ST};
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
    
    if(v && is_unit(i,j)){
        empty_tiles();
        add(i,j);
        return H_MOVE;
    }
    return IDLE;

}

int board::h_move(bool v, sf::RenderWindow& window){
    int i = sf::Mouse::getPosition(window).x/dx;
    int j = sf::Mouse::getPosition(window).y/dy;
    draw_units(window);
    cursor(tiles[0].x,tiles[0].y,window,sf::Color(212, 162, 25,255));
    if(tiles.size() >= 1){
        draw_range(5, window);
    }
    window.draw(unit(tiles[0].x,tiles[0].y,sf::Color::Red));
    if(find_distance(i,j) < 5){
        if(!v && u[find_tile(i,j)] != 1){
            tiles.push_back(tile(i,j));
            return MOVE;
        }
        else if(!v && u[find_tile(i,j)] == 1){
            tiles.push_back(tile(i,j));
            return ACTION;
        }
        //draw_path(tile(i,j),window);
            
        
    }
    else{
        cursor(i,j,window,sf::Color::Red);
        empty_tiles_one();
    }

    if(v)
        return H_MOVE;
    
    else{
        empty_tiles();
        return IDLE;
    }
}

int board::move(bool v, sf::RenderWindow& window){
    int i = sf::Mouse::getPosition(window).x/dx,
        j = sf::Mouse::getPosition(window).y/dy,
        s = tiles.size(),
        a = tiles[0].x, b = tiles[0].y, 
        c = tiles[s-1].x, d = tiles[s-1].y;

        // if(H.find_path(tiles[0],tile(i,j))) // BUGGED AF 
        //     draw_tile(tiles[0],window,sf::Color::Yellow);
        // else
        //     draw_tile(tiles[0],window,sf::Color::Red);

    move_unit(a,b,-(a-c),-(b-d), sf::Color::Red);
    draw_units(window);
    cursor(c, d, window, sf::Color(180,75,189,250));
    cursor(i,j,window,sf::Color::Blue);
   // draw_tile(c+1,d-1,window,sf::Color(180,75,189,150)); //pink
    //draw_tile(c+1,d,window,sf::Color(180,75,189,150)); //pink
    
    if(v){
        update();
        return IDLE;}
    else
        return MOVE;
}
int board::action(bool v, sf::RenderWindow& window){
    int i = sf::Mouse::getPosition(window).x/dx;
    int j = sf::Mouse::getPosition(window).y/dy;
    int a = tiles[0].x, b = tiles[0].y, 
        s = tiles.size(),
        c = tiles[s-1].x, d = tiles[s-1].y;
    move_unit(a,b,-(a-c),-(b-d), sf::Color::Red);
    draw_units(window);
    draw_tile(c,d,window,sf::Color(212, 162, 25,150));

    if(v){
        update();
        return IDLE;}
    else 
        return ACTION;
}

void board::empty_tiles(){
    while(!tiles.empty()){
        tiles.pop_back();
    }
}

void board::empty_tiles_one(){
    while(tiles.size() > 1){
        tiles.pop_back();
    }
}

bool board::is_unit(int coordx, int coordy, int unused){
    return is_unit(sfml_to_tile(coordx, coordy));
}

/* possible 
we can figure out if we can reach i,j from x,y by finding the move vector <k,h>
s.t. k = horizonal movemnt ; vertical axis movement
we can then use the vector k,h and iterate for k and h until we find blocking 

*/
void board::draw_path(tile start, sf::RenderWindow& window){
    int range = find_distance(start,tiles[0]);
    int last = tiles.size()-1;
    if(find_distance(start,tiles[last]) == 1){
        if(!is_unit(start)){
            tiles.push_back(start);
        }
    }
    std::cout<<tiles.size() << std::endl;
    for(int i=1;i<tiles.size();i++){
        draw_tile(tiles[i].x,tiles[i].y,window,sf::Color::Yellow);
    }
}



/*

x x x x 
x o o x
x o x x
x o x x


x O O O O D
O x x x x O
O O O O x O
O O O O x O
T O O O x O


*/

//cursor states 
// idle -> click tile with own unit -> toggle movement -> click on valid movespace -> toggle action -> click action 

// idle - hovering screen and moves cursor with mouse 
//click title with own unit - opens all movement spaces possible highlighted 
// toggle movement - when hovering over tilespace that is valid will shift color 
// click on valid movespace - unit will go there and open actions menu 
// toggle action - hovering over options space will move the cursor 
// click action - will perform the action [attack, stay]

//im not sure why this shit does not work 
//the path finding uses too much cpu? power 
//for some reason there is an offset in the bool graph but other than that it it is correct 


#endif