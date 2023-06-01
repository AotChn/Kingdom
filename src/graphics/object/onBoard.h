#pragma once
#include "type_def.h"

class onBoard{
public:
    static int DX;
    static int DY;
    virtual ~onBoard(){};
    virtual void draw(sf::RenderWindow&) = 0;
    
protected:
    cord_t _cord;
};