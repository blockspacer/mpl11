/**
 * This file defines the and_ metafunction.
 */

#ifndef MPL11_AND_HPP
#define MPL11_AND_HPP

#include <type_traits>


namespace mpl11 {

/**
 * Compute the logical and of its arguments.
 * Its arguments must be metafunctions and are short-circuited when possible.
 */
namespace detail {
    template <typename T, typename ...Rest>
    struct and_impl : and_impl<typename T::type, Rest...> { };

    template <typename ...Rest>
    struct and_impl<std::true_type, Rest...> : and_impl<Rest...> { };

    template <>
    struct and_impl<std::true_type> : std::true_type { };

    template <typename ...Rest>
    struct and_impl<std::false_type, Rest...> : std::false_type { };
} // end namespace detail

template <typename T, typename U, typename ...Rest>
struct and_ : detail::and_impl<T, U, Rest...> { };

} // end namespace mpl11

#endif // !MPL11_AND_HPP