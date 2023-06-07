#ifndef BOARD__H
#define BOARD__H

#include "constants.h"

class Board : public Window_Observer
{

public:
    typedef std::pair<int,int> tile_t;
    typedef std::map<tile_t, tile_t> path_t;
    typedef std::map<Unit*,  bool> unitptr_bool;
    enum State {IDLE, H_MOVE, MOVE, ACTION};
//===========================================
//  Big 3, Set up 
//===========================================  
    Board(int r, int c);
    void set_param();
    void init_map();
    
//===========================================
//	DRAW : cursor, grid, range, path, units(obstacle, infantry)
//===========================================
    //draw what even is in the draw_q
    void draw(sf::RenderWindow& window);


private:
//===========================================
//	PROCCESS Event 
//===========================================
    virtual void onNotify(sf::RenderWindow& window, int event) override; 
    void update();
    int idle(); 
    int h_move();
    int action();
    int move();


    int(Board::*IDLE_ST)() = &Board::idle;
    int(Board::*MOVE_ST)() = &Board::move;
    int(Board::*H_MOVE_ST)() = &Board::h_move;
    int(Board::*ACTION_ST)() = &Board::action;


private: 
//===========================================
//	TILE INFO/ MANIPULATION
//===========================================
    cord_t sfml_to_tile(cord_t tile);

    //Drawable objects:

    Grid    _grid;  //grid 
    std::vector< unitptr_bool >_units; //the first list of _units[0] is player units
    Tile _cursor_tile; //Tile 
    Path _path; //Range->Path
    
    //Interal Stuff:
    int cur_ST;     //current State
    int cur_EV;     //current Event
    bool _hold;     //Holding the mouse?
    Cursor _cursor; //storing cursor position 
    unitptr_bool _already_moved; //A list of moved Units
    std::queue<onBoard*> _draw_q; //Queue of Items to be drawn on the Board
    std::vector<Unit*> _select_buffer; //if user select(click) on a tile, that tile will appear on the _selected_buffer
    std::deque<Command*> _cmdDQ;
    std::deque<Command*>::iterator _cmdDQ_it;
    std::vector<int(Board::*)()> _s = {IDLE_ST, H_MOVE_ST, MOVE_ST, ACTION_ST};
};  


#endif