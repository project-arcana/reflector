#pragma once

#include <reflector/detail/stringify.hh>

namespace rf
{
/// generic, introspection-powered to_string
///
/// in this order, the following are tested:
/// * to_string(value)
/// * cc::to_string(value)
/// * introspect(..., value)
///
/// TODO: implement stream-based version for better performance
template <class T>
auto to_string(T const& value) -> decltype(::rf_external_detail::impl_to_string(value, cc::priority_tag<2>{}))
{
    return ::rf_external_detail::impl_to_string(value, cc::priority_tag<2>{});
}

template <class T>
static constexpr bool has_to_string = ::rf_external_detail::has_to_string_t<T>::value;
}
