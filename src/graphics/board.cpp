#include "board.h"


//===========================================
//	TILE INFO/ MANIPULATION
//===========================================

tile board::sfml_to_tile(int coordx, int coordy){
    tile t;
    t.x  = coordx/dx;
    t.y = coordy/dy;
    return t;
}

void board::add(int coordx, int coordy, int unused){
    tiles.push_back(sfml_to_tile(coordx, coordy));
}

void board::add(tile t){
    tiles.push_back(t);
}

void board::add(int i, int j){
    tiles.push_back(tile(i,j));
}


int board::find_tile(int x, int y){
    return ((y*col)+x)+1;
} 

int board::find_tile(int coordx, int coordy, tile t){
    t.x = coordx/dx;
    t.y = coordy/dy;
    return ((t.y*4)+t.x)+t.y+1;
} 

int board::find_distance(tile a, tile b){
    int i = abs(a.x - b.x);
    int j = abs(a.y - b.y);
    return i+j;
}

int board::find_distance(){
    tile a = tiles[1];
    return find_distance(a, tiles[0]);
}

int board::find_distance(tile t){
    return find_distance(t,tiles[0]);
}

int board::find_distance(int x, int y){
    int i = abs(tiles[0].x - x);
    int j = abs(tiles[0].y - y);
    return i+j;
}


void board::set_param(int r, int c){
    row = r;
    col = c;
    dx = SCREEN_HEIGHT/row;
    dy = SCREEN_WIDTH/col;
    init_map();
}


//===========================================
//	DRAW
//===========================================

void board::draw(sf::RenderWindow& window){
    draw_grid(window);
    draw_cursor(window);
}

void board::draw_grid(sf::RenderWindow& window){
    for(int i=0;i<row;i++){
    sf::Vertex hori_lines[]={
        sf::Vertex(sf::Vector2f(0,i*dy),sf::Color(70,70,70,255)),
        sf::Vertex(sf::Vector2f(dy*row,i*dy),sf::Color(70,70,70,255))
        };
        window.draw(hori_lines,2,sf::Lines);
    }

    for(int i=0;i<col;i++){    
    sf::Vertex vert_lines[]={
        sf::Vertex(sf::Vector2f(i*dx,0),sf::Color(70,70,70,255)),
        sf::Vertex(sf::Vector2f(i*dx,dx*col),sf::Color(70,70,70,255))
        };
        window.draw(vert_lines,2,sf::Lines);
    }
    
    int a = sf::Mouse::getPosition(window).x;
    int b = sf::Mouse::getPosition(window).y;
    
}

void board::draw_tile(int i, int j, sf::RenderWindow& window, sf::Color c){
    int w = 15;
    sf::RectangleShape s;
    s.setFillColor(c); 
    s.setPosition(sf::Vector2f(dx*i,dy*j));
    s.setSize(sf::Vector2f(dx, dy));
    window.draw(s);
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

sf::RectangleShape board::unit(int i, int j, sf::Color c){
    int u = dx * 1/4;
    sf::RectangleShape s;
    s.setFillColor(c); 
    s.setPosition(sf::Vector2f(dx*i+u,dy*j+u));
    s.setSize(sf::Vector2f(dx/2, dy/2));
    return s;
}

void board::move_unit(int i, int j, int x, int y, sf::Color c){
   u[find_tile(i,j)] = 0;
   u[find_tile(i+x, j+y)] = 1;
}

void board::init_map(){
    stat p;
    p.set_probability(.1);

    int t = rand() % 10 + 1;
    std::cout<< row*col << std::endl;
    for(int i=0;i<(row*col); i++){
        if(p.query())
            u.push_back(1);
        else
            u.push_back(0);
    }
}

