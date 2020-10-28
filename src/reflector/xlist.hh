#pragma once


/**
 * Helpers for X Macro lists
 *
 * Usage:
 *
 * // create the list
 * #define COMMAND_LIST(X) \
 *     X(draw)               \
 *     X(dispatch)           \
 *     X(copy)               \
 *     X(resolve)
 *
 *
 * // declare an enum with these values
 * REFL_DECLARE_ENUM_CLASS(CommandTypes, COMMAND_LIST);
 *
 * // declare a to-string function
 * REFL_DECLARE_TOSTRING(to_string, CommandTypes, COMMAND_LIST);
 *
 * // use it in a manual context
 * enum class e_cmd_types : uint8_t
 * {
 *      zero_val = 0,
 *
 *      COMMAND_LIST(REFL_X_ENUM)
 *
 *      last_val = 0xffffffff
 * };
 *
 */


/// X Macro functor for enum declaration
#define REFL_X_ENUM(Val, ...) Val,

/// X Macro functor for a switch-case that stringifies the value
#define REFL_X_STRINGCASE(Val, ...) \
    case rf_xlist_enum::Val:        \
        return #Val;

/// Declares an enum class from a list
#define REFL_DECLARE_ENUM_CLASS(Type, List) \
    enum class Type                         \
    {                                       \
        List(REFL_X_ENUM)                   \
    }

/// Declares an enum class from a list, with specified underlying type
#define REFL_DECLARE_TYPED_ENUM_CLASS(Type, UnderlyingType, List) \
    enum class Type : UnderlyingType                              \
    {                                                             \
        List(REFL_X_ENUM)                                         \
    }

/// Declares a to-string function
#define REFL_DECLARE_TOSTRING(FuncName, Type, List)             \
    [[maybe_unused]] constexpr char const* FuncName(Type value) \
    {                                                           \
        using rf_xlist_enum = Type;                             \
        switch (value)                                          \
        {                                                       \
            List(REFL_X_STRINGCASE)                             \
        }                                                       \
        return "unknown " #Type;                                \
    }
