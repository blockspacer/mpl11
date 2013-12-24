/*!
 * @file
 * Forward declares `boost::mpl11::AssociativeSequence`.
 */

#ifndef BOOST_MPL11_FWD_ASSOCIATIVE_SEQUENCE_HPP
#define BOOST_MPL11_FWD_ASSOCIATIVE_SEQUENCE_HPP

#include <boost/mpl11/fwd/comparable.hpp>
#include <boost/mpl11/fwd/sequence.hpp>


namespace boost { namespace mpl11 {
    /*!
     * @ingroup concepts
     *
     * `Sequence` allowing retrieval of elements based on keys.
     *
     *
     * ## Refinement of
     * `Sequence`, `Comparable`
     *
     *
     * ## Notation
     * | Expression | Description
     * | ---------- | -----------
     * | `S`        | An `AssociativeSequence`
     * | `Element`  | An element of `S`
     * | `Key`      | Any type
     * | `Default`  | Any type
     *
     *
     * ## Valid expressions
     * | Expression                      | Type
     * | ----------                      | ----
     * | `key_of<S, Element>::type`      | Any type
     * | `value_of<S, Element>::type`    | Any type
     * | `at_key<S, Key>::type`          | Any type
     * | `at_key<S, Key, Default>::type` | Any type
     * | `has_key<S, Key>`               | Boolean `Integral`
     */
    struct AssociativeSequence : Sequence, Comparable {
#ifdef BOOST_MPL11_DOXYGEN_INVOKED
        //! This operation must be provided by the user.
        template <typename Sequence, typename Key>
        struct at_key_impl;

        //! This operation must be provided by the user.
        template <typename Sequence, typename Key, typename Default>
        struct at_key_def_impl;

        //! This operation must be provided by the user.
        template <typename Sequence, typename Key>
        struct has_key_impl;

        //! This operation must be provided by the user.
        template <typename Sequence, typename Element>
        struct key_of_impl;

        //! This operation must be provided by the user.
        template <typename Sequence, typename Element>
        struct value_of_impl;
#endif
    };
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_FWD_ASSOCIATIVE_SEQUENCE_HPP
