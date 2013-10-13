/*!
 * @file
 * Defines `boost::mpl11::distance`.
 */

#ifndef BOOST_MPL11_ALGORITHM_DISTANCE_HPP
#define BOOST_MPL11_ALGORITHM_DISTANCE_HPP

#include <boost/mpl11/algorithm/distance_fwd.hpp>
#include <boost/mpl11/algorithm/foldl.hpp>
#include <boost/mpl11/dispatch.hpp>
#include <boost/mpl11/functional/arg.hpp>
#include <boost/mpl11/integral_c.hpp>
#include <boost/mpl11/intrinsic/next.hpp>
#include <boost/mpl11/view/bounded_by.hpp>


namespace boost { namespace mpl11 {
    template <typename First, typename Last>
    struct dispatch<tag::default_<tag::distance>, First, Last>
        : foldl<
            view::bounded_by<First, Last>,
            ulong<0>,
            next<_1>
        >
    { };
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_ALGORITHM_DISTANCE_HPP
