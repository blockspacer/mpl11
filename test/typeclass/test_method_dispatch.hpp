/*!
 * @file
 * Defines utilities to ease the testing of typeclass method dispatching.
 */

#ifndef BOOST_MPL11_TEST_TEST_METHOD_DISPATCH_HPP
#define BOOST_MPL11_TEST_TEST_METHOD_DISPATCH_HPP

#include <boost/mpl11/core.hpp>
#include <boost/mpl11/detail/std_is_same.hpp>


template <unsigned level = 0>
struct Archetype;

template <unsigned level = 0>
struct archetype {
    struct type { using mpl_datatype = Archetype<level>; };
};

namespace boost { namespace mpl11 {
    template <unsigned from, unsigned to>
    struct cast<Archetype<from>, Archetype<to>> {
        using type = cast;
        template <typename>
        using apply = archetype<to>;
    };
}}

template <template <typename ...> class f>
struct method_tag { using type = method_tag; };

template <template <typename ...> class f, typename ...args>
struct method {
    static_assert(boost::mpl11::detail::std_is_same<
        typename f<args...>::type,
        method_tag<f>
    >::value, "");
};

#endif // !BOOST_MPL11_TEST_TEST_METHOD_DISPATCH_HPP
