#include "grids.h"


Grid::Grid(int r, int c): _row(r), _col(c){ _grids = new tile_info[r * c]; }

void Grid::draw(sf::RenderWindow& window){
    sf::Vertex vert_lines[2], hori_lines[2];
    vert_lines[0].color = GRID_GREY;
    vert_lines[1].color = GRID_GREY;
    hori_lines[0].color = GRID_GREY;
    hori_lines[1].color = GRID_GREY;


    for(int i=0;i<_row;i++){
        hori_lines[0].position = sf::Vector2f(0,i*DY);
        hori_lines[1].position = sf::Vector2f(DX*_col,i*DY);

        window.draw(hori_lines,2,sf::Lines);
    }

    for(int i=0;i<_col;i++){    
        vert_lines[0].position = sf::Vector2f(i*DX,0);
        vert_lines[1].position = sf::Vector2f(i*DX,DY*_row);
        window.draw(vert_lines,2,sf::Lines);
    }

}

std::vector<cord_t> Grid::get_neighbors(cord_t tile){
    std::vector<cord_t> v;

    //North
    cord_t dir = std::make_pair(tile.first, tile.second + 1); 
    if(is_valid(dir))
        v.push_back(dir);

    //East
    dir = std::make_pair(tile.first + 1, tile.second);
    if(is_valid(dir))
        v.push_back(dir);

    //South
    dir = std::make_pair(tile.first, tile.second - 1);
    if(is_valid(dir))
        v.push_back(dir);

    //West
    dir = std::make_pair(tile.first - 1, tile.second);
    if(is_valid(dir))
        v.push_back(dir);

    return v;
}