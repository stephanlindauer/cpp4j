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
    if (rna == NULL)
        return;

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
    if (rna == NULL)
        return 0;

    return rna->capacity;
}

RationalNumberArray * rnaCreate(const unsigned int size) {
    RationalNumberArray * rna = (RationalNumberArray*) malloc (
                sizeof (RationalNumber *) +
                sizeof (int) +
                sizeof (int) +
                sizeof (RNAErrorCode) +
                sizeof (rnaErrorCallback_t));

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
    if (rna == NULL)
        return NULL;

    if (rna->data != NULL) {
        // free the array
        free(rna->data);
        rna->data = NULL;
    }

    // free the struct
    free(rna);
    rna = NULL;

    return rna;
}

RNAErrorCode rnaError(const RationalNumberArray * rna) {
    if (rna == NULL)
        return rnaInvalidArray;

    return rna->error;
}

RationalNumber rnaGet(RationalNumberArray * rna, const unsigned int position) {
    if (rna == NULL) {
        return NULL_RATIONAL_NUMBER;
    }

    if (rna->data == NULL) {
        return NULL_RATIONAL_NUMBER;
    }

    if (position >= rna->size) {
        setError(rna, rnaInvalidIndex);
        return NULL_RATIONAL_NUMBER;
    }

    setError(rna, rnaNoError);
    return rna->data[position];

}

void rnaRemove(RationalNumberArray * rna, const unsigned int from, const unsigned int to) {
    if (rna == NULL)
        return;

    if (to < from) {
        setError(rna, rnaInvalidIndex);
        return;
    }

    unsigned int offset = (to - from) + 1;

    // overwrite (from .. to) with subsequent elements;
    for(unsigned int i = from; i < rna->capacity; i++)
        if (i+offset <= rna->size)
            rna->data[i] = rna->data[i+offset];
        else
            break;

    // calculate new size
    rna->size = (rna->size > offset) ? rna->size - offset : 0;

    setError(rna, rnaNoError);
    initializeWithNullRationalNumber(rna, rna->size, rna->capacity);
}

void rnaResize(RationalNumberArray * rna, const unsigned int newSize) {
    if (rna->size == newSize) // nothing to do
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

        for (unsigned int i = 0; i < rna->size; i++)
            rna->data[i] = oldData[i];

        free(oldData);
    }

    rna->capacity = newSize;
    setError(rna, rnaNoError);
    initializeWithNullRationalNumber(rna, rna->size, newSize);
}

void rnaSet(RationalNumberArray * rna, const unsigned int position, const RationalNumber rationalNumber) {
    if (rna == NULL)
        return;

    if(position > rna->size)
        rnaResize(rna, position + 1);


    rna->data[position] = rationalNumber;
    rna->size = position+1;
}

unsigned int rnaSize(const RationalNumberArray * rna) {
    if (rna == NULL)
        return 0;

    return rna->size;
}

void rnaSetErrorCallback (RationalNumberArray * rna, rnaErrorCallback_t callback) {
    if (rna == NULL) {
        if (callback != NULL)
            callback (NULL);
        return;
    }

    rna->errorCallback = callback;
}

rnum::CPP_RationalNumberArray::CPP_RationalNumberArray (const unsigned int size) {
    this->m_data = new CPP_RationalNumber[size];

    this->m_size = 0;
    this->m_capacity = size;
    this->m_errorCallback = NULL;

    if (this->m_data == NULL)
        setError(rnaAllocFailed);
    else
        setError(rnaNoError);

}

rnum::CPP_RationalNumberArray::~CPP_RationalNumberArray (void) {
    if (this->m_data != NULL) {
        // free the array
        delete(this->m_data);
        this->m_data = NULL;
    }
}

void rnum::CPP_RationalNumberArray::resize(const unsigned int newSize) {
    if (this->m_size == newSize) // nothing to do
        return;

    CPP_RationalNumber * newData = new CPP_RationalNumber[newSize];

    if (this->m_size > newSize) // truncate
    {
        for (unsigned int i = 0; i < newSize; i++) {
            newData[i] = this->m_data[i];
        }
    }
    else // append
    {
        for (unsigned int i = 0; i < this->m_size; i++) {
            newData[i] = this->m_data[i];
        }
    }

    // don't leak
    delete(this->m_data);

    this->m_data = newData;
    this->m_capacity = newSize;
    setError(rnaNoError);
}

unsigned int rnum::CPP_RationalNumberArray::size(void) {
    return this->m_size;
}

unsigned int rnum::CPP_RationalNumberArray::capacity(void) {
    return this->m_capacity;
}

void rnum::CPP_RationalNumberArray::add(const rnum::CPP_RationalNumber newRationalNumber) {
    if (this->m_size < this->m_capacity) {
        this->m_data[this->m_size++] = newRationalNumber;
        setError(rnaNoError);
        return;
    }

    // resize array and retry
    const unsigned int oldCapacity = this->m_capacity;
    resize(oldCapacity + INCREMENTATION);
    assert (this->m_capacity == oldCapacity + INCREMENTATION);
    add(newRationalNumber);
}

void rnum::CPP_RationalNumberArray::set(const unsigned int position, const rnum::CPP_RationalNumber rationalNumber) {
    if(position > this->m_size)
        resize(position + 1);

    this->m_data[position] = rationalNumber;
    this->m_size = position+1;
}

const rnum::CPP_RationalNumber rnum::CPP_RationalNumberArray::get(const unsigned int position) {
    if (position >= this->m_size) {
        setError(rnaInvalidIndex);
        return NULL_RATIONAL_NUMBER;
    }

    setError(rnaNoError);
    return this->m_data[position];
}

void rnum::CPP_RationalNumberArray::remove(const unsigned int from, const unsigned int to) {
    //this->m_

    if (to < from) {
        setError(rnaInvalidIndex);
        return;
    }

    unsigned int offset = (to - from) + 1;

    // overwrite (from .. to) with subsequent elements;
    for(unsigned int i = from; i < this->m_capacity; i++)
        if (i+offset <= this->m_size)
            this->m_data[i] = this->m_data[i+offset];
        else
            break;

    // calculate new size
    this->m_size = (this->m_size > offset) ? this->m_size - offset : 0;

    setError(rnaNoError);

    for (unsigned int i = this->m_size; i < this->m_capacity; i++)
        this->m_data[i] = CPP_RationalNumber();
}

RNAErrorCode rnum::CPP_RationalNumberArray::rnaError(void) const {
    return this->m_error;
}

void rnum::CPP_RationalNumberArray::rnaSetErrorCallback (const rnum::cppErrorCallback_t callback) {
    this->m_errorCallback = callback;
}

void rnum::CPP_RationalNumberArray::setError(const RNAErrorCode errorCode) {
    this->m_error = errorCode;

    if (this->m_error != rnaNoError && this->m_errorCallback != NULL)
        this->m_errorCallback (*this);
}


/*void rnum::CPP_RationalNumberArray::initializeWithNullRationalNumber(const unsigned int from, const unsigned int to) {
    for (unsigned int i = from; i < to; i++) {
        this->data[i] = NULL_RATIONAL_NUMBER;
    }
}*/
