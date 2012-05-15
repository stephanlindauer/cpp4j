#include <stdio.h>
#include <assert.h>

#include "rationalnumber.h"
#include "rationalnumberarray.h"

using namespace rnum;

void testCPP_RN(void)
{
    printf("Performing unit tests for CPP_RationalNumber...");
    fflush(stdout);

    CPP_RationalNumber a, x;
    CPP_RationalNumber b(0,1), c(2,3), d(9,3), e(-4,2), f(17,3);

    a = b + c*d - e/f;
    assert( a == CPP_RationalNumber( 40 , 17 ));

    x = -f + CPP_RationalNumber(3,4);
    assert( x == CPP_RationalNumber( -59 , 12 ));

    int i=5, j=4;
    CPP_RationalNumber g(1,2), h(7,3);

    CPP_RationalNumber aa = g*i, bb = h/j;
    assert(aa==CPP_RationalNumber( 5 , 2 ));
    assert(bb==CPP_RationalNumber( 7 , 12 ));

    CPP_RationalNumber ia (i);
    assert(ia==CPP_RationalNumber( 5 , 1 ));

    CPP_RationalNumber ja = j;
    assert(ja==CPP_RationalNumber( 4 , 1 ));

    CPP_RationalNumber k(4,2), l(6,3);

    assert( (int) k.toDouble() == l.toInt() );

    printf(" successful!\n");
}
