#ifndef RATIONALNUMBERARRAY_H
#define RATIONALNUMBERARRAY_H

#include "rationalnumber.h"

const RationalNumber NULL_RATIONAL_NUMBER = { 0, 1 };

struct RationalNumberArray;

typedef void (*rnaErrorCallback_t)(RationalNumberArray * rna);

enum RNAErrorCode {
    rnaNoError,
    rnaInvalidArray,
    rnaInvalidIndex,
    rnaAllocFailed
};

// allocate a new array with the given size
RationalNumberArray * rnaCreate(const unsigned int size = 10);

// free all memory created by rnaCreate
RationalNumberArray * rnaDelete(RationalNumberArray * rna);

// resize the array to the new size
// both size and capacity are changed by this operation
void rnaResize(RationalNumberArray * rna, const unsigned int newSize);

// retrieve the size of this array, i. e. the used elements; also returns 0 if the array isn't initialized
unsigned int rnaSize(const RationalNumberArray * rna);

// retrieve the capacity of this array; also returns 0 if the array isn't initialized
unsigned int rnaCapacity(const RationalNumberArray * rna);

// add a new element to the array; the array must already be initialized, otherwise it quietly returns
void rnaAdd(RationalNumberArray * rna, const RationalNumber newRationalNumber);

// replace an element in the array; the array must already be initialized, otherwise it quietly returns
// if the position is outside of the current size of the array, the array is resized and all elements between
// the last used element and the newly inserted elements are initialized to the NULL_RATIONAL_NUMBER
void rnaSet(RationalNumberArray * rna, const unsigned int position, const RationalNumber rationalNumber);

// retrieve the element at position; the array must already be initialized otherwise NULL_RATIONAL_NUMBER is
// returned. if the position is outside of the used elements, an error is set (and callback called if
// available) and NULL_RATIONAL_NUMBER is returned
RationalNumber rnaGet(RationalNumberArray * rna, const unsigned int position);

// remove all elements between (inclusive) from and to. elements following to are shifted to the left,
// so the element matching the index to + 1 then has the index from; the array must already be initialized
// otherwise it quietly returns; if the value stored in from is greater than the value stored in to, an error
// is set (and callback called if available).
void rnaRemove(RationalNumberArray * rna, const unsigned int from, const unsigned int to);

// retrieve the error code stored in the array; the array must already be initialized, otherwise it returns
// rnaInvalidArray.
RNAErrorCode rnaError(const RationalNumberArray * rna);

// set an error callback which gets called when ever an error is set (i. e. a value different from rnaNoError)
// the array must already be initialized, otherwise it calls the callback with NULL as argument, but only if
// callback does not equal NULL
void rnaSetErrorCallback (RationalNumberArray * rna, rnaErrorCallback_t callback);


namespace rnum{

const CPP_RationalNumber NULL_RATIONAL_NUMBER ( 0, 1 );

class CPP_RationalNumberArray;

typedef void (*cppErrorCallback_t)(CPP_RationalNumberArray &rna);

class CPP_RationalNumberArray {

public :

    CPP_RationalNumberArray (const unsigned int size = 10);
    CPP_RationalNumberArray (const CPP_RationalNumberArray &rhs);

    ~CPP_RationalNumberArray (void);

    void resize(const unsigned int newSize);

    unsigned int size(void);

    unsigned int capacity(void);

    void add(const CPP_RationalNumber newRationalNumber);

    void set(const unsigned int position, const CPP_RationalNumber rationalNumber);

    const CPP_RationalNumber get(const unsigned int position);

    void remove(const unsigned int from, const unsigned int to);

    RNAErrorCode rnaError(void) const;
    void rnaSetErrorCallback (const cppErrorCallback_t callback);

    CPP_RationalNumberArray& operator=
    (const CPP_RationalNumberArray &right);

    const CPP_RationalNumber& operator[]
    (const unsigned int &index) const;

    CPP_RationalNumber& operator[]
    (const unsigned int &index) ;



private:

    void setError(const RNAErrorCode errorCode);

    CPP_RationalNumber * m_data;

    unsigned int m_size;

    unsigned int m_capacity;

    RNAErrorCode m_error;

    cppErrorCallback_t m_errorCallback;

    void copy(const CPP_RationalNumberArray &from);

    bool operator==
    (const RationalNumberArray & rna) const{
        return false;
    }
};
}

#endif // RATIONALNUMBERARRAY_H
