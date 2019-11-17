#pragma once

#include <type_traits>

namespace rf::detail
{
struct dummy_inspector
{
};

template <class T>
auto is_introspectable_test(T& t) -> decltype(introspect(dummy_inspector{}, t), std::true_type{});
std::false_type is_introspectable_test(...);
}
