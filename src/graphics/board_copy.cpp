#include "board_copy.h"

//===========================================
//	TILE INFO/ MANIPULATION
//===========================================


std::pair<int,int> board::sfml_to_tile(int coordx, int coordy){
    return make_pair(coordx/dx,coordy/dy);
}

bool board::is_valid(std::pair<int,int> tile){
    return tile.first >=0 && tile.first < col && tile.second >=0 && tile.second < row;
}

bool board::empty(std::pair<int,int> tile){
    return board_info[find_tile(tile.first, tile.second)].empty;
}

int board::mCost(std::pair<int,int> tile){
    return board_info[find_tile(tile.first, tile.second)].mCost;
}

bool board::same_tile(tile_t t1, tile_t t2){
    return (t2 == t1 && t2.second == t1.second );
}


std::vector<std::pair<int,int>> board::get_neighbors(std::pair<int,int> tile){
    std::vector<tile_t> v;

    tile_t dir = make_pair(tile.first + 1, tile.second);
    if(is_valid(dir))
        v.push_back(dir);

    dir = make_pair(tile.first - 1, tile.second);
    if(is_valid(dir))
        v.push_back(dir);

    dir = make_pair(tile.first, tile.second - 1);
    if(is_valid(dir))
        v.push_back(dir);

    dir = make_pair(tile.first, tile.second + 1);
    if(is_valid(dir))
        v.push_back(dir);


    return v;
}

board::path_t board::get_range(int range, std::pair<int,int> tile){
    //Sorry this is not dijkstra but just bredth-first search
    std::queue<std::pair<tile_t, int>> q;
    path_t r;
    std::map<tile_t, int> seen; 

    tile_t cur = tile;
    int ap = range;
    q.push(make_pair<tile_t, int>(tile, ap));
    seen[cur] = ap;

    while (!q.empty())
    {   
        cur = q.front().first;
        ap = q.front().second;
        if(seen.find(cur) == seen.end()){
            seen[q.front().first] = ap;
        }
        
        if(ap != 0){            
            for(auto x : get_neighbors(cur)){
                if(empty(x) || u[find_tile(x.first,x.second)] == 1){ //if the tile is passible
                    if(seen.find(x) == seen.end() || seen[q.front().first] < ap){ //if never been here || been here but this time cost less ap
                        q.push(make_pair<tile_t, int>(x, ap - mCost(x))); //step into this tile
                        r[x] = cur;//and set the tile's parent to current tile
                    }
                }

            }   
        }

        q.pop();
    }
    return r;
}

board::path_t board::get_range_all(tile_t tile){
    std::queue<std::pair<tile_t, int>> q;
    path_t r;
    std::map<tile_t, int> seen; 

    tile_t cur = tile;
    int ap = 0;
    q.push(make_pair<tile_t, int>(tile, ap));
    seen[cur] = ap;

    while (!q.empty())
    {   
        ap = q.front().second;
        cur = q.front().first;
        if(seen.find(cur) == seen.end()){
            seen[q.front().first] = ap;
        }
        
          
        for(auto x : get_neighbors(q.front().first)){
            if(empty(x) || u[find_tile(x.first,x.second)] == 1){ //if the tile is passible
                if(seen.find(x) == seen.end() || seen[q.front().first] > ap + mCost(x)){ //if never been here || been here but this time cost less ap
                    q.push(make_pair<tile_t, int>(x, ap + mCost(x))); //step into this tile
                    r[x] = cur;//and set the tile's parent to current tile
                }
            }

        }   
        

        q.pop();
    }
    return r;
}

int board::find_tile(int x, int y){
    return ((y*row)+x);
} 

int board::find_tile(tile_t tile){
    return find_tile(tile.first, tile.second);
}

int board::find_tile(int coordx, int coordy, std::pair<int,int> tile){
    tile.first = coordx/dx;
    tile.second = coordy/dy;
    return ((tile.second*col)+tile.first)+1;
} 

int board::find_distance(std::pair<int,int> start, std::pair<int,int> des){
    auto path = get_range_all(start);
    int ap = 0;
    for(auto last = des; last != start; last = path[last]){
        ap += board_info[find_tile(last)].mCost;
    }
    return ap;
}

int board::find_distance(){
    std::pair<int,int> des = tiles[1];
    //tiles.pop_back();
    return find_distance(tiles[0], des);
}

int board::find_distance(int x, int y){

    return find_distance(tiles[0], tile_t(x,y));
}

