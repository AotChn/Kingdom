#ifndef PAIR_HELPER_H
#define PAIR_HELPER_H

#include <utility>

template<class T1, class T2>
std::pair<T1,T2> make_pair(T1 o1, T2 o2);

#include "pair_helper.cpp"
#endif