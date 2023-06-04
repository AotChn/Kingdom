#pragma once


#include "type_def.h"
#include "onBoard.h"


class Terrain : public onBoard
{
private:
    int _mCost;
public:
    Terrain(cord_t where) : onBoard(where){}
    /*****************************************************
     * VIRTUAL 
     */
    
    virtual void draw(sf::RenderWindow& window) override{
        
    }
    /*****************************************************
     * GETTER
     */
    virtual int get_mCost(){return 0;}

    /*****************************************************
     * MUTATOR 
     */
};
