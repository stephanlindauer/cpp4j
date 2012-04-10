#ifndef RATIONALNUMBERARRAY_H
#define RATIONALNUMBERARRAY_H

#include "rationalnumber.h"

struct RationalNumberArray;

RationalNumberArray* rnaCreate(const unsigned int size);

void rnaDelete(RationalNumberArray* rna);

RationalNumberArray* rnaResize(const unsigned int newSize);

int rnaSize(RationalNumberArray* rna);

int rnaCapacity(RationalNumberArray* rna);

RationalNumberArray* rnaAdd(RationalNumber newRationalNumber );

RationalNumberArray* rnaSet(RationalNumber rationalNumber, const unsigned int position );

RationalNumberArray* rnaGet(const unsigned int position );

RationalNumberArray* rnaRemove(const unsigned int position );






#endif // RATIONALNUMBERARRAY_H
