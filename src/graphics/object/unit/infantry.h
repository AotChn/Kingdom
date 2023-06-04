#ifndef INFANTRY_H
#define INFANTRY_H

#include "unit.h"


class Infantry : public Unit
{
private:
    
public:

    /*****************************************************
     * BIG3
     */  
    Infantry();
    Infantry(cord_t cord, cost_t mCost);
   
    /*****************************************************
     * GETTER
     */  

    bool isPC();

    static const ap_t InfantryAP = 4;
};


#endif