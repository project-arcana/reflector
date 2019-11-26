#pragma once

#include <clean-core/bit_cast.hh>
#include <clean-core/string_view.hh>

#include <reflector/introspect.hh>

namespace rf
{
namespace detail
{
struct MemberwiseComparator
{
    std::byte const* lhs_raw;
    std::byte const* rhs_raw;
    bool is_equal = true;

    template <class T, class... Args>
    void operator()(T const& rhs_member, cc::string_view, Args&&...) noexcept
    {
        if (is_equal)
        {
            size_t const member_offset = cc::bit_cast<std::byte const*>(&rhs_member) - rhs_raw;
            T const& lhs_member = *reinterpret_cast<T const*>(lhs_raw + member_offset);
            is_equal = is_equal && (rhs_member == lhs_member);
        }
    }
};
}

/// performs a memberwise operator== comparison, returns true if all members compare equal
template <class T>
[[nodiscard]] bool member_compare(T const& lhs, T const& rhs) noexcept
{
    detail::MemberwiseComparator comparator;
    comparator.lhs_raw = cc::bit_cast<std::byte const*>(&lhs);
    comparator.rhs_raw = cc::bit_cast<std::byte const*>(&rhs);
    do_introspect<T>(comparator, const_cast<T&>(rhs));
    return comparator.is_equal;
}
}
