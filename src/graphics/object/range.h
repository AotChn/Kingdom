#pragma once

#include "type_def.h"
#include "onBoard.h"
#include "grids.h"

typedef std::map<cord_t,cord_t> cordt_cordt;
typedef std::map<cord_t,ap_t> cordt_int;

class Range : public onBoard
{
private:
    cordt_cordt _trace_map;
    int _range;
    void getRangeAll(Grid* board){
        std::queue<std::pair<cord_t, int>> q;
        cordt_cordt r;
        cordt_int seen; 

        cord_t cur = get_cord();
        int ap = 0;
        q.push(make_pair<cord_t, int>(cur, ap));
        seen[cur] = ap;
        while (!q.empty())
        {   
            cur = q.front().first; //update current tile
            ap = q.front().second; //update actionPoint already spent upto current tile
            seen[cur] = ap; //set the total ActionPoint spent 

            for(auto x : board->get_neighbors(cur)){ 
                //check each nighbor
                if( board->is_passable(x) &&  ( seen.find(x) == seen.end() || seen[q.front().first] < ap ) ){ 
                    //if it is a passable tile AND
                        //if never been here || been here but this time cost less ap
                    q.push( make_pair<cord_t, int>( x, ap + board->get_mCost(x) ) ); 
                        //step into this tile (push ( coordinate, remaining ap ) )
                    r[x] = cur;
                    if(ap < _range) 
                        _trace_map[x] = cur; 
                    //and set the tile's parent (the tile before step into it) to current tile
                }
            }   
            

            q.pop();
        }

        trace_map = r;
        trace_ap = seen;
    }
    
public:
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
        //draw the tile 
        int& dx = onBoard::DX, &dy = onBoard::DY;
        sf::RectangleShape s;
        s.setSize(sf::Vector2f(dx, dy));
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

    //Set the starting point of the Range
    inline void setPosition(cord_t center);

    //Calculate the map, and update the global map object
    void updateMap(Grid* board){
        getRangeAll(board);
    }
};


    
    /*****************************************************
     * MUTATOR 
     */
    //Set the action point(range)
    void Range::setRange(int range){
        _range = range;
    }
    
    //Set the starting point of the Range
    void Range::setPosition(cord_t center){ set_cord(center); }


    bool Range::within_range(cord_t tile){
        return _trace_map.find(tile) != _trace_map.end();
    }

