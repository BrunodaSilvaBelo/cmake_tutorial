#ifndef CMAKE_UNIT_H
#define CMAKE_UNIT_H

#include <type_traits>

namespace cm {

template <typename T, typename U, typename Operator> class Glue {
  T const& t;
  U const& u;
  Operator& op;

  constexpr Glue(T const& _t, U const& _u, Operator& _op)
      : t(_t), u(_u), op(_op) {}
};

template <typename Derived> struct Unit {
  using return_type = Derived const&;
  return_type get_ref() const { return static_cast<Derived const&>(*this); }
};

template <typename T> struct Kilo : public Unit<Kilo<T>> {
  using value_type  = T;
  using return_type = value_type&;
  value_type value;

  constexpr Kilo(value_type value) : value(value) {}
  constexpr Kilo(Kilo<value_type>& kilo) : value(kilo.value) {}

  constexpr auto& operator+=(Kilo<value_type> const& rhs) {
    value += rhs.value;
    return *this;
  }

  constexpr auto& operator-=(Kilo<value_type> const& rhs) {
    value -= rhs.value;
    return *this;
  }
};
} // namespace cm

template <typename T>
constexpr auto operator+(cm::Kilo<T> const& lhs, cm::Kilo<T> const& rhs) {
  return cm::Kilo(lhs.value + rhs.value);
}

template <typename T>
constexpr auto operator-(cm::Kilo<T> const& lhs, cm::Kilo<T> const& rhs) {
  return cm::Kilo(lhs.value - rhs.value);
}

template <typename OUT, typename T>
constexpr OUT& operator<<(OUT& out, cm::Kilo<T> const& rhs) {
  return out << rhs.value << " kg";
}
#endif /* CMAKE_UNIT_H */
