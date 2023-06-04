
#include "infantry.h"


const ap_t Infantry::InfantryAP;


/*****************************************************
 * BIG3
 */  
Infantry::Infantry(){};
Infantry::Infantry(cord_t cord, cost_t mCost): Unit(cord, mCost){}


/*****************************************************
 * GETTER
 */  

bool Infantry::isPC(){ return true; }
