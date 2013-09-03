/*!
 * @file
 * Contains unit tests for `boost::mpl11::view::empty`.
 */

#include <boost/mpl11/view/empty.hpp>

#include <boost/mpl11/intrinsic/begin.hpp>
#include <boost/mpl11/intrinsic/end.hpp>
#include <boost/mpl11/intrinsic/equal_to.hpp>
#include <boost/mpl11/intrinsic/is_empty.hpp>


using namespace boost::mpl11;
using namespace intrinsic;

static_assert(is_empty<view::empty>::type::value, "");

static_assert(equal_to<
    begin<view::empty>::type,
    end<view::empty>::type
>::type::value, "");


int main() { }
