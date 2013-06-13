/*!
 * @file
 * This file defines `boost::mpl11::if_` and `boost::mpl11::if_c`.
 */

#ifndef BOOST_MPL11_IF_HPP
#define BOOST_MPL11_IF_HPP

namespace boost { namespace mpl11 { inline namespace v2 {
template <typename M>
struct eval;

namespace if_detail {
template <typename T>
struct unwrap_eval { using type = T; };

template <typename T>
struct unwrap_eval<eval<T>> : T { };

template <bool Cond, typename Then, typename Else>
struct conditional : unwrap_eval<Then> { };

template <typename Then, typename Else>
struct conditional<false, Then, Else> : unwrap_eval<Else> { };

template <bool Cond, typename Action>
struct branch {
    static constexpr bool condition = Cond;
    using action = Action;
};

// We walk the branches until we encounter one whose condition is `true`,
// and pick its action. If there is no branch whose condition is `true`,
// we don't provide a nested `type`, which enables us to mimic the
// functionality provided by `enable_if`.
template <typename ...Branches>
struct evaluate_branches;

template <typename Branch, typename ...Rest>
struct evaluate_branches<Branch, Rest...>
    : conditional<
        Branch::condition,
        typename Branch::action,
        eval<evaluate_branches<Rest...>>
    >
{ };

template <> struct evaluate_branches<> { };


template <typename ...Branches>
struct jump_table {
    template <bool Cond, typename Action>
    using append = jump_table<Branches..., branch<Cond, Action>>;

    struct evaluate : evaluate_branches<Branches...> { };
};

template <typename JumpTable> struct else_if_interface;
template <typename JumpTable> struct else_interface;
template <typename JumpTable> struct eval_interface;

struct if_interface {
    using JumpTable = jump_table<>;

    template <bool Cond, typename ...>
    struct if_c;

    template <typename Cond, typename ...Args>
    using if_ = if_c<Cond::type::value, Args...>;

    template <bool Cond>
    struct if_c<Cond>
        : eval_interface<
            // emulate enable_if
            typename JumpTable::template append<Cond, void>
        >
    {
        template <typename Then>
        using then = if_c<Cond, Then>;
    };

    template <bool Cond, typename Then>
    struct if_c<Cond, Then>
        : else_if_interface<
            typename JumpTable::template append<Cond, Then>
        >,
        else_interface<
            typename JumpTable::template append<Cond, Then>
        >,
        eval_interface<
            typename JumpTable::template append<Cond, Then>
        >
    { };

    template <bool Cond, typename Then, typename Else>
    struct if_c<Cond, Then, Else>
        : else_interface<
            typename JumpTable::template append<Cond, Then>
        >::template else_<Else>
    { };
};

template <typename JumpTable>
struct else_if_interface {
    template <bool Cond, typename ...>
    struct else_if_c;

    template <typename Cond, typename ...Args>
    using else_if = else_if_c<Cond::type::value, Args...>;

    template <bool Cond>
    struct else_if_c<Cond>
        : eval_interface<
            // emulate enable_if
            typename JumpTable::template append<Cond, void>
        >
    {
        template <typename Then>
        using then = else_if_c<Cond, Then>;
    };

    template <bool Cond, typename Then>
    struct else_if_c<Cond, Then>
        : else_if_interface<
            typename JumpTable::template append<Cond, Then>
        >,
        else_interface<
            typename JumpTable::template append<Cond, Then>
        >,
        eval_interface<
            typename JumpTable::template append<Cond, Then>
        >
    { };

    template <bool Cond, typename Then, typename Else>
    struct else_if_c<Cond, Then, Else>
        : else_interface<
            typename JumpTable::template append<Cond, Then>
        >::template else_<Else>
    { };
};

template <typename JumpTable>
struct else_interface {
    template <typename Else>
    struct else_
        : eval_interface<
            typename JumpTable::template append<true, Else>
        >
    { };
};

template <typename JumpTable>
struct eval_interface
    : JumpTable::evaluate
{ };
} // end namespace if_detail

template <bool Cond, typename ...Args>
struct if_c
    : if_detail::if_interface::template if_c<Cond, Args...>
{ };

template <typename Cond, typename ...Args>
using if_ = if_c<Cond::type::value, Args...>;
}}}

#endif // !BOOST_MPL11_IF_HPP