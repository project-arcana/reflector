#pragma once

#include <reflector/detail/is_introspectable.hh>

namespace rf
{
template <class T, class Inspector>
constexpr void do_introspect(Inspector&& inspector, T& t)
{
    static_assert(!std::is_const_v<std::remove_reference_t<T>>, "do_introspect must be called with an l-value ref");
    static_assert(is_introspectable<T>, "type is not introspectable. provide `template <class In> constexpr void introspect(In&& inspect, T& v);'");

    // TODO: other customization points
    introspect(inspector, t);
}
}
