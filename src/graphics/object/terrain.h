#pragma once


#include "type_def.h"
#include "onBoard.h"


class Terrain : public onBoard
{
private:
    /* data */
public:
    Terrain(cord_t where) : onBoard(where){}
    /*****************************************************
     * VIRTUAL 
     */
    
    virtual void draw(sf::RenderWindow& window) override{
        
    }
    /*****************************************************
     * MUTATOR 
     */

};
