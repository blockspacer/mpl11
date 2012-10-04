/**
 * This file defines the size metafunction.
 */

#ifndef MPL11_SIZE_HPP
#define MPL11_SIZE_HPP

#include <cstddef>
#include <type_traits>


namespace mpl11 {

/**
 * Determine the number of parameters in a parameter pack.
 */
namespace detail {
    template <typename Counter, typename ...> struct size_impl;

    template <typename Acc, Acc i>
    struct size_impl<std::integral_constant<Acc, i>> {
        using type = std::integral_constant<Acc, i>;
    };

    template <typename Acc, Acc i, typename T, typename ...Rest>
    struct size_impl<std::integral_constant<Acc, i>, T, Rest...>
        : size_impl<std::integral_constant<Acc, i + 1>, Rest...> { };
} // end namespace detail

template <typename ...T>
using size = detail::size_impl<std::integral_constant<std::size_t, 0>, T...>;

} // end namespace mpl11

#endif // !MPL11_SIZE_HPP