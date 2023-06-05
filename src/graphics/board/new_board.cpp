#include "new_board.h"

//===========================================
//  Big 3, Set up 
//===========================================
    
    Board::Board(int r, int c): _grid(r,c), cur_ST(0), _hold(false){
        _cursor = Cursor();
        _cursor_tile = Tile();
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
                    Unit* u = new Infantry(t);
                    _units[t] = u;

                    _grid[t].empty = false;
                    _grid[t].mCost = 1;
                    _grid[t].u = u;
                }
                else if(p.query()){
                    _grid[t].empty = true;
                    _grid[t].mCost = 1;

                }
                else{
                    _grid[t].empty = true;
                    _grid[t].mCost = 1;
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
    
    cord_t Board::sfml_to_tile(cord_t tile){
        return std::make_pair(tile.first/onBoard::DX,tile.second/onBoard::DY);
    }


//===========================================
//	PROCCESS Event 
//===========================================
    
    void Board::update(){
        cur_ST = (this->*_s[cur_ST])();
    }
    
    void Board::onNotify(sf::RenderWindow& window, int event){
        cur_EV = event;
        switch (event)
        {
            case CUSTOM_SFEV::Draw:
                draw(window);
                return;
            break;
            case sf::Event::MouseMoved:
                //updating the cursor position 
                _cursor.set_cord(sfml_to_tile(getMousePosition(window)));
                //If holding the mouse, Do not update the cursor_tile
                if(!_hold)
                    _cursor_tile.set_cord(_cursor.get_cord());
            break;
            case sf::Event::MouseButtonReleased:
                std::printf("[Board]->[EV]-> MousePressed\n");
            {
                cur_EV = event;
                break;
            }
            
            case sf::Event::MouseButtonPressed:
                std::printf("[Board]->[EV]-> MouseReleased\n");
            {
                cur_EV = event;
                break;
            }
            default:{
                //Default = set event to Idle state (a custom event enum)
                cur_EV = CUSTOM_SFEV::Idle;
                
                //If holding the mouse, Do not update the cursor_tile
                if(!_hold)
                    _cursor_tile.set_cord(_cursor.get_cord());
                break;
            }
        }

        update();
    }


    int Board::idle(){
        //DrawQ
        _draw_q.push(&_grid); // grid to drawQ
        _draw_q.push(&_cursor_tile);// cursor_tile to drawQ
        for(auto u : _units){// all Units to drawQ
            _draw_q.push(u.second);
        }
        //-------


        tile_info* curTile = &_grid[_cursor.getPosition()];
        //get the current tile info

        switch (cur_EV){
        case sf::Event::MouseButtonReleased:{
            _hold = false;
            //if there is a pre_selected_tile AND the user certain to selecte that tile (press and release are on the same tile)
            if(!_select_buffer.empty() && _select_buffer[0] == curTile->u){
                //Go to Hmove But Before

                _path.setStart(_cursor.getPosition()); //set _path
                _path.setRange(curTile->u->getAp()); //set how many range for the unit
                _path.updateMap(&_grid); //And calcuate the _path
                _cursor_tile.setFillColor(VOID_COLOR); //color
                return H_MOVE;
            }
            else {
                _select_buffer.clear();
                // std::printf("->[IDLE]->[MouseReleased] : buffer cleared\n");
            }
            break;
        }
        case sf::Event::MouseButtonPressed:{
            //if not select a tile && current Tile have a controlable unit
            if(_select_buffer.empty() && curTile->u && curTile->u->isPC()){
                //Ready to getinto Hmove (go to MouseButtonRelased)
                _hold = true;  
                _select_buffer.push_back(curTile->u);
                // std::printf("->[IDLE]->[MousePressed] : selected tile\n");
            }
            break;
        }
        case sf::Event::MouseMoved:{
            //intended empty
        }
        default:{
            //if It is not holding then update the cursor_tile 
            if(curTile->u && curTile->u->isPC() && (!_hold)){   //Green for selectable 
                _cursor_tile.setOutLineColor(sf::Color::Green);
                _cursor_tile.setFillColor(VOID_COLOR);
            }
            else if (!_hold) { //Red for not-selectable
                _cursor_tile.setOutLineColor(sf::Color::Red);
                _cursor_tile.setFillColor(VOID_COLOR);
            }
            break;
        }   
        
    }
    
        return IDLE;

    }

    int Board::h_move(){
        //DrawQ (Grid, Units, path&Range, cursor_tile)
        _draw_q.push(&_grid);
        for(auto u : _units){
            _draw_q.push(u.second);
        }
        _draw_q.push(&_path);
        _draw_q.push(&_cursor_tile);
        //---------

        _path.setEnd(_cursor.getPosition()); //Update the dest of the path

        tile_info* curTile = &_grid[_cursor.getPosition()];
    
        switch (cur_EV)
        {
        case sf::Event::MouseButtonReleased:{
            
            break;
        }
        case sf::Event::MouseButtonPressed:{
            break;
        }
        case sf::Event::MouseMoved:{
            if(_path.within_range(_cursor.getPosition()) && !curTile->u){
                _cursor_tile.setOutLineColor(sf::Color::Green);
            }
            else{
                _cursor_tile.setOutLineColor(sf::Color::Red);
            }
        }
        case sf::Event::KeyPressed:
        default:
            break;
        }
    

        _select_buffer.clear();
        return H_MOVE;
        return IDLE;
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