void board::set_param(int r, int c){
    row = r;
    col = c;
    dx = SCREEN_WIDTH/col;
    dy = SCREEN_HEIGHT/row;
    init_map();
}

void board::init_map(){
    Stat p;
    p.set_probability(.1);

    int t = rand() % 10 + 1;
    std::cout<< row*col << std::endl;
    for(int i=0;i<(row*col); i++){
        if(p.query()){
            u.push_back(1);
            board_info.push_back(board_tile(false, 1));
        }
        else{
            u.push_back(0);
            board_info.push_back(board_tile(true, 1));

        }
    }

    assert(board_info.size() == row * col && "board size is incorrect");
}



//===========================================
//	DRAW
//===========================================

void board::draw(sf::RenderWindow& window){

    if(draw_f[GRID_D]){
        draw_grid(window);
    }
    else if(!hold) draw_f[GRID_D] = true;

    if(draw_f[UNITS_D]){
        draw_units(window);
    }
    else if(!hold) draw_f[UNITS_D]= false;


    if(draw_f[RANGE_D]){
        // std::cout << "[Drew]-> ready to draw Range\n";
        draw_range(window);
    }
    else if(!hold) draw_f[RANGE_D] = true;
    

    if(draw_f[CURSOR_D]){
        draw_cursor(window);

    }
    else if(!hold) draw_f[CURSOR_D] = true;

}

void board::draw_grid(sf::RenderWindow& window){
    sf::Vertex vert_lines[2], hori_lines[2];
    vert_lines[0].color = GRID_GREY;
    vert_lines[1].color = GRID_GREY;
    hori_lines[0].color = GRID_GREY;
    hori_lines[1].color = GRID_GREY;


    for(int i=0;i<row;i++){
        hori_lines[0].position = sf::Vector2f(0,i*dy);
        hori_lines[1].position = sf::Vector2f(dx*col,i*dy);

        window.draw(hori_lines,2,sf::Lines);
    }

    for(int i=0;i<col;i++){    
        vert_lines[0].position = sf::Vector2f(i*dx,0);
        vert_lines[1].position = sf::Vector2f(i*dx,dy*row);
        window.draw(vert_lines,2,sf::Lines);
    }
    
    // int a = sf::Mouse::getPosition(window).x;
    // int b = sf::Mouse::getPosition(window).y;
    
}

