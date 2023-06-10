#pragma once
#include "type_def.h"
#include "../../resources/texture_manager.h"

class onBoard{
public:
    static int DX; //the deviation of x
    static int DY; //the deviation of y
    onBoard(cord_t where = cord_t(0,0)) : _cord(where){}
    /*****************************************************
     * VIRTUAL 
     */
    virtual ~onBoard(){};
    virtual void draw(sf::RenderWindow&) {assert(false);};
    
    /*****************************************************
     * GETTER / MUTATOR 
     */
    void    set_cord(cord_t cord){ _cord = cord; }
    cord_t  get_cord() { return _cord; }
    int     get_x() { return _cord.first;}
    int     get_y() { return _cord.second;}


    resources::TM texture;

private:
    cord_t _cord; //coordinate where the object locate
    
};