/*!
 * @file
 * Defines `boost::mpl11::always`.
 */

#ifndef BOOST_MPL11_ALWAYS_HPP
#define BOOST_MPL11_ALWAYS_HPP

#include <boost/mpl11/fwd/always.hpp>


namespace boost { namespace mpl11 {
    template <typename T>
    struct always {
        template <typename ...>
        struct apply {
            using type = T;
        };
    };
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_ALWAYS_HPP
