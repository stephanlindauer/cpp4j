/**
  * Stephan Lindauer (s761720)
  * Kai Nessig (s764304)
  */

#include "rationalnumber.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

bool rnum::CPP_RationalNumber::isValid (void) const {
    return rnIsValid(this->rn);
}

bool rnum::CPP_RationalNumber::isNaN (void)const {
    return rnIsNaN(this->rn);
}

bool rnum::CPP_RationalNumber::operator==
(const rnum::CPP_RationalNumber &right) const {
    return rnEqual(this->rn,right.rn);
}

bool rnum::CPP_RationalNumber::operator<
(const rnum::CPP_RationalNumber &right) const {
    return rnLessThan(this->rn,right.rn);
}

const rnum::CPP_RationalNumber rnum::CPP_RationalNumber::operator+
(const rnum::CPP_RationalNumber &right) const {
    rnum::CPP_RationalNumber result = *this;
    result.rn = rnAdd(this->rn, right.rn);
    return result;
}

const rnum::CPP_RationalNumber rnum::CPP_RationalNumber::operator-
(const rnum::CPP_RationalNumber &right) const {
    rnum::CPP_RationalNumber result = *this;
    result.rn = rnSubtract(this->rn, right.rn);
    return result;
}

const rnum::CPP_RationalNumber rnum::CPP_RationalNumber::operator-
() const {
    rnum::CPP_RationalNumber result = *this;
    const RationalNumber kaiSucks = { -1,1};
    result.rn = rnMultiply( this->rn , kaiSucks  );
    return result;

}

const rnum::CPP_RationalNumber rnum::CPP_RationalNumber::operator*
(const rnum::CPP_RationalNumber &right) const{
    rnum::CPP_RationalNumber result = *this;
    result.rn = rnMultiply(this->rn, right.rn);
    return result;
}

rnum::CPP_RationalNumber& rnum::CPP_RationalNumber::operator*=
(const rnum::CPP_RationalNumber &right){
    this->rn = rnMultiply(this->rn, right.rn);
    return *this;
}

const rnum::CPP_RationalNumber rnum::CPP_RationalNumber::operator/
(const rnum::CPP_RationalNumber &right) const{
    rnum::CPP_RationalNumber result = *this;
    result.rn = rnDivide(this->rn, right.rn);
    return result;
}


// find the greatest common divisor of two signed integers
unsigned int greatestCommonDivisor (const unsigned int a, const unsigned int b){
    if (b==0)
        return a;
    else
        return greatestCommonDivisor(b, a%b);
}

// return the inverse of a rational number
RationalNumber inverse(const RationalNumber number){
    const RationalNumber result = {
        number.denominator , number.nominator
    };
    return result;
}

// expand a rational number by the given factor
RationalNumber expand(const RationalNumber number, const int factor){
    const RationalNumber result = {
        number.nominator * factor, number.denominator * factor
    };
    return result;
}

// normalize the sign of the rational number
RationalNumber normalizeSign(const RationalNumber number) {
    if (number.denominator < 0)
        return expand(number, -1);
    return number;
}

// return the normalized value of a rational number
RationalNumber normalize(const RationalNumber number) {
    const int gcdNumber = greatestCommonDivisor(abs(number.nominator), abs(number.denominator));
    const RationalNumber result = {
        number.nominator / gcdNumber, number.denominator / gcdNumber
    };

    return normalizeSign(result);
}

/*
 * implementation of visible/public functions
 */

bool rnIsValid (const RationalNumber n) {
    return n.denominator != 0;
}

bool rnIsNaN (const RationalNumber n) {
    return !rnIsValid(n);
}

bool rnEqual (const RationalNumber left, const RationalNumber right){
    if (rnIsNaN(left) || rnIsNaN(right))
        return false;

    const RationalNumber normalizedL = normalize(left);
    const RationalNumber normalizedR = normalize(right);
    return (normalizedL.nominator == normalizedR.nominator)
            && (normalizedL.denominator == normalizedR.denominator);
}

bool rnLessThan (const RationalNumber left, const RationalNumber right) {
    if (rnIsNaN(left) || rnIsNaN(right))
        return false;

    const RationalNumber normL = normalizeSign(expand(left, right.denominator));
    const RationalNumber normR = normalizeSign(expand(right, left.denominator));
    return normL.nominator < normR.nominator;
}

RationalNumber rnAdd (const RationalNumber left, const RationalNumber right){
    if (rnIsNaN(left))
        return right;

    if (rnIsNaN(right))
        return left;

    const RationalNumber expandedL = expand(left, right.denominator);
    const RationalNumber expandedR = expand(right, left.denominator);

    // both numbers should have the same denominator now
    assert (expandedL.denominator == expandedR.denominator);

    const RationalNumber result = {
        expandedL.nominator + expandedR.nominator,
        expandedL.denominator
    };
    return normalize(result);
}

RationalNumber rnSubtract (const RationalNumber left, const RationalNumber right){
    if (rnIsNaN(left))
        return right;

    if (rnIsNaN(right))
        return left;

    const RationalNumber negativeR = {
        right.nominator * -1, right.denominator
    };
    return rnAdd(left, negativeR);
}

RationalNumber rnMultiply (const RationalNumber left, const RationalNumber right) {
    const RationalNumber result = {
        left.nominator * right.nominator,
        left.denominator * right.denominator
    };
    return normalize(result);
}

RationalNumber rnDivide (const RationalNumber left, const RationalNumber right) {
    const RationalNumber inversedR = inverse(right);
    return rnMultiply(left, inversedR);
}
