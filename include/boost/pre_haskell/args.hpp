/*!
 * @file
 * Defines `boost::mpl11::args`.
 */

#ifndef BOOST_MPL11_ARGS_HPP
#define BOOST_MPL11_ARGS_HPP

#include <boost/mpl11/fwd/args.hpp>

#include <boost/mpl11/detail/std_size_t.hpp>
#include <boost/mpl11/fwd/identity.hpp>
#include <boost/mpl11/join.hpp>
#include <boost/mpl11/repeat.hpp>
#include <boost/mpl11/vector.hpp>


namespace boost { namespace mpl11 {
namespace args_detail {
    using detail::std_size_t;

    //////////////////////////////////////////////////////////////////////////
    // Drop N elements from a parameter pack in O(1).
    //////////////////////////////////////////////////////////////////////////
    template <std_size_t N, typename Args>
    struct drop;

    template <std_size_t N, typename Args>
    using drop_t = typename drop<N, Args>::type;

    template <typename Ignore> struct drop_impl;
    template <typename ...Head>
    struct drop_impl<vector<Head...>> {
        template <typename ...Tail>
        static vector<Tail...> apply(Head..., identity<Tail>*...);
    };

    template <std_size_t N, typename ...Args>
    struct drop<N, vector<Args...>> {
        using type = decltype(
            drop_impl<
                repeat_c_t<void*, N>
            >::apply((identity<Args>*)nullptr...)
        );
    };

    //////////////////////////////////////////////////////////////////////////
    // Take the N first elements of a parameter pack in:
    // - O(1) if N <= O1_TAKE
    // - O(3 * floor(N / O1_TAKE)) otherwise
    //
    // IMPORTANT:
    // See detail/args_take.hpp before changing this value.
    //////////////////////////////////////////////////////////////////////////
    static constexpr std_size_t O1_TAKE = 100;

    template <std_size_t N, typename Args, bool = (N <= O1_TAKE)>
    struct take;

    template <std_size_t N, typename Args>
    using take_t = typename take<N, Args>::type;

    template <std_size_t N, typename Args>
    struct take<N, Args, false>
        : join<
            take_t<O1_TAKE, Args>,
            take_t<N-O1_TAKE, drop_t<O1_TAKE, Args>>
        >
    { };

    #include <boost/mpl11/detail/args_take.hpp>

    //////////////////////////////////////////////////////////////////////////
    // Slice a parameter pack in almost O(1) (see take and drop)
    //////////////////////////////////////////////////////////////////////////
    enum class optimization { empty, until_end, from_start, none };

    template <optimization, std_size_t First, std_size_t Last, typename ...>
    struct args_impl;

    // [First, sizeof...(Args))
    template <std_size_t First, std_size_t Last, typename ...Args>
    struct args_impl<optimization::until_end, First, Last, Args...>
        : drop<First, vector<Args...>>
    { };

    // [0, Last)
    template <std_size_t First, std_size_t Last, typename ...Args>
    struct args_impl<optimization::from_start, First, Last, Args...>
        : take<Last, vector<Args...>>
    { };

    // empty range
    template <std_size_t First, std_size_t Last, typename ...Args>
    struct args_impl<optimization::empty, First, Last, Args...> {
        using type = vector<>;
    };

    // [First, Last)
    template <std_size_t First, std_size_t Last, typename ...Args>
    struct args_impl<optimization::none, First, Last, Args...>
        : take<
            Last - First, drop_t<First, vector<Args...>>
        >
    { };
} // end namespace args_detail

template <detail::std_size_t First>
struct args<First> {
    template <typename ...Args>
    using apply =
        typename args<First, sizeof...(Args)>::template apply<Args...>;
};

template <detail::std_size_t First, detail::std_size_t Last>
struct args<First, Last> {
    static_assert(First <= Last,
    "Invalid usage of `args<>`: "
    "invalid bounds for [First, Last); First > Last.");

    template <typename ...Args>
    class apply {
        static_assert(Last <= sizeof...(Args),
        "Invalid usage of `args<>`: "
        "the last index is beyond the end of the provided arguments.");
        using optimization = args_detail::optimization;

    public:
        using type = typename args_detail::args_impl<
            First == Last           ? optimization::empty       :
            Last == sizeof...(Args) ? optimization::until_end   :
            First == 0              ? optimization::from_start  :
            /* else */                optimization::none,
            First, Last, Args...
        >::type;
    };
};
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_ARGS_HPP