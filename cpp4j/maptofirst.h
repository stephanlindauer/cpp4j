#ifndef MAPTOFIRST_H
#define MAPTOFIRST_H

#include "pair.h"

//        int       string    less
template <class T1, class T2, class Order > class MapToFirst {

public:

                             //int,string
    bool operator ()(const Pair<T1,T2> &left, const Pair<T1,T2> &right){
        Order functor; // less<int>
        return functor(left.first(),right.first());
    }


};

#endif // MAPTOFIRST_H
