#pragma once

#include "type_def.h"
#include "range.h"

class Path : public Range
{
private:
    cord_t _end = cord_t(-1,-1);
    void getRangeAll() {
    std::queue<std::pair<cord_t, int>> q;
    mCordt_cordt r;
    mCordt_int seen; 

    cord_t cur = get_cord();
    int ap = 0;
    q.push(std::pair<cord_t, int>(cur, ap));
    seen[cur] = ap;

    while (!q.empty())
    {   
        cur = q.front().first; //update current tile
        ap = q.front().second; //update actionPoint already spent upto current tile

        seen[cur] = ap; //set the total ActionPoint spent 
        for(auto x : _board->get_neighbors(cur)){ 
            //check each nighbor
            if( _board->is_passable(x) &&  ( seen.find(x) == seen.end() || seen[q.front().first] < ap ) ){ 
                //if it is a passable tile AND
                    //if never been here || been here but this time cost less ap
                q.push( std::pair<cord_t, int>( x, (ap + _board->get_mCost(x)) ) ); 
                    //step into this tile (push ( coordinate, remaining ap ) )
                r[x] = cur;
                //and set the tile's parent (the tile before step into it) to current tile
            }
        }   
        

        q.pop();
    }

    _trace_map = r;
    _trace_ap = seen;
    for(auto x : _trace_ap){
        _ap_cordv[x.second].push_back(x.first);
    }
}
public:

    Path(cord_t where = cord_t(), int range = 0) : Range(where,range){}
    
    /*****************************************************
     * VIRTUAL 
     */
    
    virtual void draw(sf::RenderWindow& window) override{
        Range::draw(window);
        assert(_end.first != -1 && _end.second != -1 && "Path does not have an end point");

        cord_t last = getEnd(), start = getStart();
        //dest cannot be reached
        if(Range::_trace_map.find(last) == Range::_trace_map.end()) return;

        //Tile
        sf::RectangleShape s;
        int& dx = onBoard::DX, &dy = onBoard::DY;
        s.setSize(sf::Vector2f(dx, dy));

        while (last != start)
        {
            //Draw each tile until reaching _start_tile
            s.setPosition( sf::Vector2f (dx * last.first, dy * last.second) );

            if(within_range(last)){
                //in Range
                s.setFillColor(PATH_GREEN);
            }
            else
            {  
                //Outof Range
                s.setFillColor(PATH_YELLOW);
            }
            window.draw(s); //Draw

            //Step backward 1 tile
            last = Range::_trace_map[last];
            
        }

    }
    /*****************************************************
     * GETTER
     */
    cord_t getStart(){ return get_cord(); }
    cord_t getEnd(){ return _end;}
    /*****************************************************
     * MUTATOR 
     */

    void setEnd(cord_t end) { _end = end; }
    void setStart(cord_t start) { set_cord(start); }
    void updateMap(Grid* board = nullptr) override{
        if(board)
            setBoard(board);
        clear();
        getRangeAll();
    }
};




