#include <stdio.h>

#include "rationalnumber.h"

#include "testRN.cpp"
#include "testRNA.cpp"
#include "testCPP_RN.cpp"
#include "testCPP_RNA.cpp"
#include "testTemplates.cpp"

int main()
{
    printf( "starting tests \n");
    testRN();
    testRNA();
    testCPP_RN();
    testCPP_RNA();
    testTemplates();
    printf( "tests done \n");

    return 0;
}
