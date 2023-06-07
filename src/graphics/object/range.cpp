#include "range.h"


void Range::getRangeAll(){
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

        //with in range
        if(ap < _range){
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
        }
        

        q.pop();
    }

    _trace_map = r;
    _trace_ap = seen;

}
