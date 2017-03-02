/**
 * \file fail_compare_unsigned_long_badsize.c
 *
 * Passing the wrong size for comparison causes a model exception.
 *
 * \copyright 2017 Velo Payments, Inc.  All rights reserved.
 */

#include <stdlib.h>
#include <cbmc/model_assert.h>
#include <vpr/compare.h>

unsigned long nondet_arg1();
unsigned long nondet_arg2();

int main(int argc, char* argv[])
{
    unsigned long x = nondet_arg1();
    unsigned long y = nondet_arg2();

    compare_unsigned_long(&x, &y, sizeof(unsigned long) + 1);

    return 0;
}
