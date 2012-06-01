#ifndef GREATER_H
#define GREATER_H

#include "less.h"

template <class T> class Greater {

public :

    bool operator ()(const T &left, const T &right){
        Less<T> less;
        // nicht kleiner && nicht gleich
        bool lesser = less(left, right);
        bool equal = !less(left, right) && !less(right,left);

        return !lesser && !equal;
    }

};


#endif // GREATER_H
