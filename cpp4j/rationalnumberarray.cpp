#include "stdlib.h"
#include "rationalnumberarray.h"


struct RationalNumberArray{
    RationalNumber *data;
    unsigned int size;
    unsigned int capacity;
};

const RationalNumber nullRationalNumber = { 0, 1 };


RationalNumberArray* rnaCreate(const unsigned int size) {
    RationalNumberArray * rna = (RationalNumberArray*) malloc (
                sizeof (RationalNumber *) +
                sizeof (int) +
                sizeof (int));

    rna->data = (RationalNumber*) malloc (sizeof (RationalNumber) * size);

    for (unsigned int i = 0; i < size; i++) {
        rna->data[i] = nullRationalNumber;
    };

    rna->size = 0;
    rna->capacity = size;

    return rna;
}

void rnaDelete(RationalNumberArray * rna) {
    return;
}

void rnaResize(const RationalNumberArray * rna, const unsigned int newSize) {

}

unsigned int rnaSize(const RationalNumberArray * rna) {
    return rna->size;
}

unsigned int rnaCapacity(const RationalNumberArray * rna) {
    return rna->capacity;
}

void rnaAdd(const RationalNumberArray * rna, const RationalNumber newRationalNumber) {
    return;
}

void rnaSet(const RationalNumberArray * rna, const RationalNumber rationalNumber, const unsigned int position) {
    if(position >= rna->size){
        rnaResize(rna, position);
    }
    rna->data[position] = rationalNumber;
}

RationalNumber rnaGet(const RationalNumberArray * rna, const unsigned int position) {
    return rna->data[position];
}

void rnaRemove( RationalNumberArray * rna, const unsigned int from, const unsigned int to) {
    unsigned int offset = to - from;

    for( unsigned int i = from; i <= rna->capacity; i++){
        if (i+offset <= rna->size){
            rna->data[i] = rna->data[i+offset];
        }
    }

    rna->size = rna->size - offset;

    for (unsigned j = rna->size; j <= rna->capacity; j++){
        rna->data[j] = nullRationalNumber;
    }
}
