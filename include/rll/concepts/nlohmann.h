#pragma once

#include <type_traits>
#include <nlohmann/json.hpp>
#include <rll/global/definitions.h>

#if __cplusplus >= 202'002L
#  include <concepts>
#endif

namespace rll {
#if _cplusplus >= 202'002L || defined(RLL_DOC)
  concept nlohmann_serializable = requires(nlohmann::json j, auto const& t) {
    { nlohmann::json(j, t) } -> std::same_as<nlohmann::json>;
    { nlohmann::from_json(j, t) } -> std::same_as<void>;
  };
#endif
}  // namespace rll

namespace rll {
  template <typename T, typename = void>
  struct is_nlohmann_serializable : std::false_type {};

#ifndef DOXYGEN
  template <typename T>
  struct is_nlohmann_serializable<
    T,
    std::void_t<
      decltype(nlohmann::json(std::declval<nlohmann::json&>(), std::declval<T const&>())),
      decltype(nlohmann::from_json(std::declval<nlohmann::json const&>(), std::declval<T&>()))>>
    : std::true_type {};
#endif

  template <typename T>
  inline constexpr bool is_nlohmann_serializable_v = is_nlohmann_serializable<T>::value;
}  // namespace rll

static_assert(
  rll::is_nlohmann_serializable_v<int>,
  "int should be serializable with nlohmann::json"
);
static_assert(
  rll::is_nlohmann_serializable_v<std::string>,
  "std::string should be serializable with nlohmann::json"
);
