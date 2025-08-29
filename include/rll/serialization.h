#pragma once

#include <string>
#include <string_view>
#include <type_traits>
#include <nlohmann/json.hpp>

namespace rll {
  template <typename T, typename Backend>
  struct serialization_traits;

  template <typename T>
  struct serialization_traits<T, nlohmann::json> {
    [[nodiscard]] static nlohmann::json to(T const& t) {
      auto j = nlohmann::json();
      nlohmann::adl_serializer<T>::to_json(j, t);
      return j;
    }

    [[nodiscard]] static T from(nlohmann::json const& j) {
      auto obj = T();
      nlohmann::adl_serializer<T>::from_json(j, obj);
      return obj;
    }
  };

  template <typename Backend>
  struct serializer {
    template <typename T>
    [[nodiscard]] static auto serialize(T const& t) {
      return serialization_traits<T, Backend>::to(t);
    }

    template <typename T>
    [[nodiscard]] static auto deserialize(Backend const& data) {
      return serialization_traits<T, Backend>::from(data);
    }
  };
}  // namespace rll
