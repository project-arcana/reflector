#pragma once


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
 *      // or multiple fields at once
 *      REFL_FIELD4(scale, bias, f7, f8);
 *
 *      // custom names
 *      inspect(v.scaleInv, "inverse scale");
 *  }
 *
 */

#define REFL_INTROSPECT(_type_) \
    template <class In>         \
    constexpr void introspect(In&& inspect, _type_& v)

#define REFL_FIELD(_field_) inspect(v._field_, #_field_)

#define REFL_FIELD4(_field1_, _field2_, _field3_, _field4_) \
    REFL_FIELD(_field1_);                                   \
    REFL_FIELD(_field2_);                                   \
    REFL_FIELD(_field3_);                                   \
    REFL_FIELD(_field4_)
