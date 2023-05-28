#ifndef PAIR_HELPER_CPP
#define PAIR_HELPER_CPP

#include "pair_helper.h"

template<class T1, class T2>
std::pair<T1,T2> make_pair(T1 o1, T2 o2){
    return std::pair<T1,T2>(o1, o2);
}

#endif