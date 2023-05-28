#include "board_copy.h"

//===========================================
//	TILE INFO/ MANIPULATION
//===========================================


std::pair<int,int> board::sfml_to_tile(int coordx, int coordy){
    return make_pair(coordx/dx,coordy/dy);
}

bool board::is_valid(std::pair<int,int> tile){
    return tile.first >=0 && tile.first < row && tile.second >=0 && tile.second < col;
}

bool board::empty(std::pair<int,int> tile){
    return board_info[find_tile(tile.first, tile.second)].empty;
}
int board::mCost(std::pair<int,int> tile){
    return board_info[find_tile(tile.first, tile.second)].mCost;
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

std::vector<std::pair<int,int>> board::get_range(int range, std::pair<int,int> tile){
    std::queue<std::pair<tile_t, int>> q;
    std::vector<board::tile_t> r;
    std::map<tile_t, int> seen; 

    int ap = range;
    q.push(make_pair<tile_t, int>(tile, ap));
    seen[q.front().first];

    while (!q.empty())
    {   
        if(seen.find(q.front().first) == seen.end()){
            seen[q.front().first];
            r.push_back(q.front().first);
        }
        
        ap = q.front().second;
        if(ap != 0){            
            for(auto x : get_neighbors(q.front().first)){
                if(empty(x) || u[find_tile(x.first,x.second)] == 1){
                    if(seen.find(q.front().first) != seen.end())
                        q.push(make_pair<tile_t, int>(x, ap - mCost(x)));
                }

            }   
        }

        q.pop();
    }
    return r;
}

int board::find_tile(int x, int y){
    return ((y*col)+x)+1;
} 

int board::find_tile(int coordx, int coordy, std::pair<int,int> tile){
    tile.first = coordx/dx;
    tile.second = coordy/dy;
    return ((tile.second*col)+tile.first)+1;
} 

int board::find_distance(std::pair<int,int> a, std::pair<int,int> b){
    int i = abs(a.first - b.first);
    int j = abs(a.second - b.second);
    return i+j;
}

int board::find_distance(){
    std::pair<int,int> a = tiles[1];
    //tiles.pop_back();
    return find_distance(a, tiles[0]);
}

int board::find_distance(int x, int y){
    int i = abs(tiles[0].first - x);
    int j = abs(tiles[0].second - y);
    return i+j;
}

void board::set_param(int r, int c){
    row = r;
    col = c;
    dx = SCREEN_HEIGHT/row;
    dy = SCREEN_WIDTH/col;
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
}



//===========================================
//	DRAW
//===========================================

void board::draw(sf::RenderWindow& window){

    if(draw_f[GRID_D]){
        draw_grid(window);
        draw_f[GRID_D] = false;
    }


    if(draw_f[UNITS_D]){
        draw_units(window);
        draw_f[UNITS_D]= false;

    }

    if(draw_f[RANGE_D]){
        draw_range(4, window);
        draw_f[RANGE_D] = false;
    }


    if(draw_f[CURSOR_D]){
        draw_f[CURSOR_D] = false;
        draw_cursor(window);
    }

}

void board::draw_grid(sf::RenderWindow& window){
    sf::Vertex vert_lines[2], hori_lines[2];
    vert_lines[0].color = GRID_GREY;
    vert_lines[1].color = GRID_GREY;
    hori_lines[0].color = GRID_GREY;
    hori_lines[1].color = GRID_GREY;


    for(int i=0;i<row;i++){
        hori_lines[0].position = sf::Vector2f(0,i*dy);
        hori_lines[1].position = sf::Vector2f(dy*row,i*dy);

        window.draw(hori_lines,2,sf::Lines);
    }

    for(int i=0;i<col;i++){    
        vert_lines[0].position = sf::Vector2f(i*dx,0);
        vert_lines[1].position = sf::Vector2f(i*dx,dx*col);
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

void board::draw_range(int range, sf::RenderWindow& window){
    // for(int i=0 ; i<col;i++){
    //         for(int j=0; j<row; j++){
    //             if(find_distance(i,j) < range){
    //                 draw_tile(i,j, window, sf::Color(51,78,232,100));
    //             }
    //         }
    //     }

    for(auto x : get_range(range,tiles[0])){
        draw_tile(x.first, x.second, window, sf::Color(51,78,232,100));

    }
}

void board::draw_cursor(sf::RenderWindow& window){
    if(u[find_tile(cur.first,cur.second)] == 1){
        switch (cur_ST)
        {
            case IDLE:
                cursor(cur.first,cur.second, window, sf::Color::Green);
                break;
            case H_MOVE:
                break;
            case MOVE:
                break;
            case ACTION:
                break;
        }
    }
    else
    {
        switch (cur_ST)
        {
            case IDLE:
            case H_MOVE:
            case MOVE:
                cursor(cur.first,cur.second, window, sf::Color::Red);
                break;
        }
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
    if(proc_f[MOVE_P]){
        proc_f[MOVE_P] = false;
        draw_f[CURSOR_D] = true;
        return IDLE;
    }

    if(proc_f[CLICK_P]){
        proc_f[CLICK_P] = false;
        if(u[find_tile(cur.first, cur.second)] == 1){
            tiles.push_back(cur);
            return H_MOVE;
        }
    }


    return IDLE;

}

int board::h_move(){
    // int i = sf::Mouse::getPosition(window).x/dx;
    // int j = sf::Mouse::getPosition(window).y/dy;
    // draw_units(window);
    // if(tiles.size() >= 1){
    //     draw_range(5, window);
    // }
    // window.draw(unit(tiles[0].first,tiles[0].second,sf::Color::Red));
    
    
    // if(find_distance(i,j) < 5){ //if cursor is within the movable range
    //     draw_tile(i,j,window, SELECTED_LIGHTBLUE); 

    //     if(!v && u[find_tile(i,j)] != 1){
    //         tiles.push_back(std::pair<int,int>{i,j});
    //         return MOVE;
    //     }
    // }
    // else
    //     cursor(i,j,window,sf::Color::Red); //draw the cursor

    draw_f[RANGE_D] = true;
    // if(v)
        return H_MOVE;
    
    // else{
    //     while(!tiles.empty()){
    //         tiles.pop_back();
    //     }
        // return IDLE;
    // }

}

int board::move(){
    // int i = sf::Mouse::getPosition(window).x/dx,
    //     j = sf::Mouse::getPosition(window).y/dy,
    //     a = tiles[0].first, b = tiles[0].second, 
    //     c = tiles[1].first, d = tiles[1].second;

    // move_unit(a,b,-(a-c),-(b-d), sf::Color::Red);
    // draw_units(window);
    // cursor(c, d, window, sf::Color(180,75,189,250));
    // cursor(i,j,window,sf::Color::Blue);
    // draw_tile(c+1,d-1,window,sf::Color(180,75,189,150));
    // draw_tile(c+1,d,window,sf::Color(180,75,189,150));
    
    // if(v){
    //     update();
    //     while(!tiles.empty()){
    //         tiles.pop_back();
    //     }
    //     return IDLE;}
    // else
    //     return MOVE;
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
    draw_f[GRID_D] = true;
    draw_f[UNITS_D] = true;
}


void board::move_unit(int i, int j, int x, int y, sf::Color c){
   u[find_tile(i,j)] = 0;
   u[find_tile(i+x, j+y)] = 1;
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

}
