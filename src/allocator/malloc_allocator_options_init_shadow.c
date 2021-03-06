/**
 * \file malloc_allocator_options_init_shadow.c
 *
 * Shadow library implementation of
 * malloc_allocator.malloc_allocator_options_init.
 *
 * \copyright 2017-2018 Velo Payments, Inc.  All rights reserved.
 */

#include <cbmc/model_assert.h>
#include <stdlib.h>
#include <string.h>
#include <vpr/allocator.h>
#include <vpr/allocator/malloc_allocator.h>
#include <vpr/parameters.h>

/* this is the shadow implementation. */
#ifdef MODEL_CHECK_vpr_malloc_allocator_shadowed

/**
 * Internal allocation method.
 */
static void* allocate_malloc(void* UNUSED(context), size_t size)
{
    MODEL_ASSERT(size > 0);

    return malloc(size);
}

/**
 * Internal release method.
 */
static void allocate_free(void* UNUSED(context), void* mem)
{
    MODEL_ASSERT(mem != NULL);

    return free(mem);
}

/**
 * Internal reallocate method.
 */
static void* allocate_realloc(void* UNUSED(context), void* mem,
    size_t UNUSED(old_size), size_t new_size)
{
    MODEL_ASSERT(mem != NULL);
    MODEL_ASSERT(new_size > 0);

    return realloc(mem, new_size);
}

/**
 * Internal control method.
 */
static int allocate_control(void* UNUSED(context), uint32_t UNUSED(key),
    void* UNUSED(value))
{
    /* control is undefined for the malloc allocator. */
    return VPR_ERROR_ALLOCATOR_CONTROL_INVALID_KEY;
}

/* forward decl for dispose method */
void malloc_allocator_options_dispose(allocator_options_t* options);

/**
 * \brief This method initializes the provided allocator_options_t structure so
 * that it uses malloc() and free() for managing memory.
 *
 * After malloc_allocator_options_init() is called, the caller owns the
 * ::allocator_options_t structure and must dispose of it by calling dispose().
 *
 * \param options       The allocation options structure to initialize.  Owned
 *                      by the caller.
 */
void malloc_allocator_options_init(allocator_options_t* options)
{
    MODEL_ASSERT(options != NULL);

    /* use our internal dispose method for disposing of this structure. */
    options->hdr.dispose = (dispose_method_t)&malloc_allocator_options_dispose;

    /* use malloc() for allocation. */
    options->allocator_allocate = &allocate_malloc;

    /* use free() for release. */
    options->allocator_release = &allocate_free;

    /* use realloc() for reallocate. */
    options->allocator_reallocate = &allocate_realloc;

    /* allocator_control is not valid for this allocator. */
    options->allocator_control = &allocate_control;

    /* force context to NULL */
    options->context = NULL;

    /* the allocator options structure should now be valid. */
    MODEL_ASSERT(MODEL_PROP_VALID_ALLOCATOR_OPTIONS(options));

    /* context should be set to NULL. */
    MODEL_ASSERT(options->context == NULL);
}

#endif /*defined(MODEL_CHECK_vpr_malloc_allocator_shadowed)*/
