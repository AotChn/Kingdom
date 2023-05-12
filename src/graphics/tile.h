#ifndef TILE_H
#define TILE_H

struct tile{
    
    tile() : x(0), y(0){};
    tile(int i, int j){
        x = i, y = j;
    }

    void set_coord(int i,int j) {x = i; y = j;}
    
    int x;
    int y;

};



#endif 
