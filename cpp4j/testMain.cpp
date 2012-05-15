#include <stdio.h>


#include "rationalnumber.h"

#include "testRN.cpp"
#include "testRNA.cpp"
#include "testCPP_RN.cpp"

int main()
{
    printf( "starting tests \n");
    testRN();
    testRNA();
    testCPP_RN();
    printf( "tests done \n");

    return 0;
}

