#ifndef PAIR_H
#define PAIR_H

#include <stdio.h>

template <class T1, class T2> class Pair {

public :

    Pair  (): m_first(), m_second() { }

    Pair (T1 firstParam, T2 secondParam): m_first(firstParam), m_second(secondParam) { }

    Pair (const Pair <T1,T2>& otherPair): m_first(otherPair.first()), m_second(otherPair.second()) { }
    Pair (Pair <T1,T2>& otherPair): m_first(otherPair.first()), m_second(otherPair.second()) { }

    Pair& operator= (const Pair &right){
        m_first = right.first();
        m_second = right.second();
        return *this;
    }

    friend ostream& operator<< (ostream &os, const Pair<T1,T2>& pair){
        os << '<' << pair.first() << ',' << pair.second() << '>';
        return os;
    }

    T1& first(void){
        return m_first;
    }

    const T1& first(void) const {
        return m_first;
    }

    T2& second(void){
        return m_second;
    }

    const T2& second(void) const{
        return m_second;
    }

private:

    T1 m_first;
    T2 m_second;

};
#endif // PAIR_H
