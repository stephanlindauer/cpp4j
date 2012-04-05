#ifndef RATIONALNUMBER_H
#define RATIONALNUMBER_H

struct RationalNumber {
    int nominator;
    int denominator;
};

bool rnIsValid (const RationalNumber n) ;
bool rnIsNaN (const RationalNumber n) ;
bool rnEqual (const RationalNumber number, const RationalNumber otherNumber) ;
bool rnLessThan (const RationalNumber number, const RationalNumber otherNumber) ;
RationalNumber rnAdd (const RationalNumber number, const RationalNumber otherNumber) ;
RationalNumber rnSubtract (const RationalNumber number, const RationalNumber otherNumber) ;
RationalNumber rnMultiply (const RationalNumber number, const RationalNumber otherNumber) ;
RationalNumber rnDivide (const RationalNumber number, const RationalNumber otherNumber) ;

#endif // RATIONALNUMBER_H
