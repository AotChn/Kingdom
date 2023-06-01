#pragma once

#include "../constants.h"
#include "unit/unit.h"
#include "type_def.h"
#include "terrain.h"
#include "onBoard.h"

struct tile_info{
    tile_info(bool _empty = true, int _mCost  = 1): empty(_empty), mCost(_mCost){}
    bool empty;
    int mCost;
    Unit* u = nullptr;
    Terrain* t = nullptr;
};

class Grid : public onBoard{
public:
    int _row, _col;
    Grid(int r, int c): _row(r), _col(c){ _grids = new tile_info[r * c]; }

    /*****************************************************
     * VIRTUAL 
     */
    virtual void draw(sf::RenderWindow& window){
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
    /*****************************************************
     * GETTER 
     */
    tile_info operator[](const int index)const{return _grids[index];}
    tile_info& operator[](const int index){return _grids[index];}
    tile_info operator[](const cord_t cord)const{ return _grids[ find_tile(cord) ]; }
    tile_info& operator[](const cord_t cord){ return _grids[ find_tile(cord) ]; }


    /*****************************************************
     * NAVIGATOR
     */
    int find_tile(cord_t tile) const {
        assert(tile.first >= 0 && tile.first < _col);
        assert(tile.second >= 0 && tile.second < _row);
        return ((tile.second*_row)+tile.first);
    }
    //return the index of the "tile" in _grids array
private:
    tile_info* _grids;
};