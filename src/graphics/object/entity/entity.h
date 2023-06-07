#pragma once


#include "../type_def.h"
#include "../onBoard.h"

class Entity : public onBoard{
protected:
    typedef int cost_t;
    typedef int ap_t;
    cost_t _mCost;      //Movement cost modifier
public:
    Entity(){}
    Entity(cord_t cord, cost_t mCost): _mCost(mCost){
        set_cord(cord);
    }

    cost_t get_mCost(){
        return _mCost;
    }
    void set_mCost(cost_t mCost){
        _mCost = mCost;
    }
};

