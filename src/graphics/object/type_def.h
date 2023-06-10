#pragma once

#include <assert.h>
#include <utility>
#include <map>
#include <vector>
#include <queue>
#include <SFML/Graphics.hpp>

#include "../color_constants.h"

typedef std::pair<int,int> cord_t;  
typedef int ap_t;

typedef std::map<cord_t,cord_t> mCordt_cordt;
typedef std::map<cord_t,ap_t> mCordt_int;
typedef std::vector<cord_t> vCordt;

typedef int mCost_t;