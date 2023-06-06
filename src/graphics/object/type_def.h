#pragma once

#include <assert.h>
#include <utility>
#include <Map>
#include <vector>
#include <Queue>
#include <SFML/Graphics.hpp>

#include "../color_constants.h"

typedef std::map<cord_t,cord_t> mCordt_cordt;
typedef std::map<cord_t,ap_t> mCordt_int;
typedef std::vector<cord_t> vCordt;
typedef std::pair<int,int> cord_t;  

typedef int ap_t;
typedef int mCost_t;