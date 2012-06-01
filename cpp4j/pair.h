#ifndef PAIR_H
#define PAIR_H

template <T1,T2> class Pair {

public :

    Pair ():
        m_first(),
        m_second()
    { }

    Pair (T1 firstParam, T2 secondParam):
        m_first(firstParam),
        m_second(secondParam)
    { }

    Pair (Pair otherPair):
        m_first(otherPair.first()),
        m_second(otherPair.second())
    { }

    Pair& operator=
    (const Pair &right){
        return Pair(right.first(), right.second());
    }

    ostream& operator << (ostream &os){
        os << first();
        os << second();
    }

    T1& first(void){
        return &m_first;
    }

    const T1& first(void) const {
        return &m_first;
    }

    T2& second(void){
        return &m_second;
    }

    const T2& second(void) const{
        return &m_second;
    }

private:

    T1 m_first ;
    T2 m_second;

}
#endif // PAIR_H
