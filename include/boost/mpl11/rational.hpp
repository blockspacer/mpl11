/*!
 * @file
 * Defines the @ref Rational datatype.
 *
 *
 * @copyright Louis Dionne 2014
 * Distributed under the Boost Software License, Version 1.0.
 *         (See accompanying file LICENSE.md or copy at
 *             http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_MPL11_RATIONAL_HPP
#define BOOST_MPL11_RATIONAL_HPP

#include <boost/mpl11/fwd/rational.hpp>

#include <boost/mpl11/bool.hpp>
#include <boost/mpl11/comparable.hpp>
#include <boost/mpl11/core.hpp>
#include <boost/mpl11/enumerable.hpp>
#include <boost/mpl11/field.hpp>
#include <boost/mpl11/group.hpp>
#include <boost/mpl11/monoid.hpp>
#include <boost/mpl11/orderable.hpp>
#include <boost/mpl11/ring.hpp>


namespace boost { namespace mpl11 {
    template <typename T, T numerator, T denominator>
    struct rational_c {
        using type = rational_c;
        using mpl_datatype = Rational;

        static constexpr T num = numerator;
        static constexpr T den = denominator;
    };

    template <>
    struct cast<Integer, Rational> {
        using type = cast;
        template <typename i>
        using apply = rational_c<
            typename i::value_type, i::value
        >;
    };

    template <>
    struct Monoid<Rational> : instantiate<Monoid>::with<Rational> {
        template <typename x, typename y>
        using plus_impl = rational_c<
            decltype(true ? x::num : y::num),
            (x::num * y::den) + (x::den * y::num),
            x::den * y::den
        >;

        template <typename ...>
        using zero_impl = rational_c<long long, 0>;
    };

    template <>
    struct Group<Rational> : instantiate<Group>::with<Rational> {
        template <typename x, typename y>
        using minus_impl = rational_c<
            decltype(true ? x::num : y::num),
            (x::num * y::den) - (x::den * y::num),
            x::den * y::den
        >;

        template <typename x>
        using negate_impl = rational_c<
            decltype(-x::num), -x::num, x::den
        >;
    };

    template <>
    struct Ring<Rational> : instantiate<Ring>::with<Rational> {
        template <typename x, typename y>
        using mult_impl = rational_c<
            decltype(true ? x::num : y::num),
            x::num * y::num,
            x::den * y::den
        >;

        template <typename ...>
        using one_impl = rational_c<long long, 1>;
    };

    template <>
    struct Field<Rational> : instantiate<Field>::with<Rational> {
        template <typename x, typename y>
        using quot_impl = rational_c<
            decltype(true ? x::num : y::num),
            x::num * y::den,
            x::den * y::num
        >;

        template <typename x>
        using recip_impl = rational_c<
            decltype(x::num), x::den, x::num
        >;
    };

    template <>
    struct Comparable<Rational> : instantiate<Comparable>::with<Rational> {
        template <typename x, typename y>
        using equal_impl = bool_<
            x::num * y::den == x::den * y::num
        >;

        template <typename x, typename y>
        using not_equal_impl = bool_<
            x::num * y::den != x::den * y::num
        >;
    };

    template <>
    struct Orderable<Rational> : instantiate<Orderable>::with<Rational> {
        template <typename x, typename y>
        using less_impl = bool_<(
            x::num * y::den < x::den * y::num
        )>;

        template <typename x, typename y>
        using less_equal_impl = bool_<(
            x::num * y::den <= x::den * y::num
        )>;

        template <typename x, typename y>
        using greater_impl = bool_<(
            x::num * y::den > x::den * y::num
        )>;

        template <typename x, typename y>
        using greater_equal_impl = bool_<(
            x::num * y::den >= x::den * y::num
        )>;
    };
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_RATIONAL_HPP
