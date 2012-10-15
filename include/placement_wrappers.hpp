//
// Copyright (C) 2011-12, Dynamic NDArray Developers
// BSD 2-Clause License, see LICENSE.txt
//
// This header defines some placement wrappers of dtype and ndarray
// to enable wrapping them without adding extra indirection layers.
//

#ifndef _DND__PLACEMENT_WRAPPERS_HPP_
#define _DND__PLACEMENT_WRAPPERS_HPP_

#include <dynd/dtype.hpp>
#include <dynd/ndarray.hpp>
#include <dynd/codegen/codegen_cache.hpp>

namespace pydynd {

// This is a struct with the same alignment (because of intptr_t)
// and size as dynd::dtype. It's what we wrap in Cython, and use
// placement new and delete to manage its lifetime.
struct dtype_placement_wrapper {
    intptr_t dummy[(sizeof(dynd::dtype) + sizeof(intptr_t) - 1)/sizeof(intptr_t)];
};

inline void dtype_placement_new(dtype_placement_wrapper& v)
{
    // Call placement new
    new (&v) dynd::dtype();
}

inline void dtype_placement_delete(dtype_placement_wrapper& v)
{
    // Call the destructor
    ((dynd::dtype *)(&v))->~dtype();
}

// dtype placement cast
inline dynd::dtype& GET(dtype_placement_wrapper& v)
{
    return *(dynd::dtype *)&v;
}

// dtype placement assignment
inline void SET(dtype_placement_wrapper& v, const dynd::dtype& d)
{
    *(dynd::dtype *)&v = d;
}

///////////////////////////////////
// Same thing as above, for ndarray

struct ndarray_placement_wrapper {
    intptr_t dummy[(sizeof(dynd::ndarray) + sizeof(intptr_t) - 1)/sizeof(intptr_t)];
};

inline void ndarray_placement_new(ndarray_placement_wrapper& v)
{
    // Call placement new
    new (&v) dynd::ndarray();
}

inline void ndarray_placement_delete(ndarray_placement_wrapper& v)
{
    // Call the destructor
    ((dynd::ndarray *)(&v))->~ndarray();
}

// placement cast
inline dynd::ndarray& GET(ndarray_placement_wrapper& v)
{
    return *(dynd::ndarray *)&v;
}

// placement assignment
inline void SET(ndarray_placement_wrapper& v, const dynd::ndarray& d)
{
    *(dynd::ndarray *)&v = d;
}

///////////////////////////////////
// Same thing as above, for codegen_cache

struct codegen_cache_placement_wrapper {
    intptr_t dummy[(sizeof(dynd::codegen_cache) + sizeof(intptr_t) - 1)/sizeof(intptr_t)];
};

inline void codegen_cache_placement_new(codegen_cache_placement_wrapper& v)
{
    // Call placement new
    new (&v) dynd::codegen_cache();
}

inline void codegen_cache_placement_delete(codegen_cache_placement_wrapper& v)
{
    // Call the destructor
    ((dynd::codegen_cache *)(&v))->~codegen_cache();
}

// placement cast
inline dynd::codegen_cache& GET(codegen_cache_placement_wrapper& v)
{
    return *(dynd::codegen_cache *)&v;
}

} // namespace pydynd

#endif // _DND__PLACEMENT_WRAPPERS_HPP_
