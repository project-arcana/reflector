#pragma once

#include <clean-core/macros.hh>

/**
 * create an introspection function with a little less boilerplate
 *
 * usage:
 *
 *  REFL_INTROSPECT(MyStructType)
 *  {
 *      REFL_FIELD(f1);
 *      REFL_FIELD(f2);
 *      REFL_FIELD(f3);
 *      // ... list all fields ...
 *
 *      // or multiple fields at once (explicit count)
 *      REFL_FIELD4(scale, bias, f7, f8);
 *
 *      // or multiple fields at once (implicit count)
 *      REFL_FIELDS(f10, f11, f12);
 *
 *      // custom names
 *      inspect(v.scaleInv, "inverse scale");
 *  }
 *
 * NOTE: follows the typical introspect conventions. (the inspector is called 'inspect' and the value 'v')
 * NOTE: use REFL_MAKE_INTROSPECTABLE(...); for even less boilerplate
 */
#define REFL_INTROSPECT(_type_) \
    template <class In>         \
    constexpr void introspect(In&& inspect, _type_& v)

/// defines a reflected field (for use inside of REFL_INTROSPECT)
#define REFL_FIELD(f) inspect(v.f, #f)

/// defines introspect and reflect fields for a given type
/// NOTE: currently supports up to 9 fields
/// Usage: REFL_MAKE_INTROSPECTABLE(MyStructType, field0, field1, field2);
#define REFL_MAKE_INTROSPECTABLE(TYPE, ...)                                                                                       \
    REFL_INTROSPECT(TYPE) { REFL_IMPL_MACRO_APPLY(REFL_IMPL_MACRO_PASTE(REFL_FIELD, REFL_IMPL_NARG(__VA_ARGS__)), __VA_ARGS__); } \
    CC_FORCE_SEMICOLON

/// defines a variable number of reflected fields for a given type
/// NOTE: currently supports up to 9 fields
/// NOTE: use inside REFL_INTROSPECT
/// Usage: REFL_FIELDS(f0, f1, f2);
#define REFL_FIELDS(...) REFL_IMPL_MACRO_APPLY(REFL_IMPL_MACRO_PASTE(REFL_FIELD, REFL_IMPL_NARG(__VA_ARGS__)), __VA_ARGS__)

//
// Implementation details
//

#define REFL_IMPL_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N

#define REFL_IMPL_NARG(...) REFL_IMPL_EXPAND(REFL_IMPL_NARG_(__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define REFL_IMPL_NARG_(...) REFL_IMPL_EXPAND(REFL_IMPL_ARG_N(__VA_ARGS__))

#define REFL_IMPL_EXPAND(x) x
#define REFL_IMPL_MACRO_PASTE_(a, b) a##b
#define REFL_IMPL_MACRO_PASTE(a, b) REFL_IMPL_MACRO_PASTE_(a, b)
#define REFL_IMPL_MACRO_APPLY(M, ...) REFL_IMPL_EXPAND(M(__VA_ARGS__))

#define REFL_FIELD1(f0) REFL_FIELD(f0)

#define REFL_FIELD2(f0, f1) \
    REFL_FIELD(f0);         \
    REFL_FIELD(f1)

#define REFL_FIELD3(f0, f1, f2) \
    REFL_FIELD(f0);             \
    REFL_FIELD(f1);             \
    REFL_FIELD(f2)

#define REFL_FIELD4(f0, f1, f2, f3) \
    REFL_FIELD(f0);                 \
    REFL_FIELD(f1);                 \
    REFL_FIELD(f2);                 \
    REFL_FIELD(f3)

#define REFL_FIELD5(f0, f1, f2, f3, f4) \
    REFL_FIELD(f0);                     \
    REFL_FIELD(f1);                     \
    REFL_FIELD(f2);                     \
    REFL_FIELD(f3);                     \
    REFL_FIELD(f4)

#define REFL_FIELD6(f0, f1, f2, f3, f4, f5) \
    REFL_FIELD(f0);                         \
    REFL_FIELD(f1);                         \
    REFL_FIELD(f2);                         \
    REFL_FIELD(f3);                         \
    REFL_FIELD(f4);                         \
    REFL_FIELD(f5)

#define REFL_FIELD7(f0, f1, f2, f3, f4, f5, f6) \
    REFL_FIELD(f0);                             \
    REFL_FIELD(f1);                             \
    REFL_FIELD(f2);                             \
    REFL_FIELD(f3);                             \
    REFL_FIELD(f4);                             \
    REFL_FIELD(f5);                             \
    REFL_FIELD(f6)

#define REFL_FIELD8(f0, f1, f2, f3, f4, f5, f6, f7) \
    REFL_FIELD(f0);                                 \
    REFL_FIELD(f1);                                 \
    REFL_FIELD(f2);                                 \
    REFL_FIELD(f3);                                 \
    REFL_FIELD(f4);                                 \
    REFL_FIELD(f5);                                 \
    REFL_FIELD(f6);                                 \
    REFL_FIELD(f7)

#define REFL_FIELD9(f0, f1, f2, f3, f4, f5, f6, f7, f8) \
    REFL_FIELD(f0);                                     \
    REFL_FIELD(f1);                                     \
    REFL_FIELD(f2);                                     \
    REFL_FIELD(f3);                                     \
    REFL_FIELD(f4);                                     \
    REFL_FIELD(f5);                                     \
    REFL_FIELD(f6);                                     \
    REFL_FIELD(f7);                                     \
    REFL_FIELD(f8)
