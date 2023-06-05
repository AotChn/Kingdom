#pragma once

#include "type_def.h"
#include "onBoard.h"
#include "grids.h"

typedef std::map<cord_t,cord_t> cordt_cordt;
typedef std::map<cord_t,ap_t> cordt_int;

class Range : public onBoard
{   

public:
    // friend class Path;
    static cordt_cordt trace_map;
    static cordt_int trace_ap;

    /*****************************************************
     * BIG3
     */
    Range(cord_t where = cord_t(), int range = 0) : onBoard(where), _range(range){}
    
    /*****************************************************
     * VIRTUAL 
     */
    
    //before drawing, call setRange/setPosition to setup the parameter,
    // And then call call updateMap to calculate the range;
    virtual void draw(sf::RenderWindow& window){
        int& dx = onBoard::DX, &dy = onBoard::DY;
        sf::RectangleShape s;
        s.setSize(sf::Vector2f(dx, dy));
        //draw center tile 
        s.setFillColor(RANGE_YELLOW); 
        s.setPosition( sf::Vector2f( dx*get_cord().first, dy*get_cord().second) );
        window.draw(s);

        s.setFillColor(RANGE_BLUE); 
        for(auto t : _trace_map){
            s.setPosition(sf::Vector2f(dx*t.first.first, dy*t.first.second));
            window.draw(s);

        }
    }

    /*****************************************************
     *  GETTER 
     */
    //If the tile is within the range, return true, else false;
    inline bool within_range(cord_t tile);

    /*****************************************************
     * MUTATOR 
     */

    //Set the action point(range)
    inline void setRange(int range);

    //Set this object to the board
    void setBoard(Grid* board){
        _board = board;
    }
    
    //Calculate the map, and update the global map object
    void updateMap(Grid* board = nullptr){
        if(board)
            setBoard(board);
        getRangeAll();
    }

private:
    cordt_cordt _trace_map;
    Grid* _board;
    int _range;

    //Calculate and Update the Map
    void getRangeAll();
};


    

void Range::setRange(int range){
    _range = range;
}

bool Range::within_range(cord_t tile){
    return _trace_map.find(tile) != _trace_map.end();
}

