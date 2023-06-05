#pragma once

#include "type_def.h"
#include "range.h"

class Path : public Range
{
private:
    cord_t _end = cord_t(-1,-1);
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
        if(Range::trace_map.find(last) == Range::trace_map.end()) return;

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
            last = Range::trace_map[last];
            
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
};
