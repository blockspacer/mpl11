/*!
 * @file
 * Contains unit tests for `boost::mpl11::foldl`.
 */

#include <boost/mpl11/foldl.hpp>

#include <boost/mpl11/detail/sequence_test.hpp>
#include <boost/mpl11/quote.hpp>
#include <boost/mpl11/snoc.hpp>


using namespace boost::mpl11;

template <int> struct x;

template <int ...i>
struct test_with {
    static_assert(equal<
        foldl_t<
            quote<snoc>,
            detail::minimal_sequence<>,
            detail::minimal_sequence<x<i>...>
        >,
        detail::minimal_sequence<x<i>...>
    >::value, "");
};

struct tests :
    test_with<>,
    test_with<0>,
    test_with<0, 1>,
    test_with<0, 1, 2>,
    test_with<0, 1, 2, 3>,
    test_with<0, 1, 2, 3, 4>,
    test_with<0, 1, 2, 3, 4, 5>,
    test_with<0, 1, 2, 3, 4, 5, 6>,
    test_with<0, 1, 2, 3, 4, 5, 6, 7>,
    test_with<0, 1, 2, 3, 4, 5, 6, 7, 8>,
    test_with<0, 1, 2, 3, 4, 5, 6, 7, 8, 9>
{ };


int main() { }
