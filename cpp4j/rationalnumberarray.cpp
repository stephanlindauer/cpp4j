#include "assert.h"
#include "stdlib.h"
#include "rationalnumberarray.h"

struct RationalNumberArray{
    RationalNumber * data;
    unsigned int size;
    unsigned int capacity;
    RNAErrorCode error;
    rnaErrorCallback_t errorCallback;
};

const RationalNumber NULL_RATIONAL_NUMBER = { 0, 1 };
const unsigned int INCREMENTATION = 100;

void initializeWithNullRationalNumber(const RationalNumberArray * rna, const unsigned int from, const unsigned int to) {
    for (unsigned int i = from; i < to; i++) {
        rna->data[i] = NULL_RATIONAL_NUMBER;
    }
}

size_t computeSizeForData(const unsigned int elements) {
    return (sizeof (RationalNumber) * elements);
}

void setError(RationalNumberArray * rna, const RNAErrorCode errorCode) {
    rna->error = errorCode;
    if (rna->error != rnaNoError && rna->errorCallback != NULL)
        rna->errorCallback (rna);
}

void rnaAdd(RationalNumberArray * rna, const RationalNumber newRationalNumber) {
    if (rna->size < rna->capacity) {
        rna->data[rna->size++] = newRationalNumber;
        setError(rna, rnaNoError);
        return;
    }

    // resize array and retry
    const unsigned int oldCapacity = rna->capacity;
    rnaResize(rna, oldCapacity + INCREMENTATION);
    assert (rna->capacity == oldCapacity + INCREMENTATION);
    rnaAdd(rna, newRationalNumber);
}

unsigned int rnaCapacity(const RationalNumberArray * rna) {
    return rna->capacity;
}

RationalNumberArray * rnaCreate(const unsigned int size) {
    RationalNumberArray * rna = (RationalNumberArray*) malloc (
                sizeof (RationalNumber *) +
                sizeof (int) +
                sizeof (int));

    rna->data = (RationalNumber*) malloc (computeSizeForData(size));


    initializeWithNullRationalNumber(rna, 0, size);

    rna->size = 0;
    rna->capacity = size;
    rna->errorCallback = NULL;

    if (rna->data == NULL)
        setError(rna, rnaAllocFailed);
    else
        setError(rna, rnaNoError);

    return rna;
}

RationalNumberArray * rnaDelete(RationalNumberArray * rna) {
    free(rna->data); rna->data = NULL;
    free(rna); rna = NULL;
    return rna;
}

RNAErrorCode rnaError(const RationalNumberArray * rna) {
    return rna->error;
}

RationalNumber rnaGet(RationalNumberArray * rna, const unsigned int position) {
    if (rna->data == NULL) {
        setError(rna, rnaInvalidArray);
        return NULL_RATIONAL_NUMBER;
    }

    if (position >= rna->size) {
        setError(rna, rnaInvalidIndex);
        return NULL_RATIONAL_NUMBER;
    }

    setError(rna, rnaNoError);
    return rna->data[position];

}

void rnaRemove( RationalNumberArray * rna, const unsigned int from, const unsigned int to) {
    if (to < from) {
        setError(rna, rnaInvalidIndex);
        return;
    }

    unsigned int offset = (to - from) + 1;

    for(unsigned int i = from; i < rna->capacity; i++){
        if (i+offset <= rna->size){
            rna->data[i] = rna->data[i+offset];
        }
    }

    rna->size = rna->size - offset;

    setError(rna, rnaNoError);
    initializeWithNullRationalNumber(rna, rna->size, rna->capacity);
}

void rnaResize(RationalNumberArray * rna, const unsigned int newSize) {
    if (rna->size == newSize)
        // nothing to do
        return;

    RationalNumber * newData = (RationalNumber*) realloc(rna->data, computeSizeForData(newSize));

    if (rna->size > newSize) {
        // size decreases, ptr returned by realloc should always be equal to the old ptr
        assert (rna->data == newData);
        rna->size = rna->capacity = newSize;
        setError(rna, rnaNoError);
        return;
    }

    // size increases
    RationalNumber * oldData = rna->data;

    if (oldData != newData) { // ptr changed
        rna->data = newData;

        for (unsigned int i = 0; i < rna->size; i++) {
            rna->data[i] = oldData[i];
        }
        free(oldData);
    }

    rna->capacity = newSize;
    setError(rna, rnaNoError);
    initializeWithNullRationalNumber(rna, rna->size, newSize);
}

void rnaSet(RationalNumberArray * rna, const RationalNumber rationalNumber, const unsigned int position) {
    if(position > rna->size){
        rnaResize(rna, position + 1);
    }

    rna->data[position] = rationalNumber;
    rna->size = position+1;
}

unsigned int rnaSize(const RationalNumberArray * rna) {
    return rna->size;
}

void rnaSetErrorCallback (RationalNumberArray * rna, rnaErrorCallback_t callback) {
    rna->errorCallback = callback;
}
