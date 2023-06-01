#pragma once 

#include "../type_def.h"
#include "../onBoard.h"

class Unit : public onBoard{
private:
    typedef int cost_t;
    typedef int ap_t;
    cost_t _mCost;      //Movement cost added to passing unit
    static ap_t ap;
public:
    Unit(){};
    Unit(cord_t cord, cost_t mCost): _mCost(mCost){
        set_cord(cord);
    }
    
    /*****************************************************
     * VIRTUAL 
     */
    virtual void draw(sf::RenderWindow& window){
        window.draw(unit(sf::Color::Red));
    }
    virtual sf::RectangleShape unit(sf::Color c);
    
    /*****************************************************
     * MUTATOR
     */
    inline Unit& move(cord_t newCord){
        set_cord(newCord);
        return *this;
    }
    
    /*****************************************************
     * GETTER
     */
    inline cost_t get_mCost(){
        return _mCost;
    }

};