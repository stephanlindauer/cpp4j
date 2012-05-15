

#include <stdio.h>
#include <assert.h>

#include "rationalnumber.h"
#include "rationalnumberarray.h"

using namespace rnum;

void testCPP_RNA(void)
{
    printf("Performing unit tests for CPP_RationalNumberArray...");
    fflush(stdout);



    CPP_RationalNumber
            rn1 = CPP_RationalNumber( 3, 4 ),
            rn2 = CPP_RationalNumber(  6, 4 ),
            rn3 = CPP_RationalNumber(  3, 2 ),
            rn4 = CPP_RationalNumber(  -9, -6 ),
            rn5 = CPP_RationalNumber(  9, -6 ),
            rn6 = CPP_RationalNumber(  9, 4 ),
            rn7 = CPP_RationalNumber(  0, 4 ),
            rn8 = CPP_RationalNumber(  4, 0 ),
            rnn = CPP_RationalNumber(  0, 1 ), // null value
            rnx; // uninitialized

    /* Part 1 - RationalNumberArray data type */
    CPP_RationalNumberArray rna (wantedCapacity);

    assert ( rna.size() == 0 );
    assert ( rna.capacity() == wantedCapacity );

    unsigned int i = 0;

    for (i = 0; i<wantedCapacity; i++) {
        rnx = rna.get( i);
        assert (rnx == rnn);
    }

    rna.resize( wantedCapacity * 2 );

    assert ( rna.size() == 0 );
    assert ( rna.capacity() == wantedCapacity * 2 );

    rna.add(rn1);
    assert ( rna.size() == 1 );
    assert ( rna.capacity() == wantedCapacity * 2 );

    rnx = rna.get(0);
    assert (rn1 == rnx);

    rna.set(0, rn2);
    rnx = rna.get( 0);
    assert (rn2 == rnx);

    rna.add( rn1);
    assert (rna.size() == 2);
    assert (rna.capacity() == wantedCapacity *2 );

    rna.add( rn2);
    assert (rna.size() == 3);
    assert (rna.capacity() == wantedCapacity *2);

    rna.add(rn3);
    assert (rna.size() == 4);
    assert (rna.capacity() == wantedCapacity *2);

    rna.add( rn4);
    rna.add( rn5);
    rna.add( rn6);
    rna.add( rn7);
    rna.add( rn8);

    assert (rna.size() == 9);

    rna.resize( 4); // remaining elements: 0, 1, 2, 3
    assert (rna.size() == 4);
    assert (rna.capacity() == 4);

    // 0, 1, 2, 3 => as before
    // new elements: 4, 5, 6
    // 4 => rnn
    // 5 => rnn
    // 6 => rn6
    rna.set( 6, rn6);

    rnx = rna.get( 4);
    assert (rnx== rnn);

    rnx = rna.get( 5);
    assert (rnx== rnn);

    rnx = rna.get( 6);
    assert (rnx ==rn6);
    assert (rna.size() == 7);
    assert (rna.capacity() == 7);


    // remove elements: 3, 4, 5
    // elements 6.. become elements 3..
    rna.remove( 3, 5);

    rnx = rna.get( 3);
    assert (rnx == rn6);

    assert (rna.size() == 4);
    assert (rna.capacity() == 7);

    rnx = rna.get( 10);
    assert (rna.rnaError() == rnaInvalidIndex);
    assert (rnx== rnn);

    rna.remove( 0, 10);
    assert (rna.size() == 0);



    printf(" successful!\n");
}
