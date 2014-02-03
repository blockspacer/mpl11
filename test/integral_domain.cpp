/*!
 * @file
 * Contains unit tests for the @ref IntegralDomain typeclass.
 */

#include <boost/mpl11/integral_domain.hpp>

#include <boost/mpl11/core.hpp>
#include <boost/mpl11/detail/std_is_same.hpp>
#include <boost/mpl11/functional.hpp>


using namespace boost::mpl11;
using detail::std_is_same;

///////////////////////////
// Test method dispatching
///////////////////////////
struct Archetype1 { template <typename> using from = quote<id>; };
struct archetype1 { struct type { using mpl_datatype = Archetype1; }; };

struct Archetype2;
struct archetype2 { struct type { using mpl_datatype = Archetype2; }; };

struct div_tag;
struct mod_tag;

namespace boost { namespace mpl11 {
    template <>
    struct common_datatype<Archetype1, Archetype2> {
        using type = Archetype1;
    };

    template <>
    struct IntegralDomain<Archetype1> {
        template <typename, typename>
        struct div_impl { using type = div_tag; };

        template <typename, typename>
        struct mod_impl { using type = mod_tag; };
    };
}} // end namespace boost::mpl11

static_assert(std_is_same<
    div<archetype1, archetype1>::type,
    div_tag
>::value, "");

static_assert(std_is_same<
    div<archetype1, archetype2>::type,
    div_tag
>::value, "");

static_assert(std_is_same<
    div<archetype2, archetype1>::type,
    div_tag
>::value, "");


static_assert(std_is_same<
    mod<archetype1, archetype1>::type,
    mod_tag
>::value, "");

static_assert(std_is_same<
    mod<archetype1, archetype2>::type,
    mod_tag
>::value, "");

static_assert(std_is_same<
    mod<archetype2, archetype1>::type,
    mod_tag
>::value, "");


int main() { }