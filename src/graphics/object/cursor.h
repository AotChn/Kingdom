#pragma once

#include "type_def.h"
#include "onBoard.h"

class Cursor : public onBoard
{
private:
public:
    Cursor(cord_t where = cord_t()):onBoard(where){  }

    /*****************************************************
     * VIRTUAL 
     */
    
    virtual void draw(sf::RenderWindow& window) override{
        onBoard::draw(window);
    }
    /*****************************************************
     * MUTATOR 
     */
    void moveTo(cord_t where){
        set_cord(where);
    }

    /*****************************************************
     * Getter
     */
    cord_t getPosition(){return get_cord();}
    //return the position of cursor
};


