#pragma once

#include <reflector/detail/is_introspectable.hh>

namespace rf
{
template <class T>
static constexpr bool is_introspectable = rf::detail::is_introspectable_t<T>::value;

template <class Inspector, class T>
constexpr void do_introspect(Inspector&& inspector, T& t)
{
    static_assert(!std::is_const_v<std::remove_reference_t<T>>, "do_introspect must be called with an l-value ref");
    static_assert(is_introspectable<T>, "type is not introspectable.");

    // TODO: check if inspectable, other customization points
    introspect(inspector, t);
}
}
