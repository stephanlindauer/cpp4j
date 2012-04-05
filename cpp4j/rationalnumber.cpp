#include "rationalnumber.h"
#include <stdio.h>
#include <stdlib.h>

bool rnIsValid (const RationalNumber n) {
    return n.denominator != 0;
}

bool rnIsNaN (const RationalNumber n) {
    return !rnIsValid(n);
}

int greatestCommonDivisor (int a, int b){
    if (b==0){
        return a;
    }
    else {
        return greatestCommonDivisor(b, a%b);
    }
}

RationalNumber inverse(const RationalNumber number){
    RationalNumber result = {
        number.denominator , number.nominator
    };
    return result;
}


RationalNumber normalize(const RationalNumber number){
    int gcdNumber = greatestCommonDivisor(abs(number.nominator), abs(number.denominator));
    RationalNumber normalizedNumber = {
        number.nominator / gcdNumber, number.denominator / gcdNumber
    };
    return normalizedNumber;
}

RationalNumber expand(const RationalNumber number, const int factor){

    RationalNumber normalizedNumber = {
        number.nominator * factor, number.denominator * factor
    };
    return normalizedNumber;
}

bool rnEqual (const RationalNumber number, const RationalNumber otherNumber){
    RationalNumber normalizedRationalNumber = normalize(number);
    RationalNumber normalizedOtherRationalNumber = normalize(otherNumber);
    return (normalizedRationalNumber.nominator == normalizedOtherRationalNumber.nominator)
            && (normalizedRationalNumber.denominator == normalizedOtherRationalNumber.denominator);
}

bool rnLessThan (const RationalNumber number, const RationalNumber otherNumber) {
    RationalNumber normalizedRationalNumber = normalize(number);
    RationalNumber normalizedOtherRationalNumber = normalize(otherNumber);
    if (normalizedRationalNumber.denominator == normalizedOtherRationalNumber.denominator){
        return normalizedRationalNumber.nominator < normalizedOtherRationalNumber.nominator;
    }
    normalizedRationalNumber = expand(normalizedRationalNumber, normalizedOtherRationalNumber.denominator);
    normalizedOtherRationalNumber = expand(normalizedOtherRationalNumber, normalizedRationalNumber.denominator);
    return normalizedRationalNumber.nominator < normalizedOtherRationalNumber.nominator;
}

RationalNumber rnAdd (const RationalNumber number, const RationalNumber otherNumber){
    RationalNumber expandedNumber = expand(number, otherNumber.denominator);
    RationalNumber expandedOtherNumber =expand(otherNumber, number.denominator);
    RationalNumber result = {
        expandedNumber.nominator + expandedOtherNumber.nominator,
        expandedNumber.denominator
    };
    return result;
}

RationalNumber rnSubtract (const RationalNumber number, const RationalNumber otherNumber){
    RationalNumber expandedNumber = expand(number, otherNumber.denominator);
    RationalNumber expandedOtherNumber =expand(otherNumber, number.denominator);
    RationalNumber result = {
        expandedNumber.nominator - expandedOtherNumber.nominator,
        expandedNumber.denominator
    };
    return result;
}

RationalNumber rnMultiply (const RationalNumber number, const RationalNumber otherNumber) {
    RationalNumber result = {
        number.nominator * otherNumber.nominator,
        number.denominator *otherNumber.denominator
    };
    return result;
}

RationalNumber rnDivide (const RationalNumber number, const RationalNumber otherNumber) {
    RationalNumber inversedOtherNumber = inverse(otherNumber);
    RationalNumber result = rnMultiply(number, inversedOtherNumber );
    return result;
}
