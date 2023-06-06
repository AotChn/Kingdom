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
    Grid(int r, int c);

    /*****************************************************
     * VIRTUAL 
     */
    virtual void draw(sf::RenderWindow& window);
    /*****************************************************
     * GETTER 
     */
    inline tile_info operator[](const int index)const;
    inline tile_info& operator[](const int index);
    inline tile_info operator[](const cord_t cord)const;
    inline tile_info& operator[](const cord_t cord);

    tile_info& getTile(cord_t cord){
        return _grids[find_tile(cord)];
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

    /*****************************************************
     * NAVIGATOR / BOOL_SRC 
     */
        //return the index of the "tile" in _grids array
    inline int find_tile(cord_t tile) const;
        //return true if the cord is valid, else false;
    inline bool is_valid(cord_t tile) const;
        //return true if the cord is passable, else false;
    inline bool is_passable(cord_t tile) const;
        //return a vector of the neighbors of the tile
    std::vector<cord_t> get_neighbors(cord_t tile);
        //return the movement Cost of the tile
    inline ap_t get_mCost(cord_t tile);
    
private:

    tile_info* _grids;
};


tile_info Grid::operator[](const int index)const{
    assert(index < _row * _col);
    return _grids[index];
}
tile_info& Grid::operator[](const int index){
    assert(index < _row * _col);
    return _grids[index];
}
tile_info Grid::operator[](const cord_t cord)const{ return _grids[ find_tile(cord) ]; }
tile_info& Grid::operator[](const cord_t cord){ return _grids[ find_tile(cord) ]; }


inline int Grid::find_tile(cord_t tile) const {
    return ((tile.second*_row)+tile.first);
}
//return the index of the "tile" in _grids array

inline bool Grid::is_valid(cord_t tile) const{
    return tile.first >=0 && tile.first < _col && tile.second >=0 && tile.second < _row;
}

inline bool Grid::is_passable(cord_t tile) const{
    return (_grids[find_tile(tile)].empty || _grids[find_tile(tile)].u->isPC());
}

inline ap_t Grid::get_mCost(cord_t tile){
    auto t = _grids[find_tile(tile)];
    auto m = t.mCost;

    if(t.u) m += t.u->get_mCost();
    if(t.t) m += t.t->get_mCost();
    return m;
}
