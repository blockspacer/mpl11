/*!
 * @file
 * Forward declares `boost::mpl11::length`.
 */

#ifndef BOOST_MPL11_FWD_LENGTH_HPP
#define BOOST_MPL11_FWD_LENGTH_HPP

namespace boost { namespace mpl11 {
    /*!
     * @ingroup sequence_intrinsics
     *
     * Returns the number of elements contained in a `Sequence`.
     *
     * The length of a sequence is a non-negative `IntegralConstant`.
     */
    template <typename Sequence>
    struct length;

    template <typename Sequence>
    using length_t = typename length<Sequence>::type;
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_FWD_LENGTH_HPP