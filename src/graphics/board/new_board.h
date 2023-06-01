#ifndef BOARD__H
#define BOARD__H

#include "constants.h"

class Board : public Window_Observer
{

public:
    typedef std::pair<int,int> tile_t;
    typedef std::map<tile_t, tile_t> path_t;
    typedef std::map<tile_t, Unit*> tile_unit;
    enum State {IDLE, H_MOVE, MOVE, ACTION};
//===========================================
//  Big 3, Set up 
//===========================================
    
    Board(int r, int c);
    void set_param();
    void init_map();
    
//===========================================
//	DRAW : cursor, grid, units, range, path, obstacle
//===========================================
    
    void draw(sf::RenderWindow& window);


//===========================================
//	TILE INFO/ MANIPULATION
//===========================================
    


//===========================================
//	GATHER INFO
//===========================================


//===========================================
//	PROCCESS Event 
//===========================================
    void update();
    virtual void onNotify(sf::RenderWindow& window, int event) override; 

    int idle(); 
    int h_move();
    int action();
    int move();


    int(Board::*IDLE_ST)() = &Board::idle;
    int(Board::*MOVE_ST)() = &Board::move;
    int(Board::*H_MOVE_ST)() = &Board::h_move;
    int(Board::*ACTION_ST)() = &Board::action;

//===========================================
//  BOOL SRC
//===========================================


private: 
    int cur_ST;     //current state
    Grid    _grid;  //grid object
    tile_unit _units; //map, key = cord_t | data = unit*
    std::queue<onBoard*> _draw_q;
    std::vector<int(Board::*)()> _s = {IDLE_ST, H_MOVE_ST, MOVE_ST, ACTION_ST};
};  


#endif