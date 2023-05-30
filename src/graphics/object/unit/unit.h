#pragma once 

#include "../type_def.h"

class Unit{
public:
    Unit();
    
    void draw();
private:
    typedef int cost_t;
    cord_t _c;
    cost_t _mCost;
};