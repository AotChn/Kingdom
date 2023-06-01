#pragma once 

#include "../type_def.h"
#include "../onBoard.h"

class Unit : public onBoard{
private:
    typedef int cost_t;
    cost_t _mCost;
public:
    Unit(){};
    Unit(cord_t cord, cost_t mCost): _mCost(mCost){
        this->_cord = cord;
    }
    
    virtual void draw(sf::RenderWindow& window){window.draw(unit(sf::Color::Red));}
    virtual sf::RectangleShape unit(sf::Color c);
    void move(cord_t newCord){
        _cord = newCord;
    }
    
    cord_t get_cord(){
        return _cord;
    }
    cost_t get_mCost(){
        return _mCost;
    }

};