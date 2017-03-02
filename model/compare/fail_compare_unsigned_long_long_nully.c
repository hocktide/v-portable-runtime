/**
 * \file fail_compare_unsigned_long_long_nully.c
 *
 * A null right hand side argument causes a model assertion.
 *
 * \copyright 2017 Velo Payments, Inc.  All rights reserved.
 */

#include <stdlib.h>
#include <cbmc/model_assert.h>
#include <vpr/compare.h>

unsigned long long nondet_arg1();

int main(int argc, char* argv[])
{
    unsigned long long x = nondet_arg1();

    compare_unsigned_long_long(&x, NULL, sizeof(unsigned long long));

    return 0;
}
