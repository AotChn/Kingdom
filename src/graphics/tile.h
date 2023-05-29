#ifndef TILE_H
#define TILE_H

struct tile{
    
    tile() : x(0), y(0){};
    tile(int i, int j) : x(i), y(j){}

    void set_coord(int i,int j) {x = i; y = j;}
    
    int x;
    int y;

    tile& operator=(const tile& rhs){
        x = rhs.x;
        y = rhs.y;
        return *this;
    }
    tile(const tile& copy){
        x = copy.x; 
        y = copy.y;
    }

    friend bool operator==(const tile& lhs, const tile& rhs){
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    friend bool operator!=(const tile& lhs, const tile& rhs){
        return lhs.x != rhs.x || lhs.y != rhs.y;
    }

    int find_distance(tile a, tile b){
        int i = abs(a.x - b.x);
        int j = abs(a.y - b.y);
        return i+j;
    }
};



#endif 
