#include "board.h"

int find_idx(int x, int y){
    return (y*4)+x;
}

void board::set_param(int r, int c){
    row = r;
    col = c;
}

void board::draw_grid(int c, int r, sf::RenderWindow& window){
    set_param(r,c);
    int dy = SCREEN_HEIGHT/row;
    int dx = SCREEN_WIDTH/col;
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
    
    int a = sf::Mouse::getPosition(window).x/dx;
    int b = sf::Mouse::getPosition(window).y/dy;

    soldier(a,b,window);
}

void board::soldier(int i, int j, sf::RenderWindow& window){
    int dy = SCREEN_HEIGHT/row;
    int dx = SCREEN_WIDTH/col;
    sf::RectangleShape s;
    s.setFillColor(sf::Color::Red); 
    s.setPosition(sf::Vector2f(dx*i,dy*j));
    s.setSize(sf::Vector2f(dx-5, dy-5));

    window.draw(s);
}

