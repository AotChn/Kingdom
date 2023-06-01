#include "new_board.h"

//===========================================
//  Big 3, Set up 
//===========================================
    
    Board::Board(int r, int c): _grid(r,c), cur_ST(0){
        set_param();
        init_map();
    }
    void Board::set_param(){
        onBoard::DX = SCREEN_WIDTH  / _grid._col;
        onBoard::DY = SCREEN_HEIGHT / _grid._row;
    }
    void Board::init_map(){
        Stat p;
        p.set_probability(.1);

        for( int y = 0; y < _grid._row; ++y ){
            for(int x = 0; x < _grid._col; ++x){
                tile_t t(x,y);
                if(p.query()){
                    _units[t] = new Unit(t, 0);
                    _grid[t].empty = false;
                }
                else if(p.query()){
                }
                else{
                    
                }
            }
        }
    }
    
//===========================================
//	DRAW : cursor, grid, units, range, path, obstacle
//===========================================
    
    void Board::draw(sf::RenderWindow& window){
        while(!_draw_q.empty()){
            _draw_q.front()->draw(window);
            _draw_q.pop();
        }
    }
//===========================================
//	TILE INFO/ MANIPULATION
//===========================================
    


//===========================================
//	GATHER INFO
//===========================================


//===========================================
//	PROCCESS Event 
//===========================================
    void Board::update(){
        cur_ST = (this->*_s[cur_ST])();
    }
    void Board::onNotify(sf::RenderWindow& window, int event){
        switch (event)
        {
        case CUSTOM_SFEV::Draw :
            draw(window);
            return;
            break;
        default:
            break;
        }

        update();
    }


    int Board::idle(){
        _draw_q.push(&_grid);
        for(auto u : _units){
            _draw_q.push(u.second);
        }
        // draw_f[RANGE_D] = false; //won't draw "range"
        // draw_f[PATH_D] = false; //won't draw "path"

        // if(proc_f[RELEASE_P]){ //if mouse release
        //     proc_f[RELEASE_P] = false;
        //     if(!tiles.empty() && same_tile(tiles[0], cur)){ //if chose a unit && current pos == chosen unit
        //         return H_MOVE; //go to h_move
        //     }
        //     return IDLE; //else remain idle
        // }

        // if(proc_f[CLICK_P]){ //if mouse click
        //     proc_f[CLICK_P] = false;
            
        //     // printf("[Idle] -> [Click_P] tile info: empty? %d, mCost? %d, is_passable? %d\n", 
        //     // board_info[find_tile(cur)].empty, board_info[find_tile(cur)].mCost, is_passable(cur));

        //     if(tiles.empty() && unit_q.find(cur) != unit_q.end()){ //if never choose a unit &&  current position contains unit
        //         tiles.push_back(cur); //push this unit into the buffer
        //     }
        //     return IDLE;
        // }

        // if(proc_f[MOVE_P]){
        //     proc_f[MOVE_P] = false;
        //     return IDLE;
        // }



        return IDLE;

    }

    int Board::h_move(){
        
        // if(proc_f[RELEASE_P]){
        //     proc_f[RELEASE_P] = false;
        //     if(same_tile(tiles[1], cur)){
        //         if(find_distance(tiles[1].first, tiles[1].second) < 5 && board_info[find_tile(cur)].empty){
        //             cur_ST = MOVE;
        //             return (this->*s[cur_ST])();
        //         }
        //         //else
        //             tiles.clear();
        //         return IDLE;
        //     }
        //     else tiles.pop_back();
        //     return H_MOVE;
        // }

            
        // if(proc_f[CLICK_P]){
        //     proc_f[CLICK_P] = false;

        //     if(tiles.size() == 1){
        //         tiles.push_back(cur);
        //     }

        //     return H_MOVE;
        // }

        
        // if(proc_f[MOVE_P]){
        //     proc_f[MOVE_P] = false;
        //     return H_MOVE;
        // }
        
        
        return H_MOVE;
    }

    int Board::move(){
        // draw_f[RANGE_D] = false;
        // int a = tiles[0].first, b = tiles[0].second, 
        //     c = tiles[1].first, d = tiles[1].second;

        
        // move_unit(a, b, c, d, sf::Color::Red);
        // tiles.clear();

        return IDLE;
    }

    int Board::action(){
        // int i = sf::Mouse::getPosition(window).x/dx;
        // int j = sf::Mouse::getPosition(window).y/dy;
        // cursor(tiles[1].first, tiles[1].second,window, sf::Color(180,75,189,250));
        // cursor(i,j,window,sf::Color::Yellow);
        
        // return v ? ACTION : IDLE;
        return IDLE;
    }


//===========================================
//  BOOL SRC
//===========================================
