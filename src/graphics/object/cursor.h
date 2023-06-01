#pragma once

#include "type_def.h"
#include "onBoard.h"

class Cursor : public onBoard
{
private:
    /* data */
public:
    Cursor(cord_t where):onBoard(where){}

    /*****************************************************
     * VIRTUAL 
     */
    
    virtual void draw(sf::RenderWindow& window) override{

    }
    /*****************************************************
     * MUTATOR 
     */
    void move(cord_t where){
        set_cord(where);
    }
};


