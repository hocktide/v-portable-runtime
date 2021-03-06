/**
 * \file doubly_linked_list_init.c
 *
 * Implementation of doubly_linked_list_init.
 *
 * \copyright 2019 Velo Payments, Inc.  All rights reserved.
 */

#include <cbmc/model_assert.h>
#include <vpr/doubly_linked_list.h>
#include <vpr/parameters.h>

/* this is the real implementation. */
#ifndef MODEL_CHECK_vpr_dll_shadowed

//forward decls
static void dll_dispose(void*);

/**
 * \brief Initialize a doubly linked list.
 *
 * This method allows for the creation of a doubly linked list.  Once initialized,
 * the list will have zero elements, and the first and last pointers will
 * be set to null.
 *
 * When the function completes successfully, the caller owns this
 * ::doubly_linked_list_t instance and must dispose of it by calling dispose() when
 * it is no longer needed.
 *
 * \param options           The doubly linked list options to use for this instance.
 * \param dll               The doubly linked list to initialize.
 *
 * \returns a status code indicating success or failure.
 *      - \ref VPR_STATUS_SUCCESS if successful.
 */
int doubly_linked_list_init(
    doubly_linked_list_options_t* options, doubly_linked_list_t* dll)
{

    //the doubly linked list structure must be non-null
    MODEL_ASSERT(NULL != dll);

    //sanity checks on options
    MODEL_ASSERT(NULL != options);
    MODEL_ASSERT(options->element_size > 0);
    MODEL_ASSERT(NULL != options->alloc_opts);

    dll->hdr.dispose = &dll_dispose;
    dll->options = options;
    dll->elements = 0;
    dll->first = NULL;
    dll->last = NULL;

    //success
    return VPR_STATUS_SUCCESS;
}


/**
 * Dispose of a doubly linked list.
 *
 * \param pdll        An opaque pointer to the doubly linked list
 */
void dll_dispose(void* pdll)
{
    MODEL_ASSERT(NULL != pdll);
    doubly_linked_list_t* dll = (doubly_linked_list_t*)pdll;
    MODEL_ASSERT(NULL != dll->options);
    MODEL_ASSERT(NULL != dll->options->alloc_opts);

    //dispose of each element in the list
    doubly_linked_list_element_t* element = dll->first;
    while (element != NULL)
    {

        // this call frees the memory for the data pointed to by the element
        if (NULL != element->data && NULL != dll->options->doubly_linked_list_element_dispose)
        {
            dll->options->doubly_linked_list_element_dispose(
                dll->options->alloc_opts, element->data);
        }

        // free the space for the element itself, being careful to
        // advance our pointer first
        doubly_linked_list_element_t* curr = element;
        element = element->next;

        release(dll->options->alloc_opts, curr);
    }
}

#endif /*!defined(MODEL_CHECK_vpr_dll_shadowed)*/
