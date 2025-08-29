#pragma once

#include <rll/euclid/angle.h>
#include <rll/serialization.h>

namespace rll {
  template <typename T, typename = std::enable_if_t<is_num_v<T>>>
  struct euler_angles {
    angle<T> pitch;
    angle<T> yaw;
    angle<T> roll;
  };
}  // namespace rll

/**
 * @brief Specialization of the `fmt::formatter` for the rll::euler_angles class.
 * @tparam T Number type.
 * @relates rll::euler_angles
 */
template <typename T>
struct fmt::formatter<rll::euler_angles<T>> {
  constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

  auto format(rll::euler_angles<T> const& val, format_context& ctx) const {
    fmt::format_to(ctx.out(), "{{ pitch: {}, yaw: {}, roll: {} }}", val.pitch, val.yaw, val.roll);
    return ctx.out();
  }
};

NLOHMANN_JSON_NAMESPACE_BEGIN

template <typename T>
struct [[maybe_unused]] adl_serializer<rll::euler_angles<T>> {
  static void to_json(json& j, rll::euler_angles<T> const& v) {
    j = {
      {"pitch", v.pitch.degrees()},
      {"yaw",   v.yaw.degrees()  },
      {"roll",  v.roll.degrees() }
    };
  }

  static void from_json(json const& j, rll::euler_angles<T>& v) {
    v.pitch = rll::angle<T>::from_degrees(j["pitch"].template get<T>());
    v.yaw = rll::angle<T>::from_degrees(j["yaw"].template get<T>());
    v.roll = rll::angle<T>::from_degrees(j["roll"].template get<T>());
  }
};

NLOHMANN_JSON_NAMESPACE_END
