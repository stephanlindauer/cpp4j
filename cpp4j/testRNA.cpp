/*
   Simple Unit Test for type RationalNumberArray
*/

#include <stdio.h>
#include <assert.h>

#include "rationalnumber.h"
#include "rationalnumberarray.h"

const unsigned int wantedCapacity = 10;

bool errorCBCalled = false;

void myRNAErrorCallback(RationalNumberArray * rna) {
    errorCBCalled = true;
    assert (rnaError(rna) != rnaNoError);
}

void testRNA(void)
{

    printf("Performing unit tests for RationalNumberArray...");
    fflush(stdout);

    RationalNumber
            rn1 = { 3, 4 },
            rn2 = { 6, 4 },
            rn3 = { 3, 2 },
            rn4 = { -9, -6 },
            rn5 = { 9, -6 },
            rn6 = { 9, 4 },
            rn7 = { 0, 4 },
            rn8 = { 4, 0 },
            rnn = { 0, 1 }, // null value
            rnx; // uninitialized

    /* Part 1 - RationalNumberArray data type */
    RationalNumberArray * rna = rnaCreate(wantedCapacity);

    assert ( rnaSize(rna) == 0 );
    assert ( rnaCapacity(rna) == wantedCapacity );

    unsigned int i = 0;

    for (i = 0; i<wantedCapacity; i++) {
        rnx = rnaGet (rna, i);
        assert (rnEqual(rnx, rnn));
    }

    rnaResize ( rna, wantedCapacity * 2 );

    assert ( rnaSize(rna) == 0 );
    assert ( rnaCapacity(rna) == wantedCapacity * 2 );

    rnaAdd(rna, rn1);
    assert ( rnaSize(rna) == 1 );
    assert ( rnaCapacity(rna) == wantedCapacity * 2 );

    rnx = rnaGet (rna, 0);
    assert (rnEqual (rn1, rnx));

    rnaSet (rna, 0, rn2);
    rnx = rnaGet (rna, 0);
    assert (rnEqual (rn2, rnx));

    rna = rnaDelete(rna);
    assert (rna == 0);

    rna = rnaCreate (1);
    assert (rnaSize(rna) == 0);

    rnaAdd (rna, rn1);
    assert (rnaSize(rna) == 1);
    assert (rnaCapacity(rna) == 1);

    rnaAdd (rna, rn2);
    assert (rnaSize(rna) == 2);
    assert (rnaCapacity(rna) == 101);

    rnaAdd (rna, rn3);
    assert (rnaSize(rna) == 3);
    assert (rnaCapacity(rna) == 101);

    rnaAdd (rna, rn4);
    rnaAdd (rna, rn5);
    rnaAdd (rna, rn6);
    rnaAdd (rna, rn7);
    rnaAdd (rna, rn8);

    assert (rnaSize(rna) == 8);

    rnaResize(rna, 4); // remaining elements: 0, 1, 2, 3
    assert (rnaSize(rna) == 4);
    assert (rnaCapacity(rna) == 4);

    // 0, 1, 2, 3 => as before
    // new elements: 4, 5, 6
    // 4 => rnn
    // 5 => rnn
    // 6 => rn6
    rnaSet(rna, 6, rn6);

    rnx = rnaGet (rna, 4);
    assert (rnEqual(rnx, rnn));

    rnx = rnaGet (rna, 5);
    assert (rnEqual(rnx, rnn));

    rnx = rnaGet (rna, 6);
    assert (rnEqual(rnx, rn6));
    assert (rnaSize(rna) == 7);
    assert (rnaCapacity(rna) == 7);


    // remove elements: 3, 4, 5
    // elements 6.. become elements 3..
    rnaRemove(rna, 3, 5);

    rnx = rnaGet (rna, 3);
    assert (rnEqual(rnx, rn6));

    assert (rnaSize(rna) == 4);
    assert (rnaCapacity(rna) == 7);

    rnaSetErrorCallback(rna, &myRNAErrorCallback);

    rnx = rnaGet(rna, 10);
    assert (errorCBCalled == true);
    assert (rnEqual(rnx, rnn));

    rnaRemove(rna, 0, 10);
    assert (rnaSize(rna) == 0);

    printf(" successful!\n");
}
