#pragma once

#include <reflector/helper.hh>

namespace rf
{
template <class T>
static constexpr bool is_introspectable = decltype(rf::detail::is_introspectable_test(std::declval<T&>()))::value;

template <class T, class Inspector>
constexpr void do_introspect(Inspector&& inspector, T& t)
{
    static_assert(is_introspectable<T>, "type is not introspectable.");

    // TODO: check if inspectable, other customization points
    introspect(inspector, t);
}
}
