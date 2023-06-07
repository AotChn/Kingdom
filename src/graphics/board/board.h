#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <Queue>
#include <Map>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "../constants.h"
#include "../object/entity/unit.h"
#include "../observer/Window_Observer.h"
#include "../../bool_source/bool_source.h"


enum cursor_ST {IDLE, H_MOVE, MOVE, ACTION};
enum proc_FLAG {CLICK_P, MOVE_P, RELEASE_P};
enum draw_FLAG {CURSOR_D, GRID_D, UNITS_D, RANGE_D, PATH_D, OBSTACLE_D};


const int MAX_PORC = 3;
const int MAX_DRAW = 6;

struct board_tile
{
    board_tile(bool _empty, int _mCost): empty(_empty), mCost(_mCost){}
    bool empty = true;
    int mCost = 1;
};


class board : public Window_Observer
{

public:
    typedef std::pair<int,int> tile_t;
    typedef std::map<tile_t, tile_t> path_t;
//===========================================
//  Big 3, Set up 
//===========================================
    
    board() : cur_ST(0), hold(false){
        for(auto x = 0; x < MAX_PORC; ++x){
            proc_f[x] = false;
        }

        for(auto x = 0; x < MAX_DRAW; ++x){
            draw_f[x] = true;
        }
    };
    void set_param(int r, int c);
    void init_map();
    
//===========================================
//	DRAW : cursor, grid, units, range, path, obstacle
//===========================================
    
    void draw(sf::RenderWindow& window);
    void draw_cursor(sf::RenderWindow& window);
    void draw_grid(sf::RenderWindow& window);
    void draw_units(sf::RenderWindow& window);          //Draw all the [units] on the window /FIN
    void draw_range(sf::RenderWindow& window);          
    void draw_path(sf::RenderWindow& window);
    void draw_obstacle(sf::RenderWindow& window);
    void draw_tile(int i, int j, sf::RenderWindow& window, sf::Color c);
    void cursor(int i, int j, sf::RenderWindow& window, sf::Color c);

//===========================================
//	TILE INFO/ MANIPULATION
//===========================================
    
    tile_t sfml_to_tile(int coordx, int coordy);
    std::vector<tile_t> get_neighbors(tile_t tile);
    path_t get_range(int range, tile_t tile);
    path_t get_range_all(tile_t tile);

    int find_tile(tile_t tile);
    int find_tile(int coordx, int coordy);
    int find_tile(int coordx, int coordy, tile_t holder);
    int find_distance();
    int find_distance(int x, int y);
    int find_distance(tile_t start, tile_t des);

    sf::RectangleShape unit(int i, int j, sf::Color c);
    void move_unit(int i, int j, int x, int y, sf::Color c);


//===========================================
//	GATHER INFO
//===========================================

    void cursor_click(int x, int y);    //called if cursor click, inputting position info
    void cursor_move(int x, int y);     //called if cursor moved, inputting position info
    void cursor_idle();                 //called if cursor didn't move
    void cursor_release(int x, int y);

//===========================================
//	PROCCESS Event 
//===========================================
    void update();
    void onNotify(sf::RenderWindow& window, int event) override;


    int idle(); 
    int h_move();
    int action();
    int move();


    int(board::*IDLE_ST)() = &board::idle;
    int(board::*MOVE_ST)() = &board::move;
    int(board::*H_MOVE_ST)() = &board::h_move;
    int(board::*ACTION_ST)() = &board::action;
//===========================================
//  BOOL SRC
//===========================================

    bool same_tile(tile_t t1, tile_t t2);
    bool is_valid(tile_t tile);     //tile is valid?
    bool is_passable(tile_t tile);  //unit can pass through?

    bool empty(tile_t tile);    //tile is empty?
    int mCost(tile_t  tile);    //return movement cost to that tile


private: 
    int row,
        col,
        dy,
        dx,
        cur_ST;
    bool draw_f[MAX_DRAW];
    bool proc_f[MAX_PORC];
    tile_t cur;     //Cursor position

    bool hold;     
    std::map<cord_t, Unit> unit_q; //array of all units

    std::vector<tile_t> tiles;  //buffer of clicked tiles
    std::vector<board_tile> board_info;  //recording information of each tile

    std::vector<int(board::*)()> s = {IDLE_ST, H_MOVE_ST, MOVE_ST, ACTION_ST};
};  



// cursor states 
// idle -> click tile with own unit -> toggle movement -> click on valid movespace -> toggle action -> click action 

// idle - hovering screen and moves cursor with mouse 
// click title with own unit - opens all movement spaces possible highlighted 
// toggle movement - when hovering over tilespace that is valid will shift color 
// click on valid movespace - unit will go there and open actions menu 
// toggle action - hovering over options space will move the cursor 
// click action - will perform the action [attack, stay]



#endif