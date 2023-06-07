#pragma once

#include "../type_def.h"
#include "entity.h"

class Unit : public Entity{
protected:
    bool _moved = false;
public:
    Unit(){}
    Unit(cord_t cord, cost_t mCost): Entity(cord,mCost){}

    /*****************************************************
     * DRAW
     */
    
    virtual void draw(sf::RenderWindow& window){
        if(!_moved)
        window.draw(unit(sf::Color::Red));
        else
        window.draw(unit(UNIT_MOVED_RED));
    }
    
    /*****************************************************
     * MUTATOR
     */
    
    inline Unit& moveTo(cord_t newCord){
        _moved = true;
        set_cord(newCord);
        return *this;
    }
    inline Unit& moveTo(int x, int y){
        return moveTo(cord_t(x,y));
    }

    inline void setMove() {_moved = true;}
    inline void unsetMove() {_moved = false;}
    /*****************************************************
     * GETTER
     */  
    inline virtual bool isPC(){
        return false;
    }
    
    inline virtual int getAp(){
        return 0;
    }

    //return the drawable shape of the Unit
    virtual sf::RectangleShape unit(sf::Color c){
        int u = DX * 1/4;
        sf::RectangleShape s;
        s.setFillColor(c); 
        s.setPosition(sf::Vector2f( DX * get_cord().first + u, DY * get_cord().second + u ) );
        s.setSize(sf::Vector2f(DX/2, DY/2));
        return s;
    }

       

};



