#pragma once 

#include "../type_def.h"

class Unit{
    typedef int cost_t;
public:
    Unit(){};
    Unit(cord_t cord, cost_t mCost): _cord(cord), _mCost(mCost){}
    
    virtual void draw(sf::RenderWindow& window){}
    
    void move(cord_t newCord){
        _cord = newCord;
    }
    cord_t get_cord(){
        return _cord;
    }
    cost_t get_mCost(){
        return _mCost;
    }
private:
    cord_t _cord;
    cost_t _mCost;
};