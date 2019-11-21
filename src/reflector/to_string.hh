#pragma once

#include <clean-core/always_false.hh>
#include <clean-core/priority_tag.hh>
#include <clean-core/string.hh>
#include <clean-core/to_string.hh>

#include <reflector/introspect.hh>

namespace rf
{
/// generic, introspection-powered to_string
///
/// in this order, the following are tested:
/// * to_string(value)
/// * cc::to_string(value)
/// * introspect(..., value)
/// * <compile error>
///
/// TODO: implement stream-based version for better performance
template <class T>
cc::string to_string(T const& value);
}

namespace rf_external_detail
{
struct stringifier
{
    cc::string& s;

    stringifier(cc::string& s) : s(s) { s += '{'; }
    ~stringifier() { s += '}'; }
};

template <class T>
auto impl_to_string(T const& value, cc::priority_tag<3>) -> decltype(to_string(value))
{
    return to_string(value);
}

template <class T>
auto impl_to_string(T const& value, cc::priority_tag<2>) -> decltype(cc::to_string(value))
{
    return cc::to_string(value);
}

template <class T, class = std::enable_if_t<rf::is_introspectable<T>>>
cc::string impl_to_string(T const& value, cc::priority_tag<1>)
{
    cc::string str;
    {
        auto s = stringifier(str);
        rf::do_introspect(s, const_cast<T&>(value)); // promise we will not change anything!
    }
    return str;
}

template <class T>
cc::string impl_to_string(T const& value, cc::priority_tag<0>)
{
    static_assert(cc::always_false<T>, "unable to stringify the given type");
    return {};
}
}

template <class T>
cc::string rf::to_string(T const& value)
{
    return ::rf_external_detail::impl_to_string(value, cc::priority_tag<3>{});
}
