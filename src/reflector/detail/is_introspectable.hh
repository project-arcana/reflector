#pragma once

#include <reflector/detail/null_inspector.hh>

#include <type_traits>

namespace rf::detail
{
template <class T, class = void>
struct is_introspectable_t : std::false_type
{
};
template <class T>
struct is_introspectable_t<T, std::void_t<decltype(introspect(null_inspector{}, std::declval<T&>()))>> : std::true_type
{
};
}
