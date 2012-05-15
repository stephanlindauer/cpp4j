#include <stdio.h>

#include "rationalnumber.h"

#include "testRN.cpp"
#include "testRNA.cpp"
#include "testCPP_RN.cpp"
#include "testCPP_RNA.cpp"

int main()
{
    printf( "starting tests \n");
    testRN();
    testRNA();
    testCPP_RN();
    testCPP_RNA();
    printf( "tests done \n");

    return 0;
}
