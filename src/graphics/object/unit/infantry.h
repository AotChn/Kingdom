#ifndef INFANTRY_H
#define INFANTRY_H

#include "unit.h"


class Infantry : public Unit
{
private:
public:
    static const ap_t InfantryAP;
    /*****************************************************
     * BIG3
     */  
    Infantry();
    Infantry(cord_t cord);
   
    /*****************************************************
     * GETTER / BOOL
     */  
    
    inline bool isPC() override;
    inline virtual ap_t getAp() override;
};


bool Infantry::isPC(){
    return true;
}

ap_t Infantry::getAp() {
    return InfantryAP;
}


#endif