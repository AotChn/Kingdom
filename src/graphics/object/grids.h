#pragma once

#include "../constants.h"
#include "entity/unit.h"
#include "type_def.h"
#include "terrain.h"
#include "onBoard.h"
struct tile_info{
    tile_info(bool _empty = true, int _mCost  = 1): empty(_empty), mCost(_mCost){
        u = nullptr;
        t = nullptr;
    }
    bool empty;
    int mCost;
    Unit* u ;
    Terrain* t;
};

class Grid : public onBoard{
public:
    int _row, _col;

    Grid(int r, int c): _row(r), _col(c){ _grids = new tile_info[r * c]; }

    
    /*****************************************************
     * GETTER 
     */
    tile_info operator[](const int index)const{
        assert(index < _row * _col);
        return _grids[index];
    }
    tile_info operator[](const cord_t& cord)const{
         return _grids[ find_tile(cord) ]; 
    }

    //return how many cols;
    int get_col()const {
        return _col;
    }
    //return how many rows;
    int get_row()const {
        return _row;
    }
    /*****************************************************
     * MUTATOR
     */

    //place unit to the tile of _grid[unit->_cord]    
    //Post: set tile t.empty to false && t.u = unit
    void attachUnit(Unit* unit){
        tile_info& t = _grids[find_tile(unit->get_cord())];
        t.empty = false;
        t.u = unit;
    }

    //Detach unit from _grid ["tile"], if there is any  
    //Post: set tile t.empty to true && t.u = nullptr
    void detachUnit(cord_t tile){
        tile_info& t = getTile(tile);
        t.u = nullptr;
        t.empty = true;
    }
    
    //use grid object as a 1d array.
    //given a coordinate , return the information object corresponding to that tile
    tile_info& operator[](const cord_t& cord){ 
        return _grids[ find_tile(cord) ]; 
    }
    tile_info& operator[](const int index){
        assert(index < _row * _col);
        return _grids[index];
    }
    tile_info& getTile(cord_t cord){
        return _grids[find_tile(cord)];
    }
    
    /*****************************************************
     * NAVIGATOR / BOOL_SRC 
     */
    //return the index of the "tile" in _grids array
    inline int find_tile(cord_t tile) const{
        return ((tile.second*_row)+tile.first);
    }

    //return true if the cord is valid, else false;
    inline bool is_valid(cord_t tile) const{
        return tile.first >=0 && tile.first < _col && tile.second >=0 && tile.second < _row;
    }
    
    //return true if the cord is passable, else false;
    inline bool is_passable(cord_t tile) const{
        return (_grids[find_tile(tile)].empty || _grids[find_tile(tile)].u->isPC());
    }

    inline bool is_empty(cord_t tile) const{
        return _grids[find_tile(tile)].empty;
    }

    //return a vector of the neighbors of the tile
    std::vector<cord_t> get_neighbors(cord_t tile){
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
    
    //return the movement Cost of the tile
    inline ap_t get_mCost(cord_t tile){
        auto t = _grids[find_tile(tile)];
        auto m = t.mCost;

        if(t.u) m += t.u->get_mCost();
        if(t.t) m += t.t->get_mCost();
        return m;
    }

    //Draw the grids

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

private:
    tile_info* _grids;
};




