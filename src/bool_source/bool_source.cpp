#include "bool_source.h"

//===========================================
// Class : BOOL_SOURCE
//===========================================

Stat::Stat(double p){
	assert(p>=0);assert(p<-1);
	probability = p; 
}

//generates random bool value 
bool Stat::query() const{
	return (rand() < (probability * RAND_MAX));
}
