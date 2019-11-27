#pragma once

#include <clean-core/assert.hh>
#include <clean-core/bit_cast.hh>

#include <reflector/introspect.hh>

namespace rf
{
namespace detail
{
template <class OuterT>
struct MemberwiseComparator
{
    std::byte const* lhs_raw;
    std::byte const* rhs_raw;
    bool is_equal = true;

    template <class T, class... Args>
    void operator()(T const& rhs_member, char const*, Args&&...) noexcept
    {
        static_assert(sizeof(T) > 0, "No incomplete members allowed");
        if (is_equal)
        {
            size_t const member_offset = cc::bit_cast<std::byte const*>(&rhs_member) - rhs_raw;
            CC_ASSERT(member_offset < sizeof(OuterT));
            T const& lhs_member = *reinterpret_cast<T const*>(lhs_raw + member_offset);
            is_equal = (rhs_member == lhs_member);
        }
    }
};
}

/// performs a memberwise operator== comparison, returns true if all members compare equal
template <class T>
[[nodiscard]] bool member_compare(T const& lhs, T const& rhs) noexcept
{
    static_assert(sizeof(T) > 0, "No incomplete types allowed");
    detail::MemberwiseComparator<T> comparator;
    comparator.lhs_raw = cc::bit_cast<std::byte const*>(&lhs);
    comparator.rhs_raw = cc::bit_cast<std::byte const*>(&rhs);
    do_introspect<T>(comparator, const_cast<T&>(rhs));
    return comparator.is_equal;
}
}
