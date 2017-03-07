/**
 * \file abstract_factory.h
 *
 * Abstract factory provides a registration and instantiation pattern for
 * interface implementations.  Internally, this factory uses a dynamic array to
 * maintain implementations.  The ideal use of this pattern is to perform
 * registration on startup / library load, and then use the abstract factory to
 * create instances of a given interface.  In this way, some compile and
 * link-time optimization can be used to select the correct implementation of a
 * given interface for a given platform.
 *
 * The abstract factory is not used directly by user code.  Instead,
 * it enables higher-level libraries such as the crypto library, to select the
 * right implementation of a given primitive or algorithm based on user
 * requirements.
 *
 * \copyright 2017 Velo Payments, Inc.  All rights reserved.
 */

#ifndef VPR_ABSTRACT_FACTORY_HEADER_GUARD
#define VPR_ABSTRACT_FACTORY_HEADER_GUARD

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <vpr/disposable.h>

/**
 * \brief instance implementation registration.
 *
 * This structure contains the details for a specific implementation
 * registration for a given instance.  This is what is stored in the abstract
 * factory.  The abstract factory, in turn, uses these details to select either
 * any implementation of a given interface, the best implementation of a given
 * interface, or a specific implementation of a given interface.
 */
typedef struct abstract_factory_registration
{
    /**
     * The interface that this registration implements.
     */
    uint32_t interface;

    /**
     * The implementation ID for this registration.
     */
    uint32_t implementation;

    /**
     * Features provided by this implementation.  Interface-specific.
     */
    uint32_t implementation_features;

    /**
     * An opaque pointer to the factory for this registration.
     */
    void* factory;

    /**
     * An opaque context pointer to use when calling the factory method.
     */
    void* context;

} abstract_factory_registration_t;

/**
 * Register an implementation in the abstract factory.
 *
 * Note: this method is NOT threadsafe.  All registrations should happen before
 * any other abstract factory methods are used by other threads.
 *
 * \param impl          The factory registration structure to register.
 */
void abstract_factory_register(abstract_factory_registration_t* impl);

/**
 * Look up an implementation of a given interface that includes the given
 * features.
 *
 * \param interface     The interface ID to look up.
 * \param features      The features this interface must have.
 *
 * \returns a matching registration or NULL if no suitable implementation was
 * found.
 */
abstract_factory_registration_t*
abstract_factory_find(uint32_t interface, uint32_t features);

/* make this header C++ friendly. */
#ifdef __cplusplus
}
#endif  //__cplusplus

#endif  //VPR_ABSTRACT_FACTORY_HEADER_GUARD