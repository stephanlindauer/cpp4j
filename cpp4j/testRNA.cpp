/*
   Simple Unit Test for type RationalNumberArray
*/

#include <stdio.h>
#include <assert.h>

#include "rationalnumber.h"
#include "rationalnumberarray.h"


const unsigned int wantedCapacity = 10;

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

    rnaSet (rna, rn2, 0);
    rnx = rnaGet (rna, 0);
    assert (rnEqual (rn2, rnx));

    rnaDelete(rna);
    assert (rna == 0);

    rna = rnaCreate (1);

    rnaAdd (rna, rn1);
    rnaAdd (rna, rn2);
    rnaAdd (rna, rn3);
    rnaAdd (rna, rn4);
    rnaAdd (rna, rn5);
    rnaAdd (rna, rn6);
    rnaAdd (rna, rn7);
    rnaAdd (rna, rn8);

    assert (rnaSize(rna) == 8);
    assert (rnaCapacity(rna) == wantedCapacity + 1);

    rnaResize(rna, 4);
    assert (rnaSize(rna) == 4);
    assert (rnaCapacity(rna) == 4);

    rnaSet(rna, rn6, 6); // should increase size to 6, 5th element should be initialized to (0|1)
    rnx = rnaGet (rna, 5);

    assert (rnaSize(rna) == 6);
    assert (rnaCapacity(rna) == 14);

    assert (rnEqual(rnx, rnn));

    rnaRemove(rna, 3, 5); // remove 4th, 5th, 6th element; 7th element becomes 4th element
    rnx = rnaGet (rna, 3);
    assert (rnaSize(rna) == 4);
    assert (rnaCapacity(rna) == 14);
    assert (rnEqual(rnx, rn6));

    printf(" successful!\n");
}


