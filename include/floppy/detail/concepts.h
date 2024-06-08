#pragma once

#include <floppy/detail/type_traits.h>
#include <floppy/detail/types.h>

namespace floppy::concepts
{
  template <typename T>
  concept num = std::integral<plain_type_t<T>> or std::floating_point<plain_type_t<T>>;

  template <typename T>
  concept array = std::is_array_v<T>;

  template <typename T>
  concept object = std::is_object_v<plain_type_t<T>>;

  template <typename T>
  concept fn = std::is_function_v<plain_type_t<T>>;

  template <typename T>
  concept ptr = std::is_pointer_v<T>;

  template <typename T>
  concept ref = std::is_reference_v<T>;

  template <typename T>
  concept enum_ = std::is_enum_v<plain_type_t<T>>;

  template <typename T, typename C>
  concept formattable = requires(T t) {
    { t.to_string() } -> std::convertible_to<std::basic_string<C>>;
  };
} // namespace floppy::concepts