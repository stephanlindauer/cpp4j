#ifndef RATIONALNUMBERARRAY_H
#define RATIONALNUMBERARRAY_H

#include "rationalnumber.h"

struct RationalNumberArray;

typedef void (*rnaErrorCallback_t)(RationalNumberArray * rna);

enum RNAErrorCode {
    rnaNoError,
    rnaInvalidArray,
    rnaInvalidIndex,
    rnaAllocFailed
};

RationalNumberArray * rnaCreate(const unsigned int size);

RationalNumberArray * rnaDelete(RationalNumberArray * rna);

void rnaResize(RationalNumberArray * rna, const unsigned int newSize);

unsigned int rnaSize(const RationalNumberArray * rna);

unsigned int rnaCapacity(const RationalNumberArray * rna);

void rnaAdd(RationalNumberArray * rna, const RationalNumber newRationalNumber);

void rnaSet(RationalNumberArray * rna, const RationalNumber rationalNumber, const unsigned int position);

RationalNumber rnaGet(RationalNumberArray * rna, const unsigned int position);

void rnaRemove( RationalNumberArray * rna, const unsigned int from, const unsigned int to);

RNAErrorCode rnaError(const RationalNumberArray * rna);

void rnaSetErrorCallback (RationalNumberArray * rna, rnaErrorCallback_t callback);

#endif // RATIONALNUMBERARRAY_H
