#ifndef LESS_H
#define LESS_H


template <class T> class Less {

public :

    bool operator ()(const T &left, const T &right){
        return left < right;
    }

};


#endif // LESS_H
