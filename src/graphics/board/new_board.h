#ifndef BOARD__H
#define BOARD__H

#include "constants.h"

class Board : public Window_Observer
{

public:
    typedef std::pair<int,int> tile_t;
    typedef std::map<tile_t, tile_t> path_t;
    typedef std::map<tile_t, Unit*> tile_unitptr;
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
    cord_t sfml_to_tile(cord_t tile);


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

    //Drawable objects:
    int cur_ST;     //current state
    int cur_EV;     //current Event
    Grid    _grid;  //grid object
    tile_unitptr _units; //map, key = cord_t | data = unit*
    Tile _cursor_tile; //Tile object

    std::vector<Unit*> _select_buffer;
    Cursor _cursor;
    std::queue<onBoard*> _draw_q; //Queue of Items to be drawn on the Board
    std::vector<int(Board::*)()> _s = {IDLE_ST, H_MOVE_ST, MOVE_ST, ACTION_ST};
};  


#endif