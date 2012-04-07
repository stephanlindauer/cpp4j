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

// return true if both numbers designate the same value
bool rnEqual
(const RationalNumber left,
 const RationalNumber right);

// return true if the value designated by the first parameter is less than the
// value designated by the second one
bool rnLessThan
(const RationalNumber left,
 const RationalNumber right);

// calculate the sum of both parameters
RationalNumber rnAdd
(const RationalNumber left,
 const RationalNumber right);

// calculate the difference of both parameters
// the calculation is performed by adding the negated value of the second
// parameter
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

#endif // RATIONALNUMBER_H
