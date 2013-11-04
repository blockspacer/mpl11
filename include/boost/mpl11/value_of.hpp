/*!
 * @file
 * Defines `boost::mpl11::value_of`.
 */

#ifndef BOOST_MPL11_VALUE_OF_HPP
#define BOOST_MPL11_VALUE_OF_HPP

#include <boost/mpl11/fwd/value_of.hpp>

#include <boost/mpl11/class_of.hpp>


namespace boost { namespace mpl11 {
    template <typename Seq, typename Element>
    struct value_of
        : class_of<Seq>::type::template value_of_impl<Seq, Element>
    { };
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_VALUE_OF_HPP