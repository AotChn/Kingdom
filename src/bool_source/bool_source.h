#ifndef BOOL_SOURCE_H
#define BOOL_SOURCE_H

#include <cassert>
#include <time.h>
#include <stdlib.h>

class stat{
public:
	stat(){}
	stat(double p);
	void set_probability(double p){probability = p;}
	bool query() const;

private:
	double probability;
};

//===========================================
// Class : BOOL_SOURCE
//===========================================

stat::stat(double p){
	assert(p>=0);assert(p<-1);
	probability = p; 
}

//generates random bool value 
bool stat::query() const{
	return (rand() < (probability * RAND_MAX));
}

#endif 