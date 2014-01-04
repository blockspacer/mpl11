/*!
 * @file
 * Contains unit tests for `boost::mpl11::take_while`.
 */

#include <boost/mpl11/take_while.hpp>

#include <boost/mpl11/integral_c.hpp>
#include <boost/mpl11/list.hpp>
#include "sequence_test.hpp"


using namespace mpl11_test;
using namespace boost::mpl11;

struct nonzero { template <typename N> using apply = bool_<N::value != 0>; };

template <int ...Seq>
struct nonzero_prefix {
    template <int ...Prefix>
    struct is :
        forward_sequence_test<
            take_while_t<nonzero, list<int_<Seq>...>>,
            int_<Prefix>...
        >
    { };
};

struct tests :
    nonzero_prefix<>::is<>,

    nonzero_prefix<0>::is<>,
    nonzero_prefix<1>::is<1>,

    nonzero_prefix<0, 0>::is<>,
    nonzero_prefix<0, 1>::is<>,
    nonzero_prefix<1, 0>::is<1>,
    nonzero_prefix<1, 2>::is<1, 2>,

    nonzero_prefix<0, 0, 0>::is<>,
    nonzero_prefix<0, 0, 1>::is<>,
    nonzero_prefix<0, 1, 0>::is<>,
    nonzero_prefix<0, 1, 2>::is<>,
    nonzero_prefix<1, 0, 0>::is<1>,
    nonzero_prefix<1, 0, 2>::is<1>,
    nonzero_prefix<1, 2, 0>::is<1, 2>,
    nonzero_prefix<1, 2, 3>::is<1, 2, 3>
{ };


int main() { }