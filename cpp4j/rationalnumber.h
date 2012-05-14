/**
  * Stephan Lindauer (s761720)
  * Kai Nessig (s764304)
  */

#ifndef RATIONALNUMBER_H
#define RATIONALNUMBER_H

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
    (int nom, int denom): rn(nom,denom)
    {
    }

    CPP_RationalNumber
    (int nom): rn(nom,1)
    {
    }

    CPP_RationalNumber& operator= (const int &right)
    {
        this->rn.nominator = right;
        this->rn.denominator = 1;
        return *this;
    }

    bool rnIsValid (void);

    bool rnIsNaN (void);

    bool operator==
    (const CPP_RationalNumber &right);

    bool operator<
    (const CPP_RationalNumber &right);

    void operator+
    (const CPP_RationalNumber &right);

    void operator-
    (const CPP_RationalNumber &right);

    void operator*
    (const CPP_RationalNumber &right);

    void operator/
    (const CPP_RationalNumber &right);

private:
    RationalNumber rn;
};
}
#endif // RATIONALNUMBER_H
