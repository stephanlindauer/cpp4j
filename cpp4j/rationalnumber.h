/**
  * Stephan Lindauer (s761720)
  * Kai Nessig (s764304)
  */

#ifndef RATIONALNUMBER_H
#define RATIONALNUMBER_H

#include <stdio.h>

struct RationalNumber {
    int nominator;
    int denominator;
};

// return true if the denominator of the parameter is different from zero
bool rnIsValid (const RationalNumber n);

// return true if the denominator of the parameter is equal to zero
bool rnIsNaN (const RationalNumber n);

// return true if both numbers designate the same value, but always
// returns false, if either argument is NaN
bool rnEqual
(const RationalNumber left,
 const RationalNumber right);

// return true if the value designated by the first parameter is less than the
// value designated by the second one, but always returns false, if either
// argument is NaN
bool rnLessThan
(const RationalNumber left,
 const RationalNumber right);

// calculate the sum of both parameters; if the left argument is NaN the right
// argument is returned; if the right argument is NaN, the left argument is returned
RationalNumber rnAdd
(const RationalNumber left,
 const RationalNumber right);

// calculate the difference of both parameters
// the calculation is performed by adding the negated value of the second
// parameter; if the left argument is NaN the right argument is returned;
// if the right argument is NaN, the left argument is returned
RationalNumber rnSubtract
(const RationalNumber left,
 const RationalNumber right);

// calculate the product of both parameters
RationalNumber rnMultiply
(const RationalNumber left,
 const RationalNumber right);

// calculate the quotient of both parameters
// the calculation is performed by multiplying with the inverse of the second
// parameter
RationalNumber rnDivide
(const RationalNumber left,
 const RationalNumber right);
namespace rnum {
class CPP_RationalNumber {
public :

    CPP_RationalNumber
    ()
    {
        rn.nominator = 0;
        rn.denominator = 1;
    }

    CPP_RationalNumber
    (int nom)
    {
        rn.nominator = nom;
        rn.denominator = 1;
    }

    explicit CPP_RationalNumber
    (int nom, int denom)
    {
        rn.nominator = nom;
        rn.denominator = denom;
    }

    bool isValid (void) const;

    bool isNaN (void) const;

    bool operator==
    (const CPP_RationalNumber &right) const;

    bool operator<
    (const CPP_RationalNumber &right) const;

    const CPP_RationalNumber operator+
    (const CPP_RationalNumber &right) const;

    const CPP_RationalNumber operator-
    (const CPP_RationalNumber &right) const;

    const CPP_RationalNumber operator-
    () const;

    const CPP_RationalNumber operator*
    (const CPP_RationalNumber &right) const;

    CPP_RationalNumber & operator*=
    (const CPP_RationalNumber &right);

    const CPP_RationalNumber operator/
    (const CPP_RationalNumber &right) const;

    int toInt(void){
        return rn.nominator / rn.denominator;
    }

    double toDouble(void){
        return ((double) rn.nominator) / ((double) rn.denominator);
    }

    void toString(void){
        printf("%d %d \n" , rn.nominator, rn.denominator);
    }


private:
    RationalNumber rn;
};

/*CPP_RationalNumber operator*(const int left, const CPP_RationalNumber &right){
    return CPP_RationalNumber(left) * right;
}

CPP_RationalNumber operator/(const CPP_RationalNumber &left, const int right){
    return left / CPP_RationalNumber(right);
}*/

}
#endif // RATIONALNUMBER_H

