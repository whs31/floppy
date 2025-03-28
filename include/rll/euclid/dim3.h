#pragma once

#include <type_traits>
#include <fmt/format.h>

#ifdef _MSC_VER
#  include <ciso646>
#endif

namespace rll {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  struct dim3 {
    T x;
    T y;
    T z;

    constexpr dim3()
      : x(0)
      , y(0)
      , z(0) {}

    explicit constexpr dim3(T v)
      : x(v)
      , y(v)
      , z(v) {}

    constexpr dim3(T x, T y, T z)
      : x(x)
      , y(y)
      , z(z) {}

    template <typename U>
    constexpr bool operator==(dim3<U> const& other) const {
      return x == other.x and y == other.y and z == other.z;
    }

    template <typename U>
    constexpr bool operator!=(dim3<U> const& other) const {
      return x != other.x or y != other.y or z != other.z;
    }

    template <typename U>
    constexpr bool operator<(dim3<U> const& other) const {
      return x < other.x and y < other.y and z < other.z;
    }

    template <typename U>
    constexpr bool operator>(dim3<U> const& other) const {
      return x > other.x and y > other.y and z > other.z;
    }

    template <typename U>
    constexpr bool operator<=(dim3<U> const& other) const {
      return x <= other.x and y <= other.y and z <= other.z;
    }

    template <typename U>
    constexpr bool operator>=(dim3<U> const& other) const {
      return x >= other.x and y >= other.y and z >= other.z;
    }

    template <typename U>
    constexpr auto operator+=(dim3<U> const& other) {
      x += other.x;
      y += other.y;
      z += other.z;
      return *this;
    }

    template <typename U>
    constexpr auto operator-=(dim3<U> const& other) {
      x -= other.x;
      y -= other.y;
      z -= other.z;
      return *this;
    }

    template <typename U>
    constexpr auto operator*=(dim3<U> const& other) {
      x *= other.x;
      y *= other.y;
      z *= other.z;
      return *this;
    }

    template <typename U>
    constexpr auto operator/=(dim3<U> const& other) {
      x /= other.x;
      y /= other.y;
      z /= other.z;
      return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator+=(U const& other) {
      x += other;
      y += other;
      z += other;
      return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator-=(U const& other) {
      x -= other;
      y -= other;
      z -= other;
      return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator*=(U const& other) {
      x *= other;
      y *= other;
      z *= other;
      return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator/=(U const& other) {
      x /= other;
      y /= other;
      z /= other;
      return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator+(dim3<U> const& other) const {
      return dim3<T>(x + other.x, y + other.y, z + other.z);
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator-(dim3<U> const& other) const {
      return dim3<T>(x - other.x, y - other.y, z - other.z);
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator*(dim3<U> const& other) const {
      return dim3<T>(x * other.x, y * other.y, z * other.z);
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator/(dim3<U> const& other) const {
      return dim3<T>(x / other.x, y / other.y, z / other.z);
    }

    constexpr auto operator-() const { return dim3<T>(-x, -y, -z); }

    constexpr auto operator+() const { return *this; }
  };

  template <
    typename T,
    typename U,
    typename = std::enable_if_t<std::is_arithmetic_v<T> and std::is_arithmetic_v<U>>>
  constexpr auto operator+(T const& lhs, dim3<U> const& rhs) {
    return dim3<T>(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
  }

  template <
    typename T,
    typename U,
    typename = std::enable_if_t<std::is_arithmetic_v<T> and std::is_arithmetic_v<U>>>
  constexpr auto operator-(T const& lhs, dim3<U> const& rhs) {
    return dim3<T>(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
  }

  template <
    typename T,
    typename U,
    typename = std::enable_if_t<std::is_arithmetic_v<T> and std::is_arithmetic_v<U>>>
  constexpr auto operator*(T const& lhs, dim3<U> const& rhs) {
    return dim3<T>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
  }

  template <
    typename T,
    typename U,
    typename = std::enable_if_t<std::is_arithmetic_v<T> and std::is_arithmetic_v<U>>>
  constexpr auto operator/(T const& lhs, dim3<U> const& rhs) {
    return dim3<T>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
  }

  template <typename T, typename U>
  constexpr auto operator%(dim3<T> const& lhs, dim3<U> const& rhs) {
    return dim3<T>(lhs.x % rhs.x, lhs.y % rhs.y, lhs.z % rhs.z);
  }
}  // namespace rll

/**
 * @brief Specialization of the `fmt::formatter` for the rll::dim3 class.
 * @tparam T Number type.
 * @relates rll::dim3
 */
template <typename T>
struct fmt::formatter<rll::dim3<T>> {
  constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

  auto format(rll::dim3<T> const& val, format_context& ctx) const {
    fmt::format_to(ctx.out(), "[{}, {}, {}]", val.x, val.y, val.z);
    return ctx.out();
  }
};

#ifdef ROLLY_SERDE
#  include <nlohmann/json.hpp>

NLOHMANN_JSON_NAMESPACE_BEGIN

template <typename T>
struct [[maybe_unused]] adl_serializer<rll::dim3<T>> {
  static void to_json(json& j, rll::dim3<T> const& v) {
    j = {
      {"x", v.x},
      {"y", v.y},
      {"z", v.z}
    };
  }

  static void from_json(json const& j, rll::dim3<T>& v) {
    v = rll::dim3<T>(j["x"].template get<T>(), j["y"].template get<T>(), j["z"].template get<T>());
  }
};

NLOHMANN_JSON_NAMESPACE_END

#endif
