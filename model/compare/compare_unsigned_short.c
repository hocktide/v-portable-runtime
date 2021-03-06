/**
 * \file compare_unsigned_short.c
 *
 * Simple model check of compare_unsigned_short.
 *
 * \copyright 2017 Velo Payments, Inc.  All rights reserved.
 */

#include <stdlib.h>
#include <cbmc/model_assert.h>
#include <vpr/compare.h>

unsigned short nondet_arg1();
unsigned short nondet_arg2();

int main(int argc, char* argv[])
{
    unsigned short x = nondet_arg1();
    unsigned short y = nondet_arg2();

    if (x == y)
    {
        MODEL_ASSERT(
            compare_unsigned_short(&x, &y, sizeof(unsigned short)) == 0);
    }
    else if (x > y)
    {
        MODEL_ASSERT(
            compare_unsigned_short(&x, &y, sizeof(unsigned short)) > 0);
    }
    else
    {
        MODEL_ASSERT(x < y);
        MODEL_ASSERT(
            compare_unsigned_short(&x, &y, sizeof(unsigned short)) < 0);
    }

    return 0;
}
