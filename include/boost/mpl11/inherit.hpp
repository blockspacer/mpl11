/*!
 * @file
 * Defines `boost::mpl11::inherit`.
 */

#ifndef BOOST_MPL11_INHERIT_HPP
#define BOOST_MPL11_INHERIT_HPP

#include <boost/mpl11/fwd/inherit.hpp>


namespace boost { namespace mpl11 {
    template <typename ...Bases>
    struct inherit {
        struct type
            : Bases...
        { };
    };
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_INHERIT_HPP
