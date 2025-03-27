#pragma once

#include <type_traits>
#include <fmt/format.h>

#ifdef _MSC_VER
#  include <ciso646>
#endif

namespace rll {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  struct dim2 {
    T x;
    T y;

    constexpr dim2()
      : x(0)
      , y(0) {}

    explicit constexpr dim2(T v)
      : x(v)
      , y(v) {}

    constexpr dim2(T x, T y)
      : x(x)
      , y(y) {}

    template <typename U>
    constexpr bool operator==(dim2<U> const& other) const {
      return x == other.x and y == other.y;
    }

    template <typename U>
    constexpr bool operator!=(dim2<U> const& other) const {
      return x != other.x or y != other.y;
    }

    template <typename U>
    constexpr bool operator<(dim2<U> const& other) const {
      return x < other.x and y < other.y;
    }

    template <typename U>
    constexpr bool operator>(dim2<U> const& other) const {
      return x > other.x and y > other.y;
    }

    template <typename U>
    constexpr bool operator<=(dim2<U> const& other) const {
      return x <= other.x and y <= other.y;
    }

    template <typename U>
    constexpr bool operator>=(dim2<U> const& other) const {
      return x >= other.x and y >= other.y;
    }

    template <typename U>
    constexpr auto operator+=(dim2<U> const& other) {
      x += other.x;
      y += other.y;
      return *this;
    }

    template <typename U>
    constexpr auto operator-=(dim2<U> const& other) {
      x -= other.x;
      y -= other.y;
      return *this;
    }

    template <typename U>
    constexpr auto operator*=(dim2<U> const& other) {
      x *= other.x;
      y *= other.y;
      return *this;
    }

    template <typename U>
    constexpr auto operator/=(dim2<U> const& other) {
      x /= other.x;
      y /= other.y;
      return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator+=(U const& other) {
      x += other;
      y += other;
      return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator-=(U const& other) {
      x -= other;
      y -= other;
      return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator*=(U const& other) {
      x *= other;
      y *= other;
      return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator/=(U const& other) {
      x /= other;
      y /= other;
      return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator+(dim2<U> const& other) const {
      return dim2<T>(x + other.x, y + other.y);
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator-(dim2<U> const& other) const {
      return dim2<T>(x - other.x, y - other.y);
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator*(dim2<U> const& other) const {
      return dim2<T>(x * other.x, y * other.y);
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator/(dim2<U> const& other) const {
      return dim2<T>(x / other.x, y / other.y);
    }

    constexpr auto operator-() const { return dim2<T>(-x, -y); }

    constexpr auto operator+() const { return *this; }
  };

  template <
    typename T,
    typename U,
    typename = std::enable_if_t<std::is_arithmetic_v<T> and std::is_arithmetic_v<U>>>
  constexpr auto operator+(T const& lhs, dim2<U> const& rhs) {
    return dim2<T>(lhs + rhs.x, lhs + rhs.y);
  }

  template <
    typename T,
    typename U,
    typename = std::enable_if_t<std::is_arithmetic_v<T> and std::is_arithmetic_v<U>>>
  constexpr auto operator-(T const& lhs, dim2<U> const& rhs) {
    return dim2<T>(lhs - rhs.x, lhs - rhs.y);
  }

  template <
    typename T,
    typename U,
    typename = std::enable_if_t<std::is_arithmetic_v<T> and std::is_arithmetic_v<U>>>
  constexpr auto operator*(T const& lhs, dim2<U> const& rhs) {
    return dim2<T>(lhs * rhs.x, lhs * rhs.y);
  }

  template <
    typename T,
    typename U,
    typename = std::enable_if_t<std::is_arithmetic_v<T> and std::is_arithmetic_v<U>>>
  constexpr auto operator/(T const& lhs, dim2<U> const& rhs) {
    return dim2<T>(lhs / rhs.x, lhs / rhs.y);
  }

  template <typename T, typename U>
  constexpr auto operator%(dim2<T> const& lhs, dim2<U> const& rhs) {
    return dim2<T>(lhs.x % rhs.x, lhs.y % rhs.y);
  }
}  // namespace rll

/**
 * @brief Specialization of the `fmt::formatter` for the rll::dim2 class.
 * @tparam T Number type.
 * @relates rll::dim2
 */
template <typename T>
struct fmt::formatter<rll::dim2<T>> {
  constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

  auto format(rll::dim2<T> const& val, format_context& ctx) const {
    fmt::format_to(ctx.out(), "[{}, {}]", val.x, val.y);
    return ctx.out();
  }
};

#ifdef ROLLY_SERDE
#  include <nlohmann/json.hpp>

NLOHMANN_JSON_NAMESPACE_BEGIN

template <typename T>
struct [[maybe_unused]] adl_serializer<rll::dim2<T>> {
  static void to_json(json& j, rll::dim2<T> const& v) {
    j = {
      {"x", v.x},
      {"y", v.y}
    };
  }

  static void from_json(json const& j, rll::dim2<T>& v) {
    v = rll::dim2<T>(j["x"].template get<T>(), j["y"].template get<T>());
  }
};

NLOHMANN_JSON_NAMESPACE_END

#endif
