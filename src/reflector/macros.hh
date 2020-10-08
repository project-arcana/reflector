#pragma once


/**
 * create an introspection function with a little less boilerplate
 *
 * usage:
 *
 *  REFL_INTROSPECT_FUNC(MyStructType)
 *  {
 *      REFL_INTROSPECT_FIELD(f1);
 *      REFL_INTROSPECT_FIELD(f2);
 *      REFL_INTROSPECT_FIELD(f3);
 *      // ... list all fields ...
 *
 *      // or multiple fields at once
 *      REFL_INTROSPECT_FIELD4(scale, bias, f7, f8);
 *
 *      // custom names
 *      inspect(v.scaleInv, "inverse scale");
 *  }
 *
 */

#define REFL_INTROSPECT_FUNC(_type_) \
    template <class In>              \
    constexpr void introspect(In&& inspect, _type_& v)

#define REFL_INTROSPECT_FIELD(_field_) inspect(v._field_, #_field_)

#define REFL_INTROSPECT_FIELD4(_field1_, _field2_, _field3_, _field4_) \
    REFL_INTROSPECT_FIELD(_field1_);                                   \
    REFL_INTROSPECT_FIELD(_field2_);                                   \
    REFL_INTROSPECT_FIELD(_field3_);                                   \
    REFL_INTROSPECT_FIELD(_field4_)
