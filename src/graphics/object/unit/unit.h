#pragma once

#include "../type_def.h"
#include "../onBoard.h"

class Unit : public onBoard{
protected:
    typedef int cost_t;
    typedef int ap_t;
    cost_t _mCost;      //Movement cost added to passing unit
public:
    Unit();
    Unit(cord_t cord, cost_t mCost);

    /*****************************************************
     * DRAW
     */
    
    virtual void draw(sf::RenderWindow& window);
    
    /*****************************************************
     * MUTATOR
     */
    
    inline Unit& moveTo(cord_t newCord);
    
    /*****************************************************
     * GETTER
     */  
    
    inline cost_t get_mCost();

    inline virtual bool isPC();
        //is Player Character?

    virtual sf::RectangleShape unit(sf::Color c);
        //return the drawable shape of the Unit

};


/*****************************************************
 * VIRTUAL 
 */

    inline bool Unit::isPC(){return false;}
        //is Player Character?

/*****************************************************
 * MUTATOR
 */

    inline Unit& Unit::moveTo(cord_t newCord){
        set_cord(newCord);
        return *this;
    }

/*****************************************************
 * GETTER
 */
    inline Unit::cost_t Unit::get_mCost(){
        return _mCost;
    }
