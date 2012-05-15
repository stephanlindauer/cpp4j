#include <stdio.h>
#include <assert.h>

#include "rationalnumber.h"
#include "rationalnumberarray.h"

using namespace rnum;

void testCPP_RN(void)
{
    printf("Performing unit tests for RationalNumberArray...");
    fflush(stdout);


    CPP_RationalNumber a, x;
    CPP_RationalNumber b(0,1), c(2,3), d(9,3), e(-4,2), f(17,3);
    a = b + c*d - e/f;
    x = -f + CPP_RationalNumber(3,4);
    a.toString();
    assert( a == CPP_RationalNumber( 40 , 17 ));

    assert( x == CPP_RationalNumber( -52 , 12 ));



    int i=5, j=4;
   /*RationalNumber a(1,2), b(7,3);
    RationalNumber aa = i*a, bb = b/j;
    RationalNumber ia (i);
    RationalNumber ja = j;*/



    printf(" successful!\n");
}