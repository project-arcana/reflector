#pragma once

#include <type_traits>

#include <clean-core/assert.hh>
#include <clean-core/bit_cast.hh>
#include <clean-core/has_operator.hh>
#include <clean-core/move.hh>

#include <reflector/introspect.hh>

namespace rf
{
/// returns lhs == rhs if defined, otherwise performs a memberwise comparison
template <class T>
[[nodiscard]] bool is_equal(T const& lhs, T const& rhs) noexcept;

/// lhs != rhs
template <class T>
[[nodiscard]] bool is_not_equal(T const& lhs, T const& rhs) noexcept
{
    return !is_equal(lhs, rhs);
}

/// lhs < rhs
template <class T>
[[nodiscard]] bool is_less(T const& lhs, T const& rhs) noexcept;

/// lhs >= rhs
template <class T>
[[nodiscard]] bool is_greater_equal(T const& lhs, T const& rhs) noexcept
{
    return !is_less(lhs, rhs);
}

/// lhs > rhs
template <class T>
[[nodiscard]] bool is_greater(T const& lhs, T const& rhs) noexcept
{
    return is_less(rhs, lhs);
}

/// lhs <= rhs
template <class T>
[[nodiscard]] bool is_less_equal(T const& lhs, T const& rhs) noexcept
{
    return !is_less(rhs, lhs);
}

namespace detail
{
template <class OuterT, class FunctorT>
struct MemberwiseComparator
{
    MemberwiseComparator(FunctorT comp_op) : comp_op(comp_op) {}

    std::byte const* lhs_raw;
    std::byte const* rhs_raw;
    FunctorT comp_op;
    bool condition_true = true;

    template <class T, class... Args>
    void operator()(T const& rhs_member, char const*, Args&&...) noexcept
    {
        static_assert(sizeof(T) > 0, "No incomplete members allowed");
        if (condition_true)
        {
            size_t const member_offset = cc::bit_cast<std::byte const*>(&rhs_member) - rhs_raw;
            CC_ASSERT(member_offset < sizeof(OuterT));
            T const& lhs_member = *reinterpret_cast<T const*>(lhs_raw + member_offset);
            static_assert(std::is_same_v<T const&, decltype(lhs_member)>);
            condition_true = comp_op(lhs_member, rhs_member);
        }
    }
};
}

template <class T>
[[nodiscard]] bool is_equal(T const& lhs, T const& rhs) noexcept
{
    static_assert(sizeof(T) > 0, "No incomplete types allowed");
    if constexpr (cc::has_operator_equal<T, T>)
    {
        return lhs == rhs;
    }
    else
    {
        auto const comp_op = [](auto lhs, auto rhs) { return rf::is_equal(lhs, rhs); };
        detail::MemberwiseComparator<T, decltype(comp_op)> comparator(comp_op);
        comparator.lhs_raw = cc::bit_cast<std::byte const*>(&lhs);
        comparator.rhs_raw = cc::bit_cast<std::byte const*>(&rhs);
        do_introspect<T>(comparator, const_cast<T&>(rhs));
        return comparator.condition_true;
    }
}


template <class T>
[[nodiscard]] bool is_less(T const& lhs, T const& rhs) noexcept
{
    static_assert(sizeof(T) > 0, "No incomplete types allowed");
    if constexpr (cc::has_operator_equal<T, T>)
    {
        return lhs < rhs;
    }
    else
    {
        auto const comp_op = [](auto lhs, auto rhs) { return rf::is_less(lhs, rhs); };
        detail::MemberwiseComparator<T, decltype(comp_op)> comparator(comp_op);
        comparator.lhs_raw = cc::bit_cast<std::byte const*>(&lhs);
        comparator.rhs_raw = cc::bit_cast<std::byte const*>(&rhs);
        do_introspect<T>(comparator, const_cast<T&>(rhs));
        return comparator.condition_true;
    }
}
}