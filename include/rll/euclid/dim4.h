#pragma once

#include <type_traits>
#include <fmt/format.h>

#ifdef _MSC_VER
#  include <ciso646>
#endif

namespace rll {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  struct dim4 {
    T x;
    T y;
    T z;
    T w;

    constexpr dim4()
      : x(0)
      , y(0)
      , z(0)
      , w(0) {}

    explicit constexpr dim4(T v)
      : x(v)
      , y(v)
      , z(v)
      , w(v) {}

    constexpr dim4(T x, T y, T z, T w)
      : x(x)
      , y(y)
      , z(z)
      , w(w) {}

    template <typename U>
    constexpr bool operator==(dim4<U> const& other) const {
      return x == other.x and y == other.y and z == other.z and w == other.w;
    }

    template <typename U>
    constexpr bool operator!=(dim4<U> const& other) const {
      return x != other.x or y != other.y or z != other.z or w != other.w;
    }

    template <typename U>
    constexpr bool operator<(dim4<U> const& other) const {
      return x < other.x and y < other.y and z < other.z and w < other.w;
    }

    template <typename U>
    constexpr bool operator>(dim4<U> const& other) const {
      return x > other.x and y > other.y and z > other.z and w > other.w;
    }

    template <typename U>
    constexpr bool operator<=(dim4<U> const& other) const {
      return x <= other.x and y <= other.y and z <= other.z and w <= other.w;
    }

    template <typename U>
    constexpr bool operator>=(dim4<U> const& other) const {
      return x >= other.x and y >= other.y and z >= other.z and w >= other.w;
    }

    template <typename U>
    constexpr auto operator+=(dim4<U> const& other) {
      x += other.x;
      y += other.y;
      z += other.z;
      w += other.w;
      return *this;
    }

    template <typename U>
    constexpr auto operator-=(dim4<U> const& other) {
      x -= other.x;
      y -= other.y;
      z -= other.z;
      w -= other.w;
      return *this;
    }

    template <typename U>
    constexpr auto operator*=(dim4<U> const& other) {
      x *= other.x;
      y *= other.y;
      z *= other.z;
      w *= other.w;
      return *this;
    }

    template <typename U>
    constexpr auto operator/=(dim4<U> const& other) {
      x /= other.x;
      y /= other.y;
      z /= other.z;
      w /= other.w;
      return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator+=(U const& other) {
      x += other;
      y += other;
      z += other;
      w += other;
      return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator-=(U const& other) {
      x -= other;
      y -= other;
      z -= other;
      w -= other;
      return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator*=(U const& other) {
      x *= other;
      y *= other;
      z *= other;
      w *= other;
      return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator/=(U const& other) {
      x /= other;
      y /= other;
      z /= other;
      w /= other;
      return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator+(dim4<U> const& other) const {
      return dim4<T>(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator-(dim4<U> const& other) const {
      return dim4<T>(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator*(dim4<U> const& other) const {
      return dim4<T>(x * other.x, y * other.y, z * other.z, w * other.w);
    }

    template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator/(dim4<U> const& other) const {
      return dim4<T>(x / other.x, y / other.y, z / other.z, w / other.w);
    }

    constexpr auto operator-() const { return dim4<T>(-x, -y, -z, -w); }

    constexpr auto operator+() const { return *this; }
  };

  template <
    typename T,
    typename U,
    typename = std::enable_if_t<std::is_arithmetic_v<T> and std::is_arithmetic_v<U>>>
  constexpr auto operator+(T const& lhs, dim4<U> const& rhs) {
    return dim4<T>(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w);
  }

  template <
    typename T,
    typename U,
    typename = std::enable_if_t<std::is_arithmetic_v<T> and std::is_arithmetic_v<U>>>
  constexpr auto operator-(T const& lhs, dim4<U> const& rhs) {
    return dim4<T>(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w);
  }

  template <
    typename T,
    typename U,
    typename = std::enable_if_t<std::is_arithmetic_v<T> and std::is_arithmetic_v<U>>>
  constexpr auto operator*(T const& lhs, dim4<U> const& rhs) {
    return dim4<T>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
  }

  template <
    typename T,
    typename U,
    typename = std::enable_if_t<std::is_arithmetic_v<T> and std::is_arithmetic_v<U>>>
  constexpr auto operator/(T const& lhs, dim4<U> const& rhs) {
    return dim4<T>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w);
  }

  template <typename T, typename U>
  constexpr auto operator%(dim4<T> const& lhs, dim4<U> const& rhs) {
    return dim4<T>(lhs.x % rhs.x, lhs.y % rhs.y, lhs.z % rhs.z, lhs.w % rhs.w);
  }
}  // namespace rll

/**
 * @brief Specialization of the `fmt::formatter` for the rll::dim4 class.
 * @tparam T Number type.
 * @relates rll::dim4
 */
template <typename T>
struct fmt::formatter<rll::dim4<T>> {
  constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

  auto format(rll::dim4<T> const& val, format_context& ctx) const {
    fmt::format_to(ctx.out(), "[{}, {}, {}, {}]", val.x, val.y, val.z, val.w);
    return ctx.out();
  }
};

#ifdef ROLLY_SERDE
#  include <nlohmann/json.hpp>

NLOHMANN_JSON_NAMESPACE_BEGIN

template <typename T>
struct [[maybe_unused]] adl_serializer<rll::dim4<T>> {
  static void to_json(json& j, rll::dim4<T> const& v) {
    j = {
      {"x", v.x},
      {"y", v.y},
      {"z", v.z},
      {"w", v.w}
    };
  }

  static void from_json(json const& j, rll::dim4<T>& v) {
    v = rll::dim4<T>(
      j["x"].template get<T>(),
      j["y"].template get<T>(),
      j["z"].template get<T>(),
      j["w"].template get<T>()
    );
  }
};

NLOHMANN_JSON_NAMESPACE_END

#endif
