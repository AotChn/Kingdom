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
public:
    static cordt_cordt trace_map;
    static cordt_int trace_ap;

    /*****************************************************
     * BIG3
     */
    Range(cord_t where, int range = 0) : onBoard(where), _range(range){}
    
    /*****************************************************
     * VIRTUAL 
     */
    
    virtual void draw(sf::RenderWindow& window) = 0;

    /*****************************************************
     *  INFO
     */
    void get_Range(Grid* board){
        std::queue<std::pair<tile_t, int>> q;
        cordt_cordt r;
        cordt_int seen; 

        cord_t cur = get_cord();
        int ap = 0;
        q.push(make_pair<cord_t, int>(tile, ap));
        seen[cur] = ap;
        
        while (!q.empty())
        {   
            cur = q.front().first; //update current tile
            ap = q.front().second; //update actionPoint already spent upto current tile
            seen[cur] = ap; //set the total ActionPoint spent 

            if(ap < _range){ 
                //if used ap is smaller than ap can spend     
                for(auto x : board.get_neighbors(cur)){ 
                    //check each nighbor

                    if( board.is_passable(x) &&  ( seen.find(x) == seen.end() || seen[q.front().first] < ap ) ){ 
                        //if it is a passable tile AND
                            //if never been here || been here but this time cost less ap
                        q.push( make_pair<tile_t, int>( x, ap + board->get_mCost(x) ) ); 
                            //step into this tile (push ( coordinate, remaining ap ) )
                        r[x] = cur;
                        //and set the tile's parent (the tile before step into it) to current tile
                    }
                

                }   
            }

            q.pop();
        }

        trace_map = r;
        trace_ap = seen;
    }
    
    static getRangeAll(Grid* board){
        std::queue<std::pair<tile_t, int>> q;
        cordt_cordt r;
        cordt_int seen; 

        cord_t cur = get_cord();
        int ap = 0;
        q.push(make_pair<cord_t, int>(tile, ap));
        seen[cur] = ap;
        
        while (!q.empty())
        {   
            cur = q.front().first; //update current tile
            ap = q.front().second; //update actionPoint already spent upto current tile
            seen[cur] = ap; //set the total ActionPoint spent 

            for(auto x : board.get_neighbors(cur)){ 
                //check each nighbor
                if( board.is_passable(x) &&  ( seen.find(x) == seen.end() || seen[q.front().first] < ap ) ){ 
                    //if it is a passable tile AND
                        //if never been here || been here but this time cost less ap
                    q.push( make_pair<tile_t, int>( x, ap + board->get_mCost(x) ) ); 
                        //step into this tile (push ( coordinate, remaining ap ) )
                    r[x] = cur;
                    //and set the tile's parent (the tile before step into it) to current tile
                }
            }   
            

            q.pop();
        }

        trace_map = r;
        trace_ap = seen;
    }
    
    /*****************************************************
     * MUTATOR 
     */
    inline void setRange(int range);
    inline void bindMapGlobal();
        //bind the object's map to the Global map
    inline void bindMap(cordt_cordt map);
};


    
    /*****************************************************
     * MUTATOR 
     */
    void Range::setRange(int range){
        _range = range;
    }
    
    void Range::bindMapGlobal(){
         _trace_map = trace_map;}

    void Range::bindMap(cordt_cordt path){
         _trace_map = path; }