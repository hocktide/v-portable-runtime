/**
 * \file fail_compare_long_double_nullx.c
 *
 * A null left hand side argument causes a model assertion.
 *
 * \copyright 2017 Velo Payments, Inc.  All rights reserved.
 */

#include <stdlib.h>
#include <cbmc/model_assert.h>
#include <vpr/compare.h>

long double nondet_arg2();

int main(int argc, char* argv[])
{
    long double y = nondet_arg2();

    compare_long_double(NULL, &y, sizeof(long double));

    return 0;
}
