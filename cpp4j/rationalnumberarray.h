#ifndef RATIONALNUMBERARRAY_H
#define RATIONALNUMBERARRAY_H

#include "rationalnumber.h"

struct RationalNumberArray;

RationalNumberArray* rnaCreate(const unsigned int size);

void rnaDelete(RationalNumberArray * rna);

void rnaResize(const RationalNumberArray * rna, const unsigned int newSize);

unsigned int rnaSize(const RationalNumberArray * rna);

unsigned int rnaCapacity(const RationalNumberArray * rna);

void rnaAdd(const RationalNumberArray * rna, const RationalNumber newRationalNumber);

void rnaSet(const RationalNumberArray * rna, const RationalNumber rationalNumber, const unsigned int position);

RationalNumber rnaGet(const RationalNumberArray * rna, const unsigned int position);

void rnaRemove( RationalNumberArray * rna, const unsigned int from, const unsigned int to);



#endif // RATIONALNUMBERARRAY_H
