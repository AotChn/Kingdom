#ifndef BOOL_SOURCE_H
#define BOOL_SOURCE_H

#include <cassert>
#include <time.h>
#include <stdlib.h>

class Stat{
public:
	Stat(){}
	Stat(double p);
	void set_probability(double p){probability = p;}
	bool query() const;

private:
	double probability;
};

#endif 