void board::draw_tile(int i, int j, sf::RenderWindow& window, sf::Color c){
    int w = 15;
    sf::RectangleShape s;
    s.setFillColor(c); 
    s.setPosition(sf::Vector2f(dx*i,dy*j));
    s.setSize(sf::Vector2f(dx, dy));
    window.draw(s);
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

void board::draw_range(sf::RenderWindow& window){

    draw_tile(tiles[0].first, tiles[0].second, window, RANGE_YELLOW); //the center
    // std::cout << "[Drew]-> [Draw_range] -> tiles[0]: "; printf("(%d,%d)\n", tiles[0].first, tiles[0].second); 
    // std::cout << "[Drew]-> [Draw_range] -> cur: "; printf("(%d,%d)\n", cur.first, cur.second); 
    for(auto x : get_range(4, tiles[0])){
    // for(auto x : get_range_all(tiles[0])){
        draw_tile(x.first.first, x.first.second, window, RANGE_BLUE);
    }
}

void board::draw_cursor(sf::RenderWindow& window){
    switch (cur_ST)
    {
    
    case IDLE:{
            if(u[find_tile(cur.first,cur.second)] == 1) 
                cursor(cur.first,cur.second, window, sf::Color::Green);
            else 
                cursor(cur.first,cur.second, window, sf::Color::Red);
            break; 
        }
    
    case H_MOVE:{
        // std::cout << "[Drew]->[draw_cursor]->Entering H move\n";
        // std::cout << "[Drew]->[draw_cursor]-> dis == " <<find_distance(cur.first, cur.second) << "\n";

        if(find_distance(cur.first, cur.second) < 5){

            if( same_tile(cur, tiles[0]) || u[find_tile(cur.first,cur.second)] == 1 )
                 cursor(cur.first,cur.second, window, sf::Color::Red);
            else draw_tile(cur.first,cur.second,window, SELECTED_BLUE); 
        }
        else{

            cursor(cur.first,cur.second, window, sf::Color::Red);
        }
        break;  
    }

    default:
        break;
    }
}

void board::cursor(int i, int j, sf::RenderWindow& window, sf::Color c){
    int w = 15;
    sf::RectangleShape s;
    s.setFillColor(c); 
    s.setPosition(sf::Vector2f((dx*i)-(dx/w),dy*j));
    s.setSize(sf::Vector2f((dx/w), dy));
    window.draw(s);
    s.setPosition(sf::Vector2f((dx*(i+1)),dy*j));
    s.setSize(sf::Vector2f((dx/w), dy));
    window.draw(s);
    s.setPosition(sf::Vector2f((dx*i),(dy*j)-(dy/w)));
    s.setSize(sf::Vector2f((dx), dy/w));
    window.draw(s);
    s.setPosition(sf::Vector2f((dx*i),dy*(j+1)));
    s.setSize(sf::Vector2f((dx), dy/w));
    window.draw(s);
}


//===========================================
//	EVENT
//===========================================


int board::idle(){
    draw_f[RANGE_D] = false; //won't draw "range"

    if(proc_f[RELEASE_P]){ //if mouse release
        proc_f[RELEASE_P] = false;
        if(!tiles.empty() && same_tile(tiles[0], cur)){ //if chose a unit && current pos == chosen unit
            return H_MOVE; //go to h_move
        }
        return IDLE; //else remain idle
    }

    if(proc_f[CLICK_P]){ //if mouse click
        proc_f[CLICK_P] = false;
        if(tiles.empty() && u[find_tile(cur.first, cur.second)] == 1){ //if never choose a unit &&  current position contains unit
            tiles.push_back(cur); //push this unit into the buffer
        }
        return IDLE;
    }

    if(proc_f[MOVE_P]){
        proc_f[MOVE_P] = false;
        return IDLE;
    }



    return IDLE;

}

int board::h_move(){
    
    if(proc_f[RELEASE_P]){
        proc_f[RELEASE_P] = false;
        if(same_tile(tiles[1], cur)){
            if(find_distance(tiles[1].first, tiles[1].second) < 5 && board_info[find_tile(cur)].empty){
                cur_ST = MOVE;
                return (this->*s[cur_ST])();
            }
            //else
                tiles.clear();
            return IDLE;
        }
        else tiles.pop_back();
        return H_MOVE;
    }

        
    if(proc_f[CLICK_P]){
        proc_f[CLICK_P] = false;

        if(tiles.size() == 1){
            tiles.push_back(cur);
        }

        return H_MOVE;
    }

    
    if(proc_f[MOVE_P]){
        proc_f[MOVE_P] = false;
        return H_MOVE;
    }
    
    
    return H_MOVE;
}

int board::move(){
    draw_f[RANGE_D] = false;
    int a = tiles[0].first, b = tiles[0].second, 
        c = tiles[1].first, d = tiles[1].second;

    
    move_unit(a, b, c, d, sf::Color::Red);
    tiles.clear();

    return IDLE;
}

int board::action(){
    // int i = sf::Mouse::getPosition(window).x/dx;
    // int j = sf::Mouse::getPosition(window).y/dy;
    // cursor(tiles[1].first, tiles[1].second,window, sf::Color(180,75,189,250));
    // cursor(i,j,window,sf::Color::Yellow);
    
    // return v ? ACTION : IDLE;
}

void board::update(){
    cur_ST = (this->*s[cur_ST])();
}



void board::move_unit(int i, int j, int x, int y, sf::Color c){
    int a = find_tile(i, j), b = find_tile(x,y);
    u[a] = 0;
    board_info[a].empty = true;
    u[b] = 1;
    board_info[b].empty = false;

}

sf::RectangleShape board::unit(int i, int j, sf::Color c){
    int u = dx * 1/4;
    sf::RectangleShape s;
    s.setFillColor(c); 
    s.setPosition(sf::Vector2f(dx*i+u,dy*j+u));
    s.setSize(sf::Vector2f(dx/2, dy/2));
    return s;
}


void board::cursor_move(int x, int y){
    cur = sfml_to_tile(x,y);
    proc_f[MOVE_P] =  true;
}

void board::cursor_click(int x, int y){
    cur = sfml_to_tile(x,y);
    proc_f[CLICK_P] =  true;
    hold = true;
}

void board::cursor_idle(){
    
}

void board::cursor_release(int x, int y){
    cur = sfml_to_tile(x,y);
    proc_f[RELEASE_P] =  true;
    hold = false;
}