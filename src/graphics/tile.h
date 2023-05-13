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

    bool equal(tile& lhs, tile& rhs){
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    // bool operator==(const tile& lhs, const tile& rhs){
    //     return lhs.x == rhs.x && lhs.y == rhs.y;
    // }
};



#endif 